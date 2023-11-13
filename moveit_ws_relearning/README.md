# MoveIt!

### 配置步骤
- urdf
- gazebo
- rviz

### 可视化
```shell
➜  moveit_ws git:(moveit_ws) ✗ roslaunch marm_description view_arm.launch
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
- 错误：`No sensor plugin specified for octomap updater 0; ignoring` \
    编辑文件`src/marm_moveit_config/config/sensors_3d.yaml`
    ```yaml
    # The name of this file shouldn't be changed, or else the Setup Assistant won't detect it
    sensors:
      - filtered_cloud_topic: filtered_cloud
        max_range: 5.0
        max_update_rate: 1.0
        padding_offset: 0.1
        padding_scale: 1.0
        point_cloud_topic: /head_mount_kinect/depth_registered/points
        point_subsample: 1
        sensor_plugin: occupancy_map_monitor/PointCloudOctomapUpdater
    ```
- 错误：`Could not find the planner configuration 'None' on the param server` \
    编辑文件`src/marm_moveit_config/config/ompl_planning.yaml`，把`default_planner_config`的值改为`RRTConnect`
- 错误：`Unknown marker name: 'EE:goal_grasping_frame' (not published by RobotInteraction class)` \
    还未解决

### ArbotiX控制器
- 新建文件：`src/marm_description/config/arm.yaml`
- 新建文件：`src/marm_description/launch/fake_arm.launch`
- 运行arbotix
  ```shell 
  ➜  moveit_ws_relearning git:(moveit_ws) ✗ roslaunch marm_description fake_arm.launch
  ➜  moveit_ws_relearning git:(moveit_ws) ✗ chmod +x src/marm_planning/scripts/trajectory_demo.py
  ➜  moveit_ws_relearning git:(moveit_ws) ✗ rosrun marm_planning trajectory_demo.py _reset:=True
  ```

### MoveIt!关节控制器
- 作用：通过MoveIt！实现运动规划，并且将规划结果通过FollowJointTrajectoryAction发送给机器人的ArbotiX关节控制器
- 插件：moveit_simple_controller_manager
- 配置文件：`src/learning_moveit/config/ros_controllers.yaml`

#### 关节空间规划
- 所谓关节空间，就是以关节角度为控制量的机器人运动。
- 虽然各关节到达期望位置所经过的时间相同，但是各关节之间相互独立，互不影响。
- 机器人状态使用各轴位置来描述，在指定运动目标的机器人状态后，通过控制各轴运动来到达目标位姿。
- 运行：
  ```shell
  ➜  moveit_ws_relearning git:(moveit_ws) ✗ roslaunch marm_planning arm_planning.launch
  ➜  moveit_ws_relearning git:(moveit_ws) ✗ chmod +x src/marm_planning/scripts/moveit_fk_demo.py
  ➜  moveit_ws_relearning git:(moveit_ws) ✗ rosrun marm_planning moveit_fk_demo.py
  ```
#### 工作空间规划
- 机械臂关节空间的规划不需要考虑机器人终端的姿态。
- 通过机器人终端的三维坐标位置和姿态给定，在运动规划时使用逆向运动学求解各轴位置
- 运行：
  ```shell
  ➜  moveit_ws_relearning git:(moveit_ws) ✗ roslaunch marm_planning arm_planning.launch
  ➜  moveit_ws_relearning git:(moveit_ws) ✗ chmod +x src/marm_planning/scripts/moveit_ik_demo.py
  ➜  moveit_ws_relearning git:(moveit_ws) ✗ rosrun marm_planning moveit_ik_demo.py
  ```

#### 笛卡儿运动规划
- 不仅关心机械臂的起始、终止位姿，对运动过程中的位姿也有要求
- 从开始位姿到终端位姿的过程中，设定中间的轨迹形状。
- 比如希望机器人终端能够走出一条直线或圆弧轨迹。
  ```shell
  ➜  moveit_ws_relearning git:(moveit_ws) ✗ sudo apt install ros-kinetic-trac-ik-kinematics-plugin
  ➜  moveit_ws_relearning git:(moveit_ws) ✗ roslaunch marm_planning arm_planning_with_trail.launch
  ➜  moveit_ws_relearning git:(moveit_ws) ✗ chmod +x src/marm_planning/scripts/moveit_cartesian_demo.py
  ➜  moveit_ws_relearning git:(moveit_ws) ✗ rosrun marm_planning moveit_cartesian_demo.py _cartesian:=False
  ```

#### 避障规划
- 运动规划库OMPL支持避障规划
  ```shell
  ➜  moveit_ws_relearning git:(moveit_ws) ✗ roslaunch marm_planning arm_planning_with_trail.launch
  ➜  moveit_ws_relearning git:(moveit_ws) ✗ chmod +x src/marm_planning/scripts/moveit_obstacles_demo.py
  ➜  moveit_ws_relearning git:(moveit_ws) ✗ rosrun marm_planning moveit_obstacles_demo.py
  ```

  #### 抓取
```shell
➜  moveit_ws_relearning git:(moveit_ws) ✗ roslaunch marm_planning arm_planning_with_trail.launch
➜  moveit_ws_relearning git:(moveit_ws) ✗ chmod +x src/marm_planning/scripts/moveit_pick_and_place_demo.py
➜  moveit_ws_relearning git:(moveit_ws) ✗ rosrun marm_planning moveit_pick_and_place_demo.py
```