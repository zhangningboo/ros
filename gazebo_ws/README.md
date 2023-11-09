# Gazebo

### 安装
```shell
➜  gazebo_ws git:(gazebo_ws) ✗ sudo apt install ros-kinetic-gazebo*
➜  gazebo_ws git:(gazebo_ws) ✗ catkin_make
# 启动
➜  gazebo_ws git:(gazebo_ws) ✗ roslaunch learning_gazebo view_mrobot_gazebo.launch
```

### 摄像头
```shell
➜  gazebo_ws git:(gazebo_ws) ✗ roslaunch learning_gazebo view_mrobot_with_camera_gazebo.launch
# 查看
➜  gazebo_ws git:(gazebo_ws) ✗ rqt_image_view
```

### kinect
```shell
➜  gazebo_ws git:(gazebo_ws) ✗ sudo sh -c 'echo "deb  http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
➜  gazebo_ws git:(gazebo_ws) ✗ wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
➜  gazebo_ws git:(gazebo_ws) ✗ sudo apt update
➜  gazebo_ws git:(gazebo_ws) ✗ sudo apt install libsdformat4 libsdformat6 gazebo9 libgazebo9-dev
➜  gazebo_ws git:(gazebo_ws) ✗ sudo apt install ros-kinetic-gazebo9*
➜  gazebo_ws git:(gazebo_ws) ✗ roslaunch learning_gazebo view_mrobot_with_kinect_gazebo.launch
# 查看
➜  gazebo_ws git:(gazebo_ws) ✗ rosrun rviz rviz
```