#include "tf_tree_to_yaml/tf_tree_to_yaml.hpp"

int main(int argc, char ** argv)
{ 
  setlocale(LC_ALL,"");
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TfTreeToYaml>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}