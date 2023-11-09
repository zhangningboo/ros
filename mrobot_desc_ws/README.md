# gazbo

### 创建环境
```shell
➜  ros git:(master) ✗ mkdir -p mrobot_desc_ws/src
➜  ros git:(master) ✗ cd mrobot_desc_ws/src 
➜  src git:(master) ✗ git checkout mrobot_desc_ws
➜  src git:(mrobot_desc_ws) ✗ catkin_create_pkg mrobot_description urdf xacro
➜  src git:(mrobot_desc_ws) ✗ cd ..
➜  mrobot_desc_ws git:(mrobot_desc_ws) ✗ catkin_make
# 设置编码
➜  mrobot_desc_ws git:(mrobot_desc_ws) ✗ sudo apt install unicode
➜  mrobot_desc_ws git:(mrobot_desc_ws) ✗ sudo find / -name sitecustomize.py    
/usr/lib/python2.7/sitecustomize.py
/usr/lib/python3.5/sitecustomize.py
/etc/python2.7/sitecustomize.py
/etc/python3.5/sitecustomize.py
# 把找到的python2.7的文件中，都加入内容：
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

# 检测udrf配置是否正确
➜  mrobot_description git:(mrobot_desc_ws) ✗ sudo apt install liburdfdom-tools ros-kinetic-joint-state-publisher-gui
➜  mrobot_description git:(mrobot_desc_ws) ✗ cd urdf 
➜  urdf git:(mrobot_desc_ws) ✗ check_urdf mrobot_chassis.urdf 
Error:   Error reading Attributes.
         at line 72 in /build/urdfdom-UJ3kd6/urdfdom-0.4.1/urdf_parser/src/model.cpp
ERROR: Model Parsing the xml failed
➜  urdf git:(mrobot_desc_ws) ✗ 
# 检查不通过，使用在线xml格式化工具检测一遍
➜  urdf git:(mrobot_desc_ws) ✗ urdf_to_graphiz mrobot_chassis.urdf
# rviz
➜  urdf git:(mrobot_desc_ws) ✗ sudo find / -name sizecustomize.py
➜  urdf git:(mrobot_desc_ws) ✗ roslaunch mrobot_description display_mrobot_chassis_urdf.launch
```
![配置rviz](rviz.png)

- udrf: 配置机器人外观
- urdf_to_graphiz: 查看节点连接信息

### xacro
用于简化、代码化urdf文件的配置，转换有以下两种方式：
```shell
➜  urdf git:(mrobot_desc_ws) ✗ rosrun xacro xacro.py mrobot.urdf.xacro > mrobot.urdf
➜  urdf git:(mrobot_desc_ws) ✗ roslaunch mrobot_description display_mrobot.launch
# 或

# 加相机
➜  urdf git:(mrobot_desc_ws) ✗ roslaunch mrobot_description display_mrobot_with_camera.launch
# 加kinect
➜  mrobot_desc_ws git:(mrobot_desc_ws) ✗ roslaunch mrobot_description display_mrobot_with_kinect.launch
# 加雷达
➜  mrobot_desc_ws git:(mrobot_desc_ws) ✗ roslaunch mrobot_description display_mrobot_with_rplidar.launch
```

### ArobotiX
```shell
# 安装
➜  urdf git:(mrobot_desc_ws) ✗ sudo apt install ros-kinect-arbotix 
# 或（源码安装启动时有些问题）
➜  workspace ✗ git clone https://github.com/vanadiumlabs/arbotix_ros.git
➜  workspace ✗ cd arbotix_ros && mkdir src && catkin_make
➜  mrobot_desc_ws git:(mrobot_desc_ws) ✗ source ${arbotix_ros_path}/devel/setup.zsh
# 配置文件：fake_mrobot_arbotix.yaml
# launch文件：arbotix_mrobot_with_kinect.launch
# 启动
➜  mrobot_desc_ws git:(mrobot_desc_ws) ✗ roslaunch mrobot_description arbotix_mrobot_with_kinect.launch
```