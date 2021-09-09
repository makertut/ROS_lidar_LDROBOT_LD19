#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>
#include <Wire.h>
#include <RPLidar.h>

// You need to create an driver instance 
RPLidar lidar;

//ROS node handle
ros::NodeHandle  nh;

// ROS Serial Range message definition
sensor_msgs::Range range_msg;

// definition of the ROS publisher for the range data
ros::Publisher pub_range( "range_data", &range_msg);
unsigned long range_timer;

// Frame ID used in the ROS topics
char frameid[] = "/laser_scan_ld19";

void setup()
{
  // Initialize serial connection to display distance readings
   lidar.begin(Serial); // baud rate 230400 
 
  
  /* ROS related */
  nh.initNode();
  nh.advertise(pub_range);
  range_msg.radiation_type = sensor_msgs::Range::INFRARED;
  range_msg.header.frame_id =  frameid;
  range_msg.field_of_view = 0.001;
  range_msg.min_range = 0.01;
  range_msg.max_range = 40.0;
  
}

void loop()
{
  float distance =0; //distance value in mm unit
    float angle   = 0; //anglue value in degree
    bool  startBit= 0; //whether this point is belong to a new scan
    byte  quality =0;
  if (IS_OK(lidar.waitPoint())) {
    float distance = lidar.getCurrentPoint().distance; //distance value in mm unit
    float angle    = lidar.getCurrentPoint().angle; //anglue value in degree
    bool  startBit = lidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
    byte  quality  = lidar.getCurrentPoint().quality; //quality of the current measurement
    
    //perform data processing here... 
    
    
  }

  // read and convert measurements to meters to comply with ROS
  range_msg.range = distance;
  
  range_msg.header.stamp = nh.now();
  pub_range.publish(&range_msg);
  range_timer =  millis();
  nh.spinOnce();  
}
