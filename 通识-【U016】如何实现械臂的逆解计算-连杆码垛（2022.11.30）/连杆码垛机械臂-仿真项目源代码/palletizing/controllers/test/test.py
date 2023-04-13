# You may need to import some classes of the controller module. Ex:
#  from controller import Robot, Motor, DistanceSensor
from controller import Robot
from test_calssic import ThrDofArm
from math import pi
import math
# from multiprocessing.connection import Listener

# create the Robot instance.
arm = ThrDofArm()
arm.enable()

# arm.motors[0].set_pos(-0.5)
# arm.motors[1].set_pos(0.5)
# arm.motors[2].set_pos(0)
# arm.delay(3)

arm.palletizer_ik(0,200,150)
arm.delay(3)

arm.palletizer_ik(0,300,150)
arm.delay(3)

arm.palletizer_ik(0,300,200)
arm.delay(3)
# for i in range (0,400,2):
    # arm.palletizer_ik(0,i,150)
    # arm.delay(0.01)

# for i in range (0,300,2):
    # arm.palletizer_ik(0,400,i)
    # arm.delay(0.01)
    
# for i in range (200,-200,-2):
    # arm.palletizer_ik(i,400,300)
    # arm.delay(0.01)

    