import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from geometry_msgs.msg import Point32
from rcl_interfaces.msg import ParameterDescriptor
from rcl_interfaces.msg import ParameterEvent # message type for set params callback
from rcl_interfaces.msg import SetParametersResult
from cv_bridge import CvBridge
import cv2
import numpy as np
import array


'''
This class implements a colour mask filter for images from ROS topic subscription.  
After applying a colour mask, contour moments are used to detect the coloured regions.
The centroid of the largest region is marked with a red dot and a yellow circle based on the size of the region.
The coordinates of the detected region are published by default to /colour_detection

The configuration of the colour filter is stored in node params
 - image_topic, default: 'image_raw'
 - output_topic, default: '/colour_detection'
 - show_trackbars, default: True
 - lower_limits, default: [0, 0, 0]
 - upper_limits, default: [255, 255, 255]

Changing image topic can be done dynamically, however is unsafe and leaves an active subscription to the original topic.  To safely change the image topic, launch the node with param configuration setting the correct image topic.
To change the output topic, launch the node with a param configuration setting the topic name.
Trackbars are available to simplify the adjustment of the colour filter.  To disable them, launch the node with a param configuration setting it to False.
Upper and lower limits can be updated via trackbars, CLI set params or service calls to set params.  If trackbars are visible the trackbars will also be updated to match.

A launch file setting params and an example yaml config file are provided within the package.  Note, the config folder is not included in the install.

@author: phs, with open cv filter based on imutils convenience.py
    #https://github.com/jrosebr1/imutils/blob/master/imutils/convenience.py
'''


