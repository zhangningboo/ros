# 新建工程

```shell
➜  workspace git:(main) ✗ mkdir -p project_name/src
➜  workspace git:(main) ✗ cd project_name/src
➜  src git:(main) ✗ catkin_init_workspace
➜  src git:(main) ✗ sed -i '' CMakeLists.txt
➜  src git:(main) ✗ cd ..
➜  project_name git:(main) ✗ catkin_make
➜  project_name git:(main) ✗ source devel/setup.zsh
```