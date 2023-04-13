# 导入Robot及其他相关库文件
from protobot.webots import Robot
from protobot.webots.motor import MotorFactory
from protobot.webots.hand_module import HandModuleFactory
import numpy as np
from math import pi
import math

# 机械臂连杆参数
L1 = 300
L2 = L1
hand = 10
d = 79.4

# 创建机械臂类作为Robot的子类
class ThrDofArm(Robot):
    # 构造方法，初始化机械臂所用的所有电机
    def __init__(self):
        super(ThrDofArm, self).__init__()
        self.add_device('M1', MotorFactory(), reduction = 70)
        self.add_device('M2', MotorFactory(), reduction = 44)
        self.add_device('M3', MotorFactory(), reduction = 44)
        self.motors = [
            self.device('M1'),
            self.device('M2'),
            self.device('M3'),
        ]
        self.hand = self.add_device('hand',HandModuleFactory())
        
        for i in range(1,3):
            self.motors[i].position_traj_mode(1.57,5)
        
    # 机械臂复位函数
    def home(self):
        for i in range(3):
            self.motors[i].set_pos(0)
        self.hand.set_pos(0)
        
    def set_hand(self,pos):
        self.hand.set_pos(pos)
        

    # 逆向运动学
    def palletizer_ik(self, x, y, z):
        Theta = math.atan2(y,x)
        q = math.sqrt(x*x+y*y)
        Alpha_a1 = math.atan2(z,q)
        a = math.sqrt(q*q+z*z)
        Alpha_a2 = math.acos((L1*L1+a*a-L2*L2)/(2*L1*a))
        Alpha = pi/2 - (Alpha_a1+Alpha_a2)
        Beta_b1 = math.acos((L1*L1+L2*L2-a*a)/(2*L1*L2))
        Beta = Beta_b1 - pi/2
        
        print("palletizer_ik:")
        print("theta1: ",round(Theta,4))
        print("theta2: ",round(Alpha,4))
        print("theta3: ",round(Beta,4))
        
        self.motors[0].set_pos(Theta)
        self.motors[1].set_pos(Alpha)
        self.motors[2].set_pos(Beta)
         