#include <ros/ros.h>
#include "move_base_msgs/MoveBaseResult.h"
#include "move_base_msgs/MoveBaseActionGoal.h"
#include "move_base_msgs/MoveBaseActionResult.h"
#include "actionlib_msgs/GoalStatus.h"
#include "robot_msgs/navGoal.h"

void nav_result(const move_base_msgs::MoveBaseActionResult &is_nav_ok );
bool when_nav_call(robot_msgs::navGoal::Request &req, 
			 	  robot_msgs::navGoal::Response &res);
int i=6;

ros::Publisher* goal_pose;
int nav_status=0;

int main(int argc, char** argv)
{

	ros:: init(argc, argv, "pub_node");
	ros::NodeHandle nh;

	ros::Publisher goal_pose_tmp = nh.advertise<move_base_msgs::MoveBaseActionGoal>("/move_base/goal", 10);
	ros::Subscriber result_sub = nh.subscribe("/move_base_msgs/MoveBaseResult", 10, nav_result);
	ros::ServiceServer nav_srv = nh.advertiseService("nav_goal_srvr", when_nav_call);

	goal_pose= &goal_pose_tmp;
	ros::Rate loop_rate(1);






	ROS_INFO("nav_ready!");

	while(ros::ok())
	{	
		
		ros::spinOnce();
		loop_rate.sleep();
	}


}



bool when_nav_call(robot_msgs::navGoal::Request &req, 
			 	  robot_msgs::navGoal::Response &res)
{

	move_base_msgs::MoveBaseActionGoal goal_pose_yj;

	goal_pose_yj.goal.target_pose.header.frame_id="map";
	goal_pose_yj.goal.target_pose.pose.position.x=3.9;
	goal_pose_yj.goal.target_pose.pose.position.y=5.89;
	goal_pose_yj.goal.target_pose.pose.orientation.z=0.1131;
	goal_pose_yj.goal.target_pose.pose.orientation.w=1;


	i-=1;

		if(i>0)
		{
			ROS_INFO("publish start in %d sec", i);
		}

		else if(i==0)
		{
			goal_pose->publish(goal_pose_yj);

			ROS_INFO("goal_pose published!");
		}

		else
		{
			ROS_INFO("published!");
			if(nav_status==3)
			{
				res.nav_ok=true;
				return true;
			}
		}
}

void nav_result(const move_base_msgs::MoveBaseActionResult &is_nav_ok )
{
	nav_status = is_nav_ok.status.status;

	
}