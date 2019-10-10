#include "../include/controller/matlab_transmission.hpp"
MatlabSub::MatlabSub(){//初期化
        command.linear.x = command.linear.y = command.linear.z = command.angular.z = 0;//command.linear.x = command.linear.y = command.linear.z = command.angular.z = 0で初期化
};
void MatlabSub::callBack(const geometry_msgs::Twist& msg){//MatlabSubクラス内のcallBack関数
	cout << msg.linear.x <<","<< msg.linear.y <<","<<msg.linear.z <<","<<msg.angular.z<< endl;//msg.linear.xなどを表示
	this->command.linear.x = this->command.linear.y = this->command.linear.z = this->command.angular.z = 0;//MatlabSubにthisポインタでアクセスし, 格納
	this->command.linear.x = msg.linear.x;//command.linear.xにmsg.linear.xを格納
	this->command.linear.y = msg.linear.y;
	this->command.linear.z = msg.linear.z;
	this->command.angular.z = msg.angular.z;
    this->command.angular.y = msg.angular.y;
    convert_velocity_to_param();//conver_velocity_to_param関数を呼び出す
}

void MatlabSub::convert_velocity_to_param(){
    //convert from x_velocity to vx_param
    if(command.linear.x >= 0){
       // command.linear.x =
    }else if(command.linear.x < 0){
        //command.linear.x = 
    }
    //convert from y_velocity to vy_param
    //convert from z_velocity to vz_param
    if(command.linear.z >= 0){
        //command.linear.z =
    }else if(command.linear.z < 0){
        //command.linear.z =
    }
    //convert from z_rotation to rz_param
}
