# 安装插件ROS（在ROS安装的机器）,catkin_tool（vscode安装的机器）
# 使用vscode打开本目录
# 别忘了执行 source ./devel/setup.zsh

# 设置需要编译的srv文件
注意先后顺序：`find_package` -> `add_service_files` -> `generate_messages` -> `catkin_package`

```cmake
# CMakeLists.txt
add_service_files(
  FILES
  AddTwoInts.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
)
```

# 自定义消息，添加依赖
```xml
<!-- package.xml -->
<build_depend>message_generation</build_depend>
<exec_depend>message_runtime</exec_depend>
```
```cmake
# CMakeLists.txt
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  std_msgs
  message_generation
)

catkin_package(
  CATKIN_DEPENDS geometry_msgs roscpp rospy std_msgs message_runtime
)
```

# 编译、查询 别忘了执行 source devel/setup.zsh
```shell
➜  catkin_communition git:(learning_communication_server_client) ✗ catkin_make
...
➜  catkin_communition git:(learning_communication_server_client) ✗ roscore
➜  catkin_communition git:(learning_communication_server_client) ✗ rosrun learning_communication server
[ INFO] [1699435608.133423838]: Ready to add two ints.
[ INFO] [1699435611.879613527]: request: x=1, y=3
[ INFO] [1699435611.879754017]: sending back response: [4]
➜  catkin_communition git:(learning_communication_server_client) ✗ rosrun learning_communication client 1 3
[ INFO] [1699435611.880204178]: Sum: 4
```