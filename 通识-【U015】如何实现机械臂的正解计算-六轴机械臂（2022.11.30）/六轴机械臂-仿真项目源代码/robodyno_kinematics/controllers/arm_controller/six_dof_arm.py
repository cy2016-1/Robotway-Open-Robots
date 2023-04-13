# 导入Robot及其他相关库文件
from protobot.webots import Robot
from protobot.webots.motor import MotorFactory
from protobot.webots.hand_module import HandModuleFactory
from kinematics import invKine
import numpy as np
from math import pi
import math

# 创建六自由度机械臂类作为Robot的子类
class SixDofArm(Robot):
    # 构造方法，初始化机械臂所用的所有电机
    def __init__(self):
        super(SixDofArm, self).__init__()
        self.add_device('M1', MotorFactory(), reduction = 44)
        self.add_device('M2', MotorFactory(), reduction = 44)
        self.add_device('M3', MotorFactory(), reduction = 44)
        self.add_device('M4', MotorFactory(), reduction = 44)
        self.add_device('M5', MotorFactory(), reduction = 44)
        self.add_device('M6', MotorFactory(), reduction = 44)
        self.motors = [
            self.device('M1'),
            self.device('M2'),
            self.device('M3'),
            self.device('M4'),
            self.device('M5'),
            self.device('M6'),
        ]
        # self.hand = self.add_device('hand', HandModuleFactory())
        for i in range(6):
            self.motors[i].position_traj_mode(1.57, 5)
        
    # 机械臂复位函数
    def home(self):
        for i in range(6):
            self.motors[i].set_pos(0)
        self.hand.set_pos(0)
    
    # def set_hand(self, pos):
        # self.hand.set_pos(pos)
            
    # 机械臂示例位置函数
    def demo_pose(self):
        self.motors[0].set_pos(-0.6)
        self.motors[1].set_pos(0.5)
        self.motors[2].set_pos(1)
        self.motors[3].set_pos(-0.9)
        self.motors[4].set_pos(1.57)
        self.motors[5].set_pos(3.14)
        # self.hand.set_pos(0.5)
        
        
    # 正运动学
    def dhtransform(self,alpha, a, d, theta):
        matrixs = np.matrix(np.zeros((4, 4)))
        
        sth = math.sin(theta)
        cth = math.cos(theta)
        sa = math.sin(alpha)
        ca = math.cos(alpha)
        
        matrixs[0, 0] = cth
        matrixs[1, 0] = sth
        matrixs[0, 1] = -sth * ca
        matrixs[1, 1] = cth * ca
        matrixs[2, 1] = sa
        matrixs[0, 2] = sth * sa
        matrixs[1, 2] = -cth * sa
        matrixs[2, 2] = ca
        matrixs[0, 3] = a * cth
        matrixs[1, 3] = a * sth
        matrixs[2, 3] = d
        matrixs[3, 3] = 1
        
        return matrixs
    
        
    def forward_kinematics(self, theta):
        d1 =  150
        a2 =  -145
        a3 =  -145
        d4 =  75
        d5 =  75
        d6 =  70
        
        T01 = self.dhtransform(pi/2 , 0 , d1, theta[0])
        T12 = self.dhtransform(0    , a2, 0 , theta[1]-pi/2)
        T23 = self.dhtransform(0    , a3, 0 , theta[2])
        T34 = self.dhtransform(pi/2 , 0 , d4, theta[3]-pi/2)
        T45 = self.dhtransform(-pi/2, 0 , d5, theta[4])
        T56 = self.dhtransform(0    , 0 , d6, theta[5])
    
        T06 = T01*T12*T23*T34*T45*T56
        
        print(T06.round(2))
        print("x: ",T06[0,3].round(2))
        print("y: ",T06[1,3].round(2))
        print("z: ",T06[2,3].round(2))
        
        self.inverse_kinematics(T06)
        # for i in range(6):
            # self.motors[i].set_pos(theta[i])
            
        # return T06
            
        
    
    # 逆运动学算法
    def inverse_kinematics(self,T06):

        pos_arr = invKine(T06)[:,2]

        pos_arr[1] = pi/2.0 + pos_arr[1,0]
        pos_arr[2] = -pos_arr[2,0]
        pos_arr[3] = pi/2.0 + pos_arr[3,0]

        
        print(pos_arr.round(2))
        for i in range(6):
            self.motors[i].set_pos(pos_arr[i,0])