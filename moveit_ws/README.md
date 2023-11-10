# MoveIt!

### 配置步骤
- urdf
- gazebo
- rviz

### 可视化
```shell
➜  moveit_ws git:(moveit_ws) ✗ roslaunch learning_moveit view_arm.launch
```

### MoveIt! Setup Assistant配置机械臂（urdf -> srdf）

```shell
➜  moveit_ws git:(moveit_ws) ✗ sudo apt install ros-kinetic-moveit
➜  moveit_ws git:(moveit_ws) ✗ rosrun moveit_setup_assistant moveit_setup_assistant
```
- 加载urdf
- 设置自碰撞矩阵
- 配置虚拟关节
    - 虚拟关节主要用来描述机器人在world坐标系下的位置。如果机器人是移动的，则虚拟关节可以与移动基座关联
- 创建规划组
    - 将机器人的多个组成部分（link，joint）集成到一个组中，运动规划器会针对一组link或joint完成规划任务。
- 定义机器人位姿
- 夹爪配置
- 生成配置文件（保存到当前ws的src目录即可）
- 可视化(可视化失败，检查名字是否有误)
```shell
➜  moveit_ws git:(moveit_ws) ✗ catkin_make
➜  moveit_ws git:(moveit_ws) ✗ roslaunch arm_moveit_setup_assistant_config demo.launch
```

### ArbotiX控制器
- 新建文件：`src/learning_moveit/config/arm.yaml`
- 运行arbotix
```shell 
➜  moveit_ws git:(moveit_ws) ✗ roslaunch learning_moveit fake_arm.launch
➜  moveit_ws git:(moveit_ws) ✗ roslaunch learning_moveit fake_arm.launch
➜  script git:(moveit_ws) ✗ python trajectory_demo.py
```