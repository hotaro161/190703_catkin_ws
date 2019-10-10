#include "../include/controller/bebop_controller.hpp"
BebopDriver::BebopDriver(ros::NodeHandle &nh){//メンバ関数の定義
    //nh_ = nh;//ノードハンドラnhをnh_にする
    //takeoff_vel_pub_ = nh_.advertise<std_msgs::Empty>("bebop1/takeoff",1);//"bebop/takeoff"にtakeoff_vel_pub_
    //land_vel_pub_ = nh_.advertise<std_msgs::Empty>("bebop1/land",1);//"bebop/landにland_vel_pub_をパブリッシュ"
    //cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("bebop1/cmd_vel",1);//"bebop/cmd_velにcmd_vel_pub_をパブリッシュ"
    takeoff_vel_pub_;
    land_vel_pub_;
    cmd_vel_pub_;
}
void BebopDriver::takeoff(){//BebopDriver内のtakeoff()関数
    takeoff_vel_pub_.publish(takeoff_cmd);//パブリッシャtakeoff_vel_pub_でtakeoff_cmdをパブリッシュ
    takeTime = ros::Time::now();//takeoffした時間をtakeTimeに保存
    while(ros::Time::now() - takeTime <= ros::Duration(5.0)){
    }
}
void BebopDriver::land(){//BebopDriver内のland()関数
    land_vel_pub_.publish(land_cmd);//パブリッシャland_vel_pub_でland_cmdをパブリッシュ
}
//control bebop
void BebopDriver::control(float linearX,float linearY,float linearZ,float angularZ){//BebopDriver内のcontrol()関数
    char cmd[50];//char型のcmd[50]配列を宣言
    base_cmd.linear.x = linearX;//base_cmd.linear.xにlinearXを格納
    base_cmd.linear.y = linearY;
    base_cmd.linear.z = linearZ;
    base_cmd.angular.z = angularZ;//base_cmd.angular.zにangularZを格納
    cmd_vel_pub_.publish(base_cmd);//パブリッシャcmd_vel_pub_でbase_cmdをパブリッシュ
}
//hovering&stop
void BebopDriver::reset(){//BebopDriver内のreset()関数
    base_cmd.linear.x = base_cmd.linear.y = base_cmd.angular.z = 0;//base_cmd内のx, y, yawをすべて0に
    resetTime = ros::Time::now();//reset時間をresetTimeに保存
    while(ros::Time::now() - resetTime <= ros::Duration(3.0)){//whileに入って3秒後にtrueになる
    cmd_vel_pub_.publish(base_cmd);//パブリッシャcmd_vel_pub_でbase_cmdをパブリッシュ
    }
}
