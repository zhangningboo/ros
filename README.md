# 新建工程

```shell
# 创建工作空间
➜  workspace git:(main) ✗ mkdir -p project_name/src
➜  workspace git:(main) ✗ cd project_name/src
➜  src git:(main) ✗ catkin_init_workspace
➜  src git:(main) ✗ sed -i '' CMakeLists.txt
# 创建包
➜  src git:(main) ✗ catkin_create_package package_name
# 设置环境
➜  src git:(main) ✗ cd ..
➜  project_name git:(main) ✗ catkin_make
➜  project_name git:(main) ✗ source devel/setup.zsh
```