cmake_minimum_required(VERSION 3.5)
project(lab1)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(ackermann_msgs REQUIRED)
find_package(std_msgs REQUIRED)

# Include Cpp "include" directory
include_directories(include)

# Create Cpp executables
add_executable(cpp_executable src/test.cpp)
add_executable(talker src/talker.cpp)
add_executable(relay src/relay.cpp)
ament_target_dependencies(cpp_executable rclcpp)
ament_target_dependencies(talker rclcpp)
ament_target_dependencies(relay rclcpp)
ament_target_dependencies(relay ackermann_msgs)
ament_target_dependencies(talker ackermann_msgs)

# Install Cpp executables
install(TARGETS
  cpp_executable
  talker
  relay
  DESTINATION lib/${PROJECT_NAME}
)

# Install Python modules
ament_python_install_package(${PROJECT_NAME})

# Install Python executables
install(PROGRAMS
  scripts/py_node.py
  DESTINATION lib/${PROJECT_NAME}
)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
