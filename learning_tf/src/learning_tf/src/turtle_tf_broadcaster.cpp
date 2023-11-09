#include "ros/ros.h"
#include "tf/transform_broadcaster.h"
#include "turtlesim/Pose.h"

std::string turtle_name;

void poseCallback(const turtlesim::PoseConstPtr& msg)
{
    static tf::TransformBroadcaster br;
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(msg->x, msg->y, 0.0));  // 平移变换
    tf::Quaternion q;
    q.setRPY(0, 0, msg->theta);
    transform.setRotation(q);  // 旋转变换
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", turtle_name));  // 发布到tf树 源坐标系 -> 目标坐标系
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "my_tf_broadcaster");
    if (argc != 2)
    {
        ROS_ERROR("usage: rosrun learning_tf ${turtle_name}");
        return 1;
    }
    turtle_name = argv[1];
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe(turtle_name + "/pose", 10, &poseCallback);
    ros::spin();

    return 0;
}