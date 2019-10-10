#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Empty.h"
#include "sstream"
#include "stdio.h"

int main(int argc, char **argv)
{
	std_msgs::Empty land_cmd;
	
	ros::init(argc, argv, "bebopland_node");
	ros::NodeHandle nh;
	ros::Publisher land_pub=nh.advertise<std_msgs::Empty>("/bebop/land", 1000);
	ros::Publisher land1_pub=nh.advertise<std_msgs::Empty>("/bebop1/land", 1000);
	ros::Publisher land2_pub=nh.advertise<std_msgs::Empty>("/bebop2/land", 1000);
	
	ros::Rate loop_rate(10);

	while(ros::ok()){
		std_msgs::String msg;
		msg.data="緊急停止";
		ROS_DEBUG("%s",msg.data.c_str());
		land_pub.publish(land_cmd);
		land1_pub.publish(land_cmd);
		land2_pub.publish(land_cmd);
		
		ros::spinOnce();
		loop_rate.sleep();
		}
return 0;
}
