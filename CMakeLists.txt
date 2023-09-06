cmake_minimum_required(VERSION 3.8)
project(tf_tree_to_yaml)

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(yaml-cpp REQUIRED)

ament_auto_add_executable(${PROJECT_NAME}_node
  src/tf_tree_to_yaml.cpp
  src/tf_tree_to_yaml_node.cpp
)

target_link_libraries(${PROJECT_NAME}_node  ${YAML_CPP_LIBRARIES})

# install
ament_auto_package(
  INSTALL_TO_SHARE
  launch
)