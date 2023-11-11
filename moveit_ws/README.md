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

### MoveIt!控制器
- 新建文件：`src/learning_moveit/config/controllers.yaml`

### 关节空间控制机械臂
- 修改`ompl_planning.yaml`中关于`default_planner_config`的配置：
```yaml
...
arm:
  default_planner_config: RRTConnect
...
```
- 修改`ros_controllers.yaml`中`controller_list`的值：
```yaml
...
controller_list:
# name和action_ns组成控制器action接口的消息名，例如arm_controller插件的action接口就是:arm_controller/follow_joint_trajectory
  - name: arm_controller  # 控制器插件的名称
    action_ns: follow_joint_trajectory  # 控制器发布action消息的命名空间
    type: FollowJointTrajectory  # 实现action的类型
    default: true  # 是否为该规划组的默认控制器插件
    joints:
      - joint1
      - joint2
      - joint3
      - joint4
      - joint5
      - joint6
      
  - name: gripper_controller
    action_ns: gripper_action
    type: GripperCommand
    default: true # 是否为该规划组的默认控制器插件
    joints:
      - finger_joint1
...
```
- 启动仿真
```shell
➜  moveit_ws git:(moveit_ws) ✗ roslaunch learning_moveit arm_planning.launch
```
- MoveIt!
```shell
➜  moveit_ws git:(moveit_ws) ✗ roslaunch learning_moveit arm_planning.launch
➜  script git:(moveit_ws) ✗ python moveit_fk_demo.py 
```

### MoveIt! 空间运动规划
使用3维坐标的参数移动机械臂，如：向左平移30cm。
只关注起始位姿和终端位姿，对中间的轨迹没有要求。
```shell
➜  moveit_ws git:(moveit_ws) ✗ roslaunch learning_moveit arm_planning.launch
➜  script git:(moveit_ws) ✗ python moveit_ik_demo.py 
```
步骤：
- 首先需要创建规划组的控制对象；
- 然后获取机器人的终端link名称；
- 其次设置目标位姿对应的参考坐标系、起始位姿和终止位姿；
- 最后进行规划并控制机器人运动。
```python
arm = moveit_commander.MoveGroupCommander('arm')
end_effector_link = arm.get_end_effector_link()
reference_frame = 'base_link'
arm.set_pose_reference_frame(reference_frame)
arm.set_start_state_to_current_state()
arm.set_pose_target(target_pose, end_effector_link)
traj = arm.plan()
arm.execute(traj)
arm.shift_pose_target(1, -0.05, end_effector_link)
arm.go()
```

### 笛卡儿运动规划
从开始位姿到终端位姿的过程中，设定中间的轨迹形状。
```shell
➜  moveit_ws git:(moveit_ws) ✗ sudo apt install ros-kinetic-trac-ik-kinematics-plugin
➜  moveit_ws git:(moveit_ws) ✗ roslaunch learning_moveit arm_planning_with_trail.launch
➜  script git:(moveit_ws) ✗ python moveit_cartesian_demo.py 
```