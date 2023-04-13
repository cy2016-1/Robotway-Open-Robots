"""scara_test1 controller."""

# You may need to import some classes of the controller module. Ex:
#  from controller import Robot, Motor, DistanceSensor
from controller import Robot
from thrdof_demo import ThrDofArm
from math import pi
import math
# from multiprocessing.connection import Listener


# create the Robot instance.
arm = ThrDofArm()
arm.enable()

arm.palletizer_ik(100,100,0)
arm.delay(3)

arm.palletizer_ik(100,100,-50)
arm.delay(3)

    