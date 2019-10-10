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
/************************matlab subscriber class********************/
class MatlabSub{
private:
    void convert_velocity_to_param();//convert_velocity_to_param()関数を宣言
public:
    geometry_msgs::Twist velocity_param;//geometry_msgs型のvelocity_paramを宣言
    geometry_msgs::Twist command;//geometry_msgs型のcommandを宣言
    MatlabSub();//MatlabSub()クラスのコンストラクタを宣言
    void callBack(const geometry_msgs::Twist& msg);//callback関数を宣言
};
