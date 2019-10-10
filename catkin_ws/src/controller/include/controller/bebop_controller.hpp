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
class BebopDriver{//BebopDriverクラスを宣言
public:
/*******************************publisher ros*******************************/
    ros::NodeHandle nh_;//ノードハンドラを宣言
    ros::Publisher cmd_vel_pub_;//cmd_velのパブリッシャを作成
    ros::Publisher takeoff_vel_pub_;//takeoffのパブリッシャを作成
    ros::Publisher land_vel_pub_;//landのパブリッシャを作成
/***********************************time***********************************/
    ros::Time takeTime;
    ros::Time landTime;
    ros::Time resetTime;
public:
/********************************message**********************************/
    geometry_msgs::Twist base_cmd;//geometry_msgs型でcmd_velにパブリッシュする用の変数を宣言
    std_msgs::Empty takeoff_cmd;//std_msgs型でtakeoff用の変数を宣言
    std_msgs::Empty land_cmd;//std_msgs型でland_cmd用の変数を宣言
/*********************************function*********************************/
    BebopDriver(ros::NodeHandle &nh);
    void takeoff();//関数takeoff()を宣言
    void land();//関数land()を宣言
    //control bebop
    void control(float linearX,float linearY,float linearZ,float angularZ);//関数control()を宣言
    //hovering&stop
    void reset();//関数reset()を宣言
};
