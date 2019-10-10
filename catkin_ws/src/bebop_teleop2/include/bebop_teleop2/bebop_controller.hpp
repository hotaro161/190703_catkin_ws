#include <ros/ros.h>
#include <stdio.h>
#include <iostream>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <std_msgs/Empty.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>
using namespace std;
/*******************************bebop driver class****************************/
class BebopDriver{
private:
/*******************************publisher ros*******************************/
    ros::NodeHandle nh_;
    ros::Publisher cmd_vel_pub_;
    ros::Publisher takeoff_vel_pub_;
    ros::Publisher land_vel_pub_;
    ros::Publisher camera_pra_pub_;
    ros::Publisher identification_pub_;
/***********************************time***********************************/
    ros::Time takeTime;
    ros::Time landTime;
    ros::Time resetTime;
public:
/********************************message**********************************/
    geometry_msgs::Twist base_cmd;
    geometry_msgs::Twist camera_cmd;
    geometry_msgs::Twist velocity_cmd;
    std_msgs::Empty takeoff_cmd;
    std_msgs::Empty land_cmd;
/*********************************function*********************************/
    BebopDriver(ros::NodeHandle &nh);
    void takeoff();
    void land();
    //control bebop
    void control(float linearX,float linearY,float linearZ,float angularZ);
    void camera_control(float angualrY,float angularZ);
    void identification();
    //hovering&stop
    void reset();
};
