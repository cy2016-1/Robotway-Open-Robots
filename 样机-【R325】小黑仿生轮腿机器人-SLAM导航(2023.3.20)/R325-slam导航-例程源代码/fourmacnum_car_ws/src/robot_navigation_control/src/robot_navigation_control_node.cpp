//Receive last position of the ant
//Receive target position of the ant
//Publish The target state of each joint
//Broadcaster odom information
#include <string>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <nav_msgs/Odometry.h>

//robot state
float wheel_p[4] = {0,0,0,0};
float wheel_v[4] = {0,0,0,0};
float rate = 30;
float v_p_rate = 6.282/0.2/rate;

void callback(const nav_msgs::Odometry odom)
{
	ROS_INFO("I heard: [%d]", odom.header.seq);
	wheel_v[0] = (odom.twist.twist.linear.x - odom.twist.twist.linear.y - odom.twist.twist.angular.z)*v_p_rate;
	wheel_v[1] = (odom.twist.twist.linear.x + odom.twist.twist.linear.y + odom.twist.twist.angular.z)*v_p_rate;
	wheel_v[2] = (odom.twist.twist.linear.x + odom.twist.twist.linear.y - odom.twist.twist.angular.z)*v_p_rate;
	wheel_v[3] = (odom.twist.twist.linear.x - odom.twist.twist.linear.y + odom.twist.twist.angular.z)*v_p_rate;
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
    ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
    ros::Subscriber sub_cur = n.subscribe("/odom", 1000, callback);
    ros::Rate loop_rate(rate);
    //message declarations
    sensor_msgs::JointState joint_state;

    while (ros::ok()) 
    {
		ros::spinOnce();
		//update joint_state
		joint_state.header.stamp = ros::Time::now();
		joint_state.name.resize(4);
		joint_state.position.resize(4);
		joint_state.name[0] = "base_link_to_wheel1";
		joint_state.name[1] = "base_link_to_wheel2";
		joint_state.name[2] = "base_link_to_wheel3";
		joint_state.name[3] = "base_link_to_wheel4";
		wheel_p[0] += wheel_v[0];
		wheel_p[1] += wheel_v[1];
		wheel_p[2] += wheel_v[2];
		wheel_p[3] += wheel_v[3];
		joint_state.position[0] = wheel_p[0];
		joint_state.position[1] = wheel_p[1];
		joint_state.position[2] = wheel_p[2];
		joint_state.position[3] = wheel_p[3];
		//send the joint state and transform
		joint_pub.publish(joint_state);
		// This will adjust as needed per iteration
		loop_rate.sleep();
    }
    return 0;
}
