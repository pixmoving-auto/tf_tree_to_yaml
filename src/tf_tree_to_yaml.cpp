#include "tf_tree_to_yaml/tf_tree_to_yaml.hpp"


TfTreeToYaml::TfTreeToYaml(/* args */) : Node("tf_tree_to_yaml_node")
{
    // ros param
    parent_frame_ = this->declare_parameter("parent_frame", "sensor_top");

    auto child_frame = this->declare_parameter("child_frame", std::vector<std::string>{"os_lidar_fl", "os_lidar_fr", "os_lidar_rl", "os_lidar_rr"});
    std::vector<std::string> child_frame_v(child_frame.begin(), child_frame.end());
    child_frame_ = child_frame_v;

    output_yaml_file_ = this->declare_parameter("output_yaml_file", "tf_tree.yaml");

    // tf2 echo
    tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
    tf2_listener_ = std::make_unique<tf2_ros::TransformListener>(*tf_buffer_);
    // Call on_timer function every second
    timer_ = this->create_wall_timer(
        1s, std::bind(&TfTreeToYaml::on_timer, this));
}

void TfTreeToYaml::on_timer()
{
    YAML::Node root;
    geometry_msgs::msg::TransformStamped t;

    for(auto item:child_frame_){

        try {
            t = tf_buffer_->lookupTransform( parent_frame_, item, tf2::TimePointZero);
        } catch (const tf2::TransformException & ex) {
            RCLCPP_ERROR(
            this->get_logger(), "Could not transform %s to %s: %s",
            parent_frame_.c_str(), item.c_str(), ex.what());
            return;
        }

        // 四元数转欧拉角[弧度]
        tf2::Quaternion quaternion;
        tf2::fromMsg(t.transform.rotation, quaternion);
        tf2::Matrix3x3 matrix(quaternion);
        double roll, pitch, yaw;
        matrix.getRPY(roll, pitch, yaw);

        root[parent_frame_][item]["x"] =  round_up_to_five(t.transform.translation.x);
        root[parent_frame_][item]["y"] =  round_up_to_five(t.transform.translation.y);
        root[parent_frame_][item]["z"] =  round_up_to_five(t.transform.translation.z);

        root[parent_frame_][item]["roll"] =  round_up_to_five(roll);
        root[parent_frame_][item]["pitch"] =  round_up_to_five(pitch);
        root[parent_frame_][item]["yaw"] =  round_up_to_five(yaw);
    }

    std::ofstream fout(output_yaml_file_.c_str());
    YAML::Emitter emitter;
    emitter << root;
    fout << emitter.c_str();
    fout.close();
    rclcpp::shutdown();
}

std::string TfTreeToYaml::round_up_to_five(double number)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(3) << number;
    return stream.str();
}


