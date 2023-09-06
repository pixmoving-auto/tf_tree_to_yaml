#ifndef _tf_tree_to_yaml_H
#define _tf_tree_to_yaml_H 1
#include <iostream>
#include <iomanip>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <vector>

// ROS
#include <rclcpp/rclcpp.hpp>
#include "geometry_msgs/msg/transform_stamped.hpp"

// tf listener
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"
#include <tf2/utils.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>



using namespace std::chrono_literals;

namespace OutputYamlTpe{
    const std::string robobus_muti_lidar = "robobus-sensor_top2muti_lidar";
    const std::string robobus_lidar_camera_top = "robobus-sensor_top2camera_top";
    const std::string robobus_lidar_camera_front = "robobus-sensor_top2camera_front";
};

struct TransformPose{

};

class TfTreeToYaml : public rclcpp::Node
{
private:
    // tf2 listener
    std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
    std::unique_ptr<tf2_ros::TransformListener> tf2_listener_{nullptr};

    // timer
    rclcpp::TimerBase::SharedPtr timer_{nullptr};
    
    // frame
    std::string parent_frame_;
    std::vector<std::string> child_frame_;
    std::string output_yaml_file_;

public:
    TfTreeToYaml(/* args */);
    void on_timer();
    std::string round_up_to_five(double number);
    
};



#endif