class ColourDetector (Node):


    def __init__(self):

        super().__init__('colour_detector')

        self.initParams()


        self.subscription = self.create_subscription(
            Image, 
            self.image_topic, 
            self.image_callback, 
            10)
        self.subscription

        self.publisher_ = self.create_publisher(Point32, '/colour_detection', 10)
        

        #timer_period = 0.5  # seconds
        #self.timer = self.create_timer(timer_period, self.timer_callback)

        self.br = CvBridge()
        self.windowName = "Colour detector"
        cv2.namedWindow(self.windowName)
        #self.showTrackbars = True
        if self.showTrackbars:
            cv2.createTrackbar("B_High", self.windowName, 255, 255, self.nothing)
            cv2.createTrackbar("G_High", self.windowName, 255, 255, self.nothing)
            cv2.createTrackbar("R_High", self.windowName, 255, 255, self.nothing)
            cv2.createTrackbar("B_Low", self.windowName, 0, 255, self.nothing)
            cv2.createTrackbar("G_Low", self.windowName, 0, 255, self.nothing)
            cv2.createTrackbar("R_Low", self.windowName, 0, 255, self.nothing)

            self.updateTrackbars()       


        self.x=0.0
        self.y=0.0


    def initParams(self):
        limits_description = ParameterDescriptor(description='Limits used by OpenCV colour filter, listed BGR')
        self.declare_parameter('image_topic', 'image_raw')
        self.declare_parameter('output_topic', '/colour_detection')
        self.declare_parameter('show_trackbars', True)
        self.declare_parameter('lower_limits', [0, 0, 0], limits_description)
        self.declare_parameter('upper_limits', [255, 255, 255], limits_description)
        self.lowerLimit = np.uint8([0,0,0])
        self.upperLimit = np.uint8([255,255,255])

        self.showTrackbars = self.get_parameter('show_trackbars').get_parameter_value().bool_value
        self.image_topic = self.get_parameter('image_topic').get_parameter_value().string_value

        lowerLimitsParam = self.get_parameter('lower_limits').get_parameter_value()._integer_array_value
        upperLimitsParam = self.get_parameter('upper_limits').get_parameter_value()._integer_array_value
        self.lowerLimit = np.uint8(lowerLimitsParam)
        self.upperLimit = np.uint8(upperLimitsParam)
        
        

        self.add_on_set_parameters_callback(self.params_callback)

    def updateLimits(self):
        # obtain the current values for each of the sliders
        if self.showTrackbars:
            self.B_h = cv2.getTrackbarPos("B_High", self.windowName)
            self.G_h = cv2.getTrackbarPos("G_High", self.windowName)
            self.R_h = cv2.getTrackbarPos("R_High", self.windowName)
            self.B_l = cv2.getTrackbarPos("B_Low", self.windowName)
            self.G_l = cv2.getTrackbarPos("G_Low", self.windowName)
            self.R_l = cv2.getTrackbarPos("R_Low", self.windowName)

            changed = False
            if self.lowerLimit[0] != self.B_l or self.lowerLimit[1] != self.G_l or self.lowerLimit[2] != self.R_l:
                changed = True
            if self.upperLimit[0] != self.B_h or self.upperLimit[1] != self.G_h or self.upperLimit[2] != self.R_h:
                changed = True
            
            if(changed):
                # OpenCV uses colours in Blue Green Red order
                self.lowerLimit = np.uint8([self.B_l,self.G_l,self.R_l])
                self.upperLimit = np.uint8([self.B_h,self.G_h,self.R_h])
                # print(self.lowerLimit, self.upperLimit)

                # lowerLimitsParam = self.get_parameter('lower_limits').get_parameter_value()._double_array_value

                lowerLimitsParam = rclpy.parameter.Parameter(
                    'lower_limits',
                    rclpy.Parameter.Type.INTEGER_ARRAY,
                    [self.B_l,self.G_l,self.R_l]
                )
                upperLimitsParam = rclpy.parameter.Parameter(
                    'upper_limits',
                    rclpy.Parameter.Type.INTEGER_ARRAY,
                    [self.B_h,self.G_h,self.R_h]
                )

                all_new_parameters = [lowerLimitsParam, upperLimitsParam]
                self.set_parameters(all_new_parameters)

    def updateTrackbars(self):
        cv2.setTrackbarPos("B_Low", self.windowName, self.lowerLimit[0])
        cv2.setTrackbarPos("G_Low", self.windowName, self.lowerLimit[1])
        cv2.setTrackbarPos("R_Low", self.windowName, self.lowerLimit[2])
        cv2.setTrackbarPos("B_High", self.windowName, self.upperLimit[0])
        cv2.setTrackbarPos("G_High", self.windowName, self.upperLimit[1])
        cv2.setTrackbarPos("R_High", self.windowName, self.upperLimit[2])


    def params_callback(self, paramEvent):
        result = SetParametersResult()
        result.successful = True
        result.reason = "success"
        for param in paramEvent:
            if param.name == 'lower_limits':
                #self.lowerLimit
                if type(param.value) == list:
                    self.lowerLimit = np.uint8(param.value)
                elif type(param.value) == array.array:
                    self.lowerLimit = np.uint8([param.value[0],param.value[1],param.value[2]])
                    #print (self.lowerLimit)
                else:
                    result.successful = False
                    result.reason = 'Unexpected type'
                # self.get_logger().info('%s' % param.name)
                # self.get_logger().info('%s' % param.value)
                # self.get_logger().info('%s' % type(param.value))

                if self.showTrackbars:
                    self.updateTrackbars()

                self.get_logger().info('Updating lower limits to: %s' % self.lowerLimit)

            elif param.name == 'upper_limits':
                #self.lowerLimit
                if type(param.value) == list:
                    self.upperLimit = np.uint8(param.value)
                elif type(param.value) == array.array:
                    self.upperLimit = np.uint8([param.value[0],param.value[1],param.value[2]])
                    #print (self.lowerLimit)
                else:
                    result.successful = False
                    result.reason = 'Unexpected type'
                # self.get_logger().info('%s' % param.name)
                # self.get_logger().info('%s' % param.value)
                # self.get_logger().info('%s' % type(param.value))

                if self.showTrackbars:
                    self.updateTrackbars()

                self.get_logger().info('Updating upper limits to: %s' % self.upperLimit)

            elif param.name == 'image_topic':
                #self.subscription.reset() # function doesn't exist, and destroy completely destroys the variable
                '''WARNING: THIS IS UNSAFE AND LEAVES THE OLD SUBSCRIPTION STILL ACTIVE UNTIL NODE DIES!'''
                self.image_topic = param.value
                self.subscription = self.create_subscription(
                    Image, 
                    self.image_topic, 
                    self.image_callback, 
                    10)
                self.subscription


        return result

        

    def image_callback(self, imgMsg):

        image = self.br.imgmsg_to_cv2(imgMsg)
        
        if self.showTrackbars:
            self.updateLimits()

        # Generate a max that only inlcudes pixels from the image in the specified colour ranges
        mask = cv2.inRange(image, self.lowerLimit, self.upperLimit)
    
        #Remove some of the smaller individual pixels detected as noise
        mask = cv2.erode(mask, None, iterations=2)
        mask = cv2.dilate(mask, None, iterations=2)

        #overlay the mask on the original image
        result = cv2.bitwise_and(image, image, mask=mask)

        # find contours in the mask and initialize the current
        # (x, y) center of the ball
        
        contours = self.grab_contours(mask.copy())
        
        self.x=0.0
        self.y=0.0
        self.radius=0.0

        # only proceed if at least one contour was found
        if len(contours) > 0:
            # find the largest contour in the mask, then use
            # it to compute the minimum enclosing circle and
            # centroid
            c = max(contours, key=cv2.contourArea)
            ((self.x, self.y), self.radius) = cv2.minEnclosingCircle(c)
            
            # only proceed if the radius meets a minimum size
            if self.radius > 10:
                # draw the circle and centroid on the frame
                cv2.circle(result, (int(self.x), int(self.y)), int(self.radius),
                    (0, 255, 255), 2)
                cv2.circle(result, (int(self.x), int(self.y)), 5, (0, 0, 255), -1) # draw small circle at centre

                msg = Point32()
                msg.x = self.x
                msg.y = self.y
                msg.z = self.radius
                self.publisher_.publish(msg)

        

        cv2.imshow(self.windowName, result)
        cv2.waitKey(1)
        


    def nothing(self, x):
        pass


    #based on imutils convenience.py
    #https://github.com/jrosebr1/imutils/blob/master/imutils/convenience.py
    def grab_contours(self, mask):
        
        contours = cv2.findContours(mask, cv2.RETR_EXTERNAL,
            cv2.CHAIN_APPROX_SIMPLE)
        # if the length the contours tuple returned by cv2.findContours
        # is '2' then we are using either OpenCV v2.4, v4-beta, or
        # v4-official
        if len(contours) == 2:
            contours = contours[0]

        # if the length of the contours tuple is '3' then we are using
        # either OpenCV v3, v4-pre, or v4-alpha
        elif len(contours) == 3:
            contours = contours[1]

        # otherwise OpenCV has changed their cv2.findContours return
        # signature yet again and I have no idea WTH is going on
        else:
            raise Exception(("Contours tuple must have length 2 or 3, "
                "otherwise OpenCV changed their cv2.findContours return "
                "signature yet again. Refer to OpenCV's documentation "
                "in that case"))

        # return the actual contours array
        return contours
    
    def timer_callback(self):
        msg = Point32()
        msg.x = self.x
        msg.y = self.y
        self.publisher_.publish(msg)

    

def main(args=None):
   
  # Initialize the rclpy library
  rclpy.init(args=args)
   
  # Create the node
  colDet = ColourDetector()
   
  # Spin the node so the callback function is called.
  rclpy.spin(colDet)
   
  # Destroy the node explicitly
  # (optional - otherwise it will be done automatically
  # when the garbage collector destroys the node object)
  colDet.destroy_node()
   
  # Shutdown the ROS client library for Python
  rclpy.shutdown()
   
if __name__ == '__main__':
  main()
