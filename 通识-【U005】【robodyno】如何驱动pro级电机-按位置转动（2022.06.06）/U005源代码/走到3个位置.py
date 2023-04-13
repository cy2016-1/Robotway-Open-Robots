# 初始化电机对象
from protobot.can_bus import Robot
from protobot.can_bus.nodes import MotorFactory
robot = Robot()
motor = robot.add_device('motor0', MotorFactory(), node_id=0x10, reduction=-44)
# 电机使能
motor.enable()
# 进入直接位置模式
motor.position_mode()
# 设置位置参数
motor.set_pos(6.28)
robot.delay(2) # 该函数意思是为上一行的动作留出多长时间，括号里的2代表2秒，
# 进入滤波位置模式
motor.position_filter_mode(1)
# 设置位置参数
motor.set_pos(0)
robot.delay(3) # 由于滤波位置模式有加减速过程，所以留给的时间稍微长一些
# 进入轨迹位置模式
motor.position_traj_mode(2,0.5,0.5)
# 设置位置参数
motor.set_pos(-6.28)
robot.delay(3) # 由于轨迹位置模式有加减速过程，所以留给的时间稍微长一些