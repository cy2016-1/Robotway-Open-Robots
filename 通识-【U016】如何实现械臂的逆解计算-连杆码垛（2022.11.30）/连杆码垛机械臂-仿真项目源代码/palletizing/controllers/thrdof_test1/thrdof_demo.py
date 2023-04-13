# 导入Robot及其他相关库文件
from protobot.webots import Robot
from protobot.webots.motor import MotorFactory
from protobot.webots.hand_module import HandModuleFactory
import numpy as np
from math import pi
import math

# 机械臂连杆参数
L1 = 190
L2 = L1
hand = 10
d = 79.4

# 创建机械臂类作为Robot的子类
class ThrDofArm(Robot):
    # 构造方法，初始化机械臂所用的所有电机
    def __init__(self):
        super(ThrDofArm, self).__init__()
        self.add_device('M1', MotorFactory(), reduction = 44)
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
        
    # 正向运动学
    def palletizer_fk(self, theta1, theta2, theta3):
        
        a_2 = L1**2 + L2**2 - 2*L1*L2*math.cos(pi/2+theta3)
        a = math.sqrt(a_2)
        # alpha = (pi-pi/2-theta3) / 2
        ca = (L1**2 + a_2 - L2**2) / (2*a*L1)
        alpha = math.acos(ca)
        # print(alpha)
        
        b = a * math.sin(alpha + theta2)
        
        x = b * math.cos(theta1)
        y = b * math.sin(theta1)
        z = a * math.cos(alpha + theta2)
        
        print("palletizer_fk:")
        print("x: ",round(x,4))
        print("y: ",round(y,4))
        print("z: ",round(z,4))
        
        self.motors[0].set_pos(theta1)
        self.motors[1].set_pos(theta2)
        self.motors[2].set_pos(theta3)
        
        self.palletizer_ik(x, y, z)
        
        
    # 逆向运动学
    def palletizer_ik(self, x, y, z):
        
        theta1 = math.atan2(y, x)
        
        a = math.sqrt(x**2 + y**2)
        beta = math.atan2(z,a)
        b = math.sqrt(a**2 + z**2)
        ca = (b**2 + L1**2 - L2**2) / (2*b*L1)
        if ca > 1:
            print("None")
        else:
            # print(s)
            alpha = math.acos(ca)
        
            theta2 = math.atan2(a,z) -alpha
            
            theta3 = pi - pi/2 - alpha*2
        
            print("palletizer_ik:")
            print("theta1: ",round(theta1,4))
            print("theta2: ",round(theta2,4))
            print("theta3: ",round(theta3,4))
            
            self.motors[0].set_pos(theta1)
            self.motors[1].set_pos(theta2)
            self.motors[2].set_pos(theta3)
        
            # self.palletizer_fk(theta1, theta2, theta3)
            
            

        
        
        
        

    # def test1(self):
        # self.motors[0].set_pos(1)
        # self.motors[1].set_pos(1.10)
        # self.motors[2].set_pos(1)

        
    # def test3(self):
        # self.motors[1].set_pos(1.8)
        # self.delay(0.3)
        # self.motors[0].set_pos(1.5)
        # self.motors[0].set_pos(-0.5)
        # self.delay(0.2)
        # self.motors[1].set_pos(0.5)
        # self.delay(0.4)
        # self.motors[0].set_pos(0.5)
        

##arm = ScaraDofArm()
#arm.enable()    
##arm.home()
#arm.delay(15)
#arm.test1()
#arm.delay(6)
#arm.test2()
#arm.delay(3)
#arm.home()
##