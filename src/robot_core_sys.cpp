#include <ros/ros.h>
#include "fiducial_msgs/FiducialTransformArray.h"
#include "std_msgs/Float64.h"

#include "robot_msgs/mrkrDist.h"
#include "robot_msgs/usDist.h"

using namespace std;



void arduino_sub();
void position_pub();
void marker_docking();
void core_end();


int marker_num;


ros::ServiceClient *m_client; //marker client
ros::ServiceClient *u_client; //ultrasonic client
ros::ServiceClient *n_client; //navigation client
ros::ServiceClient *b_client; //bluetooth client

robot_msgs::mrkrPose mrkr_srv;
robot_msgs::usPose us_srv;
robot_msgs::navGoal nav_goal_srv;
robot_msgs::blth blth_srv;


int main(int argc, char **argv)
{
	ros::init(argc, argv, "robot_core_sys");
	ros::NodeHandle nh;

	ros::ServiceClient m_client_tmp = nh.serviceClient<robot_msgs::mrkrPose>("mrkr_pose_srvr");
	ros::ServiceClient u_client_tmp = nh.serviceClient<robot_msgs::usPose>("us_pose_srvr");
	ros::ServiceClient n_client_tmp = nh.serviceClient<robot_msgs::navGoal>("nav_goal_srvr");
	ros::ServiceClient b_client_tmp = nh.serviceClient<robot_msgs::blth>("bt_srvr");

	m_client=&m_client_tmp;
	u_client=&u_client_tmp;
	n_client=&n_client_tmp;
	b_client=&b_client_tmp;

	ros::Rate loop_rate(10);
	mod=1;

	ROS_INFO("ROBOT READY!");


	

	while(ros::ok())
	{

		switch(mod)
		{
			case 1 :  	//arduino mod
				arduino_sub();
			break;


			case 2 :  	//nav mod
				position_pub();
			break;


			case 3:		//docking mod
				marker_docking();
			break;


			case 4:		//core end
				core_end();
			break;

			default:

			break;
		}

		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}



void arduino_sub();
{
	if(m_client->call(blth_srv)&&blth_srv.response.m_result)
	{
		ROS_INFO("");
		mod=2;
	}
}


void position_pub();
{

}


void marker_docking();
{

}


void core_end()
{
	ROS_INFO("docking finished!");
}