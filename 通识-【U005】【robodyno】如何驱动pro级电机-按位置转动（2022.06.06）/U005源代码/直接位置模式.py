#初始化电机对象
from robodyno import Robot
from robodyno.nodes import MotorFactory
robot = Robot()
motor = robot.add_device('motor0', MotorFactory(), 0x10, reduction=-44)
#电机使能
motor.enable()
#进入直接位置模式
motor.position_mode()
#设置位置
motor.set_pos(-3.14)