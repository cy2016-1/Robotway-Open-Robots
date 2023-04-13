# 初始化电机对象
from robodyno import Robot
from robodyno.nodes import MotorFactory
robot = Robot()
motor = robot.add_device('motor0', MotorFactory(), 0x10, reduction=-44)
# 电机使能
motor.enable()
# 进入轨迹位置模式
motor.position_traj_mode(2,0.5,0.5)
# 设置位置
motor.set_pos(6.28)