#include<ros/ros.h>
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
#include <curses.h>
#include <ncurses.h>
using namespace std;
#define speed 0.175



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


int main(int argc,char **argv){
  geometry_msgs::Twist bebop_cmd;
  geometry_msgs::Twist bebop_camera;
  ros::init(argc,argv,"bebop_driver");
  ros::NodeHandle nh;
  BebopDriver driver(nh);
  static int count = 0;
  static int flag = 0;
  char key;

  while(ros::ok()){

    //キーボードの入力内容をkeyに入れる動作
    cin >> key;
    cout << key << endl;

    if(key == 'w')
        bebop_cmd.linear.x = speed;
    else if(key== 's')
        bebop_cmd.linear.x = -speed;
    else if(key == 'a')
        bebop_cmd.linear.y = speed;
    else if(key == 'd')
        bebop_cmd.linear.y = -speed;
    else if(key == 'r')
        bebop_cmd.linear.z = speed;
    else if(key == 'f')
        bebop_cmd.linear.z = -speed;
    else if(key == 'q')
        bebop_cmd.angular.z = speed;
    else if(key == 'e')
        bebop_cmd.angular.z = -speed;
    else if(key == 't'){
        driver.takeoff();
    }else if(key == 'l'){
        driver.land();
    }else if(key == 'm'){
        cout << "please input paramerters of camera  angular.z next angular.y" <<endl;
    }else{
        bebop_cmd.linear.x = bebop_cmd.linear.y = bebop_cmd.linear.z = bebop_cmd.angular.z = 0;
    }

    cout << bebop_cmd.linear.x<<"," << bebop_cmd.linear.y <<","<< bebop_cmd.linear.z <<","<< bebop_cmd.angular.z << endl;
    driver.control(bebop_cmd.linear.x,bebop_cmd.linear.y,bebop_cmd.linear.z,bebop_cmd.angular.z);

    ros::spinOnce();
  }
  return 0;
}
