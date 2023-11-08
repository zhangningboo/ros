# 安装插件ROS（在ROS安装的机器）,catkin_tool（vscode安装的机器）
# 使用vscode打开本目录
# 别忘了执行 source ./devel/setup.zsh

# 设置需要编译的msg文件
注意先后顺序：`find_package` -> `add_message_files` -> `generate_messages` -> `catkin_package`

```cmake
# CMakeLists.txt
add_message_files(
  FILES
  Person.msg
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

# 编译、查询
```shell
➜  catkin_communition git:(learning_communication_custom_msg) ✗ catkin_make
...
➜  catkin_communition git:(learning_communication_custom_msg) ✗ rosmsg show Person
[learning_communication/Person]:
uint8 unknown=0
uint8 male=1
uint8 female=2
string name
uint8 sex
uint8 age
```
# 运行 roscore
# rosrun learning_communication listener
# rosrun learning_communication talker