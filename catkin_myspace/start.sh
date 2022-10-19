
# 变量定义
work_path=/home/g/workspace/multisensor_fusion_localization_study/catkin_myspace/
add_source="source devel/setup.bash"

# #rviz可视化
gnome-terminal -t "可视化" -x bash -c "cd $work_path;$add_source;roslaunch multisensor_localization test_frame.launch;exec bash;"
sleep 2s
#节点1:数据预处理
gnome-terminal -t "数据处理" -x bash -c "cd $work_path;$add_source;rosrun multisensor_localization data_pretreat_node;exec bash;"
#节点2:前端里程计
gnome-terminal -t "前端" -x bash -c "cd $work_path;$add_source;rosrun multisensor_localization front_end_node;exec bash;"
#节点3:后端优化
gnome-terminal -t "后端" -x bash -c "cd $work_path;$add_source;rosrun multisensor_localization back_end_node;exec bash;"
#ros bag启动
gnome-terminal -t "bag" -x bash -c "cd $work_path;$add_source; rosbag play  *.bag ;exec bash;"
#启动roscore
# gnome-terminal -t "roscore" -x bash -c "cd $work_path;$add_source;roscore;exec bash;"
# 必要调试输出
sleep 2s
gnome-terminal -t "检测" -x bash -c "cd $work_path;$add_source; rostopic hz /laser_odom ;exec bash;"                           