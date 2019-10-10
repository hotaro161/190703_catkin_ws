#include "../include/cv_test/bebop_controller.hpp"
BebopDriver::BebopDriver(ros::NodeHandle &nh){
    nh_ = nh;
    takeoff_vel_pub_ = nh_.advertise<std_msgs::Empty>("bebop2/takeoff",1);
    land_vel_pub_ = nh_.advertise<std_msgs::Empty>("bebop2/land",1);
    cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("bebop2/cmd_vel",1);
    camera_pra_pub_ = nh_.advertise<geometry_msgs::Twist>("bebop2/camera_control",1);
}
void BebopDriver::takeoff(){
    takeoff_vel_pub_.publish(takeoff_cmd);
}
void BebopDriver::land(){
    land_vel_pub_.publish(land_cmd);
}
//control bebop
void BebopDriver::control(float linearX,float linearY,float linearZ,float angularZ){
    char cmd[50];
    base_cmd.linear.x = linearX;
    base_cmd.linear.y = linearY;
    base_cmd.linear.z = linearZ;
    base_cmd.angular.z = angularZ;
    cmd_vel_pub_.publish(base_cmd);
}
void BebopDriver::camera_control(float angularY,float angularZ){
    camera_cmd.angular.y = angularY;
    camera_cmd.angular.z = angularZ;
    camera_pra_pub_.publish(camera_cmd);
}
//hovering&stop
void BebopDriver::reset(){
    base_cmd.linear.x = base_cmd.linear.y = base_cmd.angular.z = 0;
    resetTime = ros::Time::now();
    while(ros::Time::now() - resetTime <= ros::Duration(3.0)){
        cmd_vel_pub_.publish(base_cmd);
    }
}
