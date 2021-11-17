#include <ros/ros.h>
#include "fiducial_msgs/FiducialTransformArray.h"
#include "geometry_msgs/Twist.h"
#include "robot_msgs/docking.h"

void marker_3d_pose(const fiducial_msgs::FiducialTransformArray &msg);
bool docking_seq(robot_msgs::usDist::Request &req, 
			 	robot_msgs::usDist::Response &res);

ros::Publisher* robot_mv

float mrkr_z_dist;

int main (int argc, char **argv)
{

	ros::init(argc, argv, "docking_sub_robotMv_srv");
	ros::NodeHandle nh;

	ros::ServiceServer docking_ok= nh.advertiseService("docking_srv", docking_seq);
	ros::Publisher robot_mv_tmp = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
	robot_mv= &robot_mv_tmp;

	ros::Subscriber mrkr_sub = nh.subscribe("/fiducial_transforms", 10, marker_3d_pose);

	ros::Rate loop_rate(10);

	while(ros::ok())
	{

		ros::spinOnce();
		loop_rate.sleep();

	}

}



void marker_3d_pose(const fiducial_msgs::FiducialTransformArray &msg)
{
	for(int i=0; i<msg.transforms.size() ; i++)
  	{
  		mrkr_z_dist=msg.transforms[i].transform.translation.z;

	  	ROS_INFO("%d", i);
	    ROS_INFO("TRANS_Z : %f", mrkr_z_dist);
	    
	}
}


bool docking_seq(robot_msgs::usDist::Request &req, 
			 robot_msgs::usDist::Response &res)
{

	geometry_msgs::Twist robot_move;

			if(mrkr_z_dist> 0.5)
			{
				robot_move.linear.x = 0.1;
			}
			else
			{
				robot_move.linear.x = 0;
			}

	    chatter_pub->publish(robot_move);
}