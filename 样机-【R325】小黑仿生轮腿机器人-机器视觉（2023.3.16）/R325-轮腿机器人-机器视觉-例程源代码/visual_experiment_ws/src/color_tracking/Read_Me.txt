该试验有两个版本


版本一：带有摄像头标定（程序运行较慢，但能看到实验过程）
	1.将／color_tracking／arduino_program中的程序下载到Mega 2560中
	2.打开终端（Alt＋ctrl＋T），输入： roslaunch color_tracking camera_calibration.launch
	3.按下（shift＋ctrl＋T），输入：   roslaunch astra_camera astra.launch
	4.移动灭火器，观察底盘是否跟随灭火器


版本二：不带摄像头标定（精简版，程序运行较快）
	1.将／color_tracking／arduino_program中的程序下载到Mega 2560中
	2.打开终端（Alt＋ctrl＋T），输入： roslaunch color_tracking color_tracking_sth.launch 
	3.按下（shift＋ctrl＋T），输入：   roslaunch astra_camera astra.launch  
	4.移动灭火器，观察底盘是否跟随灭火器

