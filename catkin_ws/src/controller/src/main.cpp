#include <ros/ros.h>
#include <stdio.h>
#include <iostream>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <std_msgs/Empty.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>
#include "../include/controller/matlab_transmission.hpp"
#include "../include/controller/bebop_controller.hpp"
int main(int argc,char **argv){
    ros::init(argc,argv,"bebop_driver");//ノード名"bebop_driverで"初期化
    ros::NodeHandle nh;//ノードハンドラnhの宣言
    MatlabSub matsub1;//MatlabSubのオブジェクトmatsub1を作成
    MatlabSub matsub2;//MatlabSubのオブジェクトmatsub2を作成
    ros::Subscriber sub1 = nh.subscribe("bebopData1",10,&MatlabSub::callBack,&matsub1);//サブスクライバsubを作成し, MatlabSubクラスのcallback関数を呼び出し, "bebopData"トピックとしてサブスクライブ
    ros::Subscriber sub2 = nh.subscribe("bebopData2",10,&MatlabSub::callBack,&matsub2);//サブスクライバsubを作成し, MatlabSubクラスのcallback関数を呼び出し, "bebopData"トピックとしてサブスクライブ
    ros::Time start = ros::Time::now();//現在時間をstartに格納
    cout << "program start" << endl;//program startを表示
    BebopDriver driver1(nh);//BebopDriverのオブジェクトdriver1(nh)を作成
    BebopDriver driver2(nh);//BebopDriverのオブジェクトdriver2(nh)を作成
    //ドローン1の送信先のトピックの定義, パブリッシャの定義
    driver1.takeoff_vel_pub_ = nh.advertise<std_msgs::Empty>("bebop1/takeoff",1);//"bebop/takeoffにtakeoff_vel_pub_を定義
    driver1.land_vel_pub_ = nh.advertise<std_msgs::Empty>("bebop1/land",1);//"bebop/landにland_vel_pub_を定義
    driver1.cmd_vel_pub_ = nh.advertise<geometry_msgs::Twist>("bebop1/cmd_vel",1);//"bebop/cmd_velにcmd_vel_pub_を定義
    //ドローン2の送信先のトピックの定義, パブリッシャの定義
    driver2.takeoff_vel_pub_ = nh.advertise<std_msgs::Empty>("bebop2/takeoff",1);//"bebop/takeoffにtakeoff_vel_pub_を定義
    driver2.land_vel_pub_ = nh.advertise<std_msgs::Empty>("bebop2/land",1);//"bebop/landにland_vel_pub_を定義
    driver2.cmd_vel_pub_ = nh.advertise<geometry_msgs::Twist>("bebop2/cmd_vel",1);//"bebop/cmd_velにcmd_vel_pub_を定義
/*----------------------------------------------------------------------------------------------------------------------------------------------------*/
    driver1.reset();//driver1内のreset関数を実行
    driver2.reset();//driver2内のreset関数を実行
    //driver1.takeoff();
    start = ros::Time::now();//startに現在時間に格納
    int count = 0;//int型の変数count=0を宣言
    while(ros::ok()){//ノードが死ぬまで実行
        ros::spinOnce();//繰り返し
        if(matsub1.command.angular.y == 1){//matsub.command.angular.y==1なら条件に入る
            driver1.control(matsub1.command.linear.x,matsub1.command.linear.y,matsub1.command.linear.z,matsub1.command.angular.z);//driver1内のcontrol関数にmatlabから送信された数値を格納
        }if(matsub1.command.angular.y == -1){//-1のとき
            driver1.control(0,0,0,0);//control関数内の全ての数値を0に
        }if(matsub2.command.angular.y == 1){//-1のとき
            driver2.control(matsub2.command.linear.x,matsub2.command.linear.y,matsub2.command.linear.z,matsub2.command.angular.z);//driver2内のcontrol関数にmatlabから送信された数値を格納
        }if(matsub2.command.angular.y == -1){//-1のとき
            driver2.control(0,0,0,0);//control関数内の全ての数値を0に
        }
        cout << "ドローン1" << endl << "angular_y="<<matsub1.command.angular.y << endl;//matlab内のbebop1のangular.yを表示
        cout << "ドローン2" << endl << "angular_y="<<matsub2.command.angular.y << endl;//matlab内のbebop2のangular.yを表示
    }
    driver1.reset();//reset
    driver2.reset();//reset
    //driver1.land();
    return 0;
}
