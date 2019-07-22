#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/aruco.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <std_msgs/Empty.h>
#include <sys/times.h>
#include <time.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include "../include/bebop_teleop/bebop_controller.hpp"
using namespace std;
using namespace cv;
#define speed 0.175
/*********************************************class publisher and subscriber**********************************************/
class ImgDataSub{
private:
/**************opencv**************/
public:
    Mat image;
    ImgDataSub();
    void imageCallback(const sensor_msgs::ImageConstPtr& msg);
};
/***************************constructor********************************/
ImgDataSub::ImgDataSub(){

}
/***********************get image frome bebop***************************/
void ImgDataSub::imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    try {
	    image = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8)->image;
    }
    catch (cv_bridge::Exception& e) {
	    ROS_ERROR("cv_bridge exception: %s", e.what());
    }
    const int height = image.rows;
    const int width = image.cols;
    resize(image,image,cv::Size(),0.2,0.2);
    cv::imshow("marker_detection", image);
   //cv::waitKey(1);
}
int main(int argc,char **argv){
    geometry_msgs::Twist bebop_cmd;
    geometry_msgs::Twist bebop_camera;
    ros::init(argc,argv,"bebop_driver");
    ros::NodeHandle nh;
    ImgDataSub imgSub;
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber image_sub = it.subscribe("image_raw",10,&ImgDataSub::imageCallback,&imgSub);
    BebopDriver driver(nh);
    char quit;
    static int count = 0;
    static int flag = 0;
    while(quit != '@'){
        char ch = waitKey(1);
        if(ch == -1){
            count ++;
            ch = quit;
        }else
            count = 0;
        quit = ch;
        //cout << count << endl;
        bebop_cmd.linear.x = bebop_cmd.linear.y = bebop_cmd.linear.z = bebop_cmd.angular.z = 0;
        if(flag == 0){
            if(ch == 'w')
                bebop_cmd.linear.x = speed;
            else if(ch == 's')
                bebop_cmd.linear.x = -speed;
            else if(ch == 'a')
                bebop_cmd.linear.y = speed;
            else if(ch == 'd')
                bebop_cmd.linear.y = -speed;
            else if(ch == 'r')
                bebop_cmd.linear.z = speed;
            else if(ch == 'f')
                bebop_cmd.linear.z = -speed;
            else if(ch == 'q')
                bebop_cmd.angular.z = speed;
            else if(ch == 'e')
                bebop_cmd.angular.z = -speed;
            else if(ch == 't'){
                driver.takeoff();
            }else if(ch == 'l'){
                driver.land();
            }else if(ch == 'm'){
                cout << "please input paramerters of camera  angular.z next angular.y" <<endl;
                //flag = 1;
                //quit = -1;
            }
        }/*else if(flag == 1){
            quit = -1;
            if(ch == 'w'){
                bebop_camera.angular.y += 5;
            }else if(ch == 's'){
                bebop_camera.angular.y -= 5;
            }else if(ch == 'a'){
                bebop_camera.angular.z -= 5;
            }else if(ch == 'd'){
                bebop_camera.angular.z += 5;
            }else if(ch == 'm'){
                quit = -1;
               i flag == 0;
            }
            if(bebop_camera.angular.y > 80){
                cout << "limit angular" << endl;
                bebop_camera.angular.y = 80;
            }
            if(bebop_camera.angular.y < -80){
                cout << "limit angular" << endl;
                bebop_camera.angular.y = -80;
            }
            if(bebop_camera.angular.z > 50){
                cout << "limit angular" << endl;
                bebop_camera.angular.z = 50;
            }
            if(bebop_camera.angular.z < -50){
                cout << "limit angular" << endl;
                bebop_camera.angular.z = -50;
            }
        }*/
        if(count >= 50){
            count = 0;
            bebop_cmd.linear.x = bebop_cmd.linear.y = bebop_cmd.linear.z = bebop_cmd.angular.z = 0;
            quit = -1;
        }
        cout << bebop_cmd.linear.x<<"," << bebop_cmd.linear.y <<","<< bebop_cmd.linear.z <<","<< bebop_cmd.angular.z << endl;
        driver.control(bebop_cmd.linear.x,bebop_cmd.linear.y,bebop_cmd.linear.z,bebop_cmd.angular.z);
        //driver.camera_control(bebop_camera.angular.y,bebop_camera.angular.z);
        ros::spinOnce();
    }
    //driver.land();
    return 0;
}
