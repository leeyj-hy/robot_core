#include "ros/ros.h"
#include "robot_msgs/blth.h"
#include "std_msgs/Int16.h"


void blth_num(const std_msgs::Int16 &received);//sub
bool mrkr_num(robot_msgs::blth::Request &req, 
			 robot_msgs::blth::Response &res);//server

int mrkr_blth_num=0;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "marker_server_bluetooth_sub");
    ros::NodeHandle nh;

    ros::ServiceServer mrkr_srvr= nh.advertiseService("bt_srvr", mrkr_num);

    ros::Subscriber sub = nh.subscribe("/chatter", 10, blth_num);

    ROS_INFO("ready bluetooth server!");

    ros::spin();

    return 0;
}


void blth_num(const std_msgs::Int16 &received)
{
	mrkr_blth_num=received.data;
	ROS_INFO("marker number : %ds",mrkr_blth_num);
	
}

bool mrkr_num(robot_msgs::blth::Request &req, 
			 robot_msgs::blth::Response &res)
{
	if(mrkr_blth_num>=100 &&mrkr_blth_num<120)
	{
		res.mrkr_num=mrkr_blth_num;
		res.blth_ok=true;
	}
		
	else
		res.blth_ok=false;

	return true;
}