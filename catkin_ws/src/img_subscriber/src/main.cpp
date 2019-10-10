#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <iostream>
#include "../include/img_subscriber/img_data_subpub_node.hpp"
#include "../include/img_subscriber/bebop_controller.hpp"
using namespace cv;
using namespace std;
/***************************main******************************/
int main(int argc, char** argv)
{

    static float cameraAngularY = -60;
    static float cameraAngularZ = 0;
    ros::Time camera_reset_time;
    ros::init (argc, argv, "img_subscriber");
    ROS_INFO("ok");
    ros::NodeHandle nh;
    ImgData imgData(nh);
    BebopDriver driver(nh);
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber image_sub = it.subscribe("bebop1/image_raw", 10,&ImgData::imageCallback, &imgData);
    driver.camera_control(cameraAngularY,cameraAngularZ);
    camera_reset_time = ros::Time::now();
    while(ros::Time::now() - camera_reset_time <= ros::Duration(3.0)){
        driver.camera_control(30,10);
    }
    //waitKey(2000);
    //imgData.markerCreate();
    while(ros::ok()){

        ros::spinOnce();
        driver.camera_control(cameraAngularY,cameraAngularZ);
    }
    return 0;
}
