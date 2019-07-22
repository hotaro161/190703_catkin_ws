#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>

void image_recieved(const sensor_msgs::Image &image)
{
    ROS_INFO("width: %d, height: %d, encoding: %s, is_bigendian: %d, step: %d",
             image.height, image.width, image.encoding.c_str(),
             image.is_bigendian, image.step);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_subscriber_node");

    ros::NodeHandle node_handler;
    ros::Subscriber sub = node_handler.subscribe("/usb_cam/image_raw", 10, image_recieved);

    ros::spin();
    return 0;
}

