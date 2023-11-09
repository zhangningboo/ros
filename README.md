# 新建工程

```shell
# 创建工作空间
➜  workspace git:(main) ✗ mkdir -p project_name/src
➜  workspace git:(main) ✗ cd project_name/src
➜  src git:(main) ✗ catkin_init_workspace
➜  src git:(main) ✗ sed -i '' CMakeLists.txt
# 创建包
➜  src git:(main) ✗ catkin_create_pkg package_name
# 设置环境
➜  src git:(main) ✗ cd ..
➜  project_name git:(main) ✗ catkin_make
➜  project_name git:(main) ✗ source devel/setup.zsh
```

### qt工具包
```shell
➜  ros git:(master) ✗ sudo apt install ros-kinetic-rqt ros-kinetic-rqt-common-plugins
```
##### 工具
- $ rqt_console 日志可视化
- $ rqt_graph   计算图
- $ rqt_plot    数据绘图
- $ rosrun rqt_reconfigure rqt_reconfigure 参数动态配置

### rviz 工具包
```shell
➜  ros git:(master) ✗ sudo apt install ros-kinetic-rviz
➜  ros git:(master) ✗ roscore
➜  ros git:(master) ✗ rosrun rviz rviz
```

### gazebo 仿真
```shell
➜  ros git:(master) ✗ sudo apt install ros-kinetic-gazebo-ros-pkgs ros-kinetic-gazebo-ros-control 
➜  ros git:(master) ✗ roscore
➜  ros git:(master) ✗ rosrun gazebo_ros gazebo
```

### rosbag 数据录制与回放
```shell
➜  ros git:(master) ✗ mkdir ~/bagfiles
➜  ros git:(master) ✗ cd ~/bagfiles
# 录制
➜  ros git:(master) ✗ rosbag record -a
# 回放
➜  ros git:(master) ✗ rosbag info ${bag_name}
```