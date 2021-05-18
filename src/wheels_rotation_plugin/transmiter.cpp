#include "ros/ros.h"
#include "sensor_msgs/JointState.h"



int main(int argc, char **argv)
{
  std::printf("%d",argc);
  ros::init(argc, argv, "talker");
  std::string nodeName="Informer";
  if(argc==2)
  {
    nodeName = argv[1];
  }

  ros::NodeHandle n;


  ros::Publisher informer_pub = n.advertise<sensor_msgs::JointState>(nodeName, 1000);
  float x=0;
  ros::Rate loop_rate(8);

  while (ros::ok())
  {
 
    sensor_msgs::JointState msg;
   
    msg.position.clear();
    msg.name.clear();
    msg.name.push_back("test1");
    msg.name.push_back("wheel1");
    msg.name.push_back("wheel2");
    msg.name.push_back("te2");
    msg.name.push_back("wheel3");
    msg.name.push_back("wheel4");
    msg.name.push_back("tes2");
    msg.position.push_back(0);
    msg.position.push_back(x);
    msg.position.push_back(x+0.15);
    msg.position.push_back(0);
    msg.position.push_back(x+0.25);
    msg.position.push_back(x+0.45);
    msg.position.push_back(0);
    ROS_INFO("%f, %f, %f, %f", msg.position[1], msg.position[2], msg.position[4], msg.position[5]);

    informer_pub.publish(msg);

    x+=0.087;
    if(x>6.28)
    {
      x=0;
    }
    
    ros::spinOnce();

    loop_rate.sleep();
  }


  return 0;
}