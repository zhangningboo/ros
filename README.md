# ROS melodic 安装

```shell
$ sudo echo "deb https://mirrors.tuna.tsinghua.edu.cn/ros/ubuntu/ bionic main" > /etc/apt/sources.list.d/ros-latest.list
$ sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
$ sudo apt install -y ros-melodic-desktop-full
$ sudo apt install -y python-rosdep python-rosinstall python-rosinstall-generator python-wstool build-essential
$ sudo rosdep init
$ rosdep update  # 科学上网
$ echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc && source ~/.bashrc
$ sudo apt install -y ros-melodic-rosparam-shortcuts
$ cd ~ && mkdir workspace && cd ~/workspace && git clone https://github.com/gflags/gflags.git
$ cd gflags && mkdir build && cd build
$ cmake -DCMAKE_INSTALL_PREFIX=/usr/local -DBUILD_SHARED_LIBS=ON - DGFLAGS_ NAMESPACE=gflags ..
$ make -j4 && sudo make install
$ sudo apt install -y ros-melodic-ros-control ros-melodic-ros-controllers
$ mkdir -p ~/workspace/catkin_ws/src && cd ~/workspace/catkin_ws && catkin_make
$ source ~/workspace/catkin_ws/devel/setup.bash
```

### 安装MoveIt
```shell
$ sudo apt install -y python-catkin-tools clang-format-3.9
$ sudo apt install -y ros-melodic-moveit
$ mkdir -p ~/workspace/moveit_ws/src && cd ~/workspace/moveit_ws/src
$ sudo apt install -y ros-melodic-joint-state-publisher-gui \
                      ros-melodic-moveit-resources \
                      ros-melodic-moveit-visual-tools \
                      ros-melodic-code-coverage \
                      ros-melodic-franka-description \
                      ros-melodic-joy \
                      ros-melodic-canopen-motor-node \
                      ros-melodic-panda-moveit-config
$ git clone https://github.com/ros-planning/moveit_tutorials.git -b melodic-devel
$ rosdep install -y --from-paths . --ignore-src --rosdistro melodic
$ cd ~/workspace/moveit_ws && catkin_make
$ sudo apt install -y ros-melodic-moveit ros-melodic-moveit-pr2
$ roslaunch moveit_setup_assistant setup_assistant.launch
```

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
- $ rqt_console # 日志可视化
- $ rqt_graph   # 计算图
- $ rqt_plot    # 数据绘图
- $ rosrun rqt_reconfigure rqt_reconfigure  # 参数动态配置
- TF树
    - rqt_tf_tree
        - 实时工具，观察在Ros上被发布的坐标系树。
        - $ rosrun rqt_tf_tree rqt_tf_tree  # 实时监看
    - view_frames
        - 连续采样5s获得的树的内容，并存成一个图片
        - $ rosrun tf view_frames  # 生成图片, 连续采样5s
        - $ evince frames.pdf  # 查看图片
    - tf_echo
        - 报告在ROS上任意两个坐标系发布的变换，查看指定参考系之间的变换关系
        - $ tf_echo <source_frame> <target_frame>
        - $ rosrun tf tf_echo [reference_frame] [target_frame]
    - 还有好几种

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
