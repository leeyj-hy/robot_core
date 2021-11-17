#include <ros/ros.h>
#include "fiducial_msgs/FiducialTransformArray.h"
#include "std_msgs/Float64.h"

#include "robot_msgs/docking.h"
#include "robot_msgs/navGoal.h"
#include "robot_msgs/blth.h"


using namespace std;



void blth_mode();
void nav_mode();
void docking_mode();
void core_end();


int marker_num;
int mod=0;


ros::ServiceClient *d_client; //docking client
ros::ServiceClient *n_client; //navigation client
ros::ServiceClient *b_client; //bluetooth client

robot_msgs::docking dock_srv;
robot_msgs::navGoal nav_srv;
robot_msgs::blth blth_srv;


int main(int argc, char **argv)
{
	ros::init(argc, argv, "robot_core_sys");
	ros::NodeHandle nh;

	ros::ServiceClient d_client_tmp = nh.serviceClient<robot_msgs::docking>("docking_srvr");
	ros::ServiceClient n_client_tmp = nh.serviceClient<robot_msgs::navGoal>("nav_goal_srvr");
	ros::ServiceClient b_client_tmp = nh.serviceClient<robot_msgs::blth>("bt_srvr");

	d_client=&d_client_tmp;
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
				blth_mode();
				ROS_INFO("blth_mode");
			break;


			case 2 :  	//nav mod
				nav_mode();
				ROS_INFO("nav_mode");
			break;


			case 3:		//docking mod
				docking_mode();
				ROS_INFO("docking_mode");
			break;


			case 4:		//core end
				core_end();
				ROS_INFO("core_end");
			break;

			default:

			break;
		}

		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}



void blth_mode()
{
	if(b_client->call(blth_srv)&&blth_srv.response.blth_ok)
	{
		marker_num=blth_srv.response.mrkr_num;

		ROS_INFO("");
		mod=2;
	}
}


void nav_mode()
{
	if(n_client->call(nav_srv)&&nav_srv.response.nav_ok)
	{
		ROS_INFO("");
		mod=3;
	}
}


void docking_mode()
{
	if(d_client->call(dock_srv)&&dock_srv.response.dock_ok)
	{
		ROS_INFO("");
		mod=4;
	}
}


void core_end()
{
	ROS_INFO("docking finished!");
}