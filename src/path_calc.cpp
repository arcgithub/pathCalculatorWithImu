#include "ros/ros.h"
#include <iostream>
#include "geometry_msgs/Vector3.h"
#include "sensor_msgs/Imu.h"
#include <cmath>


float delta_T = 0.01;
float initial[3];
bool isInitial = true;

float distance_x = 0.0;
float distance_y = 0.0;
float distance_z = 0.0;

ros::Subscriber sub_weg;
ros::Publisher pub_weg;

void pathCalculator(const sensor_msgs::Imu::ConstPtr & datum);

int main(int argc, char **argv)
{
	
	ros::init(argc, argv, "path_Subs");
	ros::NodeHandle node_weg;

	sub_weg = node_weg.subscribe("/imu0", 1, pathCalculator);
	pub_weg = node_weg.advertise<geometry_msgs::Vector3>("/pathcalculator/weg", 1);

	ros::spin();

	return 0;
}


void pathCalculator(const sensor_msgs::Imu::ConstPtr & datum){

	if (isInitial == true)
	{
		initial[0] = datum->linear_acceleration.x;
		initial[1] = datum->linear_acceleration.y;
		initial[2] = datum->linear_acceleration.z;
		isInitial = false;
 	}

 	// Auslesen der IMU Daten
	float acc_z = datum->linear_acceleration.z - initial[2];
	float acc_y = datum->linear_acceleration.y - initial[1];
	float acc_x = datum->linear_acceleration.x - initial[0];

	// float orientation_x = datum-> orientation.x;
	// float orientation_y = datum-> orientation.y;
	// float orientation_z = datum-> orientation.z;

	// float ang_x = datum->angular_acceleration.x;
	// float ang_y = datum->angular_acceleration.y;
	// float ang_z = datum->angular_acceleration.z;

	//Berechnung der zurückgelegten Distanzen --> even. Trafo in unser Koordssystem
	distance_x += 0.5*acc_x*delta_T*delta_T;
	distance_y += 0.5*acc_y*delta_T*delta_T;
	distance_z += 0.5*acc_z*delta_T*delta_T;

	geometry_msgs::Vector3 weg;
	weg.x = distance_x;
	weg.y = distance_y;
	weg.z = distance_z;
	pub_weg.publish(weg);

	//Warten
 	ros::Duration waitingDuration(delta_T);
 	waitingDuration.sleep();

	//std::cout << acc_x << " " << acc_y << " " << acc_z << std::endl;
	// std::cout << orientation_x<< " " << orientation_y << " " << orientation_z << std::endl;
	// std::cout << ang_x << " " << ang_y << " " << ang_z << std::endl;
	// std::cout << initial[0] << " " << initial[1] << " " << initial[2] << std::endl;
}