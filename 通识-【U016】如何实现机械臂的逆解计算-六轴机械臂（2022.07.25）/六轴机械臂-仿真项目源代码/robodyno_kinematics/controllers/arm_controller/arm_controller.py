# 导入自己创建的六自由度机械臂库文件
from six_dof_arm import SixDofArm
from scipy.spatial.transform import Rotation as R
import numpy as np
from math import pi

# 创建六自由度机械臂类型的对象arm
arm = SixDofArm()

# 机械臂使能
arm.enable()


# theta = [0,0,-pi/2,0,0,0]
theta = [0,0,pi/2,0,0,0]
arm.forward_kinematics(theta)
arm.delay(4)



# 机械臂失能
arm.disable()
