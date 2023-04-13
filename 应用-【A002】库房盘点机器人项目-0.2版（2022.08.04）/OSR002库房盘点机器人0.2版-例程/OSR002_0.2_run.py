#!/usr/bin/python3

from protobot.can_bus import Robot
from protobot.can_bus.nodes import PlcBoardFactory
from protobot.can_bus.nodes import MotorFactory
from time import time
robot = Robot()
motor_f = robot.add_device('motorf', MotorFactory(), 0x11, reduction=12.45)
motor_l = robot.add_device('motorl', MotorFactory(), 0x12, reduction=-12.45)
motor_r = robot.add_device('motorr', MotorFactory(), 0x13, reduction=12.45)
motor_z = robot.add_device('motorz', MotorFactory(), 0x10, reduction=44)
plc = robot.add_device('plc', PlcBoardFactory(), 0x20)
z_pos = 0
v = 0.1
error = False

def green_light():
    plc.set_12v_io(0, 1, 0)

def red_light():
    plc.set_12v_io(1, 0, 0)

def yellow_light():
    plc.set_12v_io(0, 0, 1)

def turn_off_lights():
    plc.set_12v_io(0, 0, 0)
    
from math import pi, sqrt
wheel_r = 0.1
v2w = lambda v: v/wheel_r

def run(vx, vy, vw):
    vf = v2w(vy) + v2w(vw * 0.48)
    vl = v2w(vx) * sqrt(2) + v2w(vy) / sqrt(2) - v2w(vw * 0.48)
    vr = v2w(vx) * sqrt(2) - v2w(vy) / sqrt(2) + v2w(vw * 0.48)
    if not error:
        motor_f.set_vel(vf)
        motor_l.set_vel(vl)
        motor_r.set_vel(vr)
    return vf, vl, vr
    
def reset_z():
    global z_pos
    if error:
        return
    if plc.get_io()[3]:
        yellow_light()
        motor_z.velocity_ramp_mode(3)
        motor_z.set_vel(-1.5)
        while plc.get_io()[3]:
            continue
    motor_z.set_vel(0)
    motor_z.velocity_mode()
    robot.delay(0.5)
    z_pos = motor_z.get_pos()
    motor_z.set_pos(z_pos)
    motor_z.position_traj_mode(6,3,3)
    green_light()
    
def z_pos1():
    if not error:
        motor_z.set_pos(z_pos+4)
def z_pos2():
    if not error:
        motor_z.set_pos(z_pos+8)
def z_pos3():
    if not error:
        motor_z.set_pos(z_pos+12)
def z_pos4():
    if not error:
        motor_z.set_pos(z_pos+16)
    
def accelerate():
    global v
    v = v * 1.2
    if v > 0.4:
        v = 0.4

def decelerate():
    global v
    v = v * 0.8
    if v < 0.03:
        v = 0.03

def start():
    motor_f.clear_errors()
    motor_l.clear_errors()
    motor_r.clear_errors()
    motor_z.clear_errors()
    robot.delay(1)
    motor_f.enable()
    motor_l.enable()
    motor_r.enable()
    motor_z.enable()
    robot.delay(1)
    if has_error():
        red_light()
    else:
        green_light()

def stop():
    run(0, 0, 0)
    motor_f.disable()
    motor_l.disable()
    motor_r.disable()
    motor_z.disable()

def motor_error(motor):
    status = motor.status()
    return status.get('error', 1) or (time() - status.get('timestamp', 0)) > 3

def has_error():
    error = motor_error(motor_f) or motor_error(motor_l) or motor_error(motor_r) or motor_error(motor_z) 
    return error

import sys
import select
import tty
import termios

def isData():
    return select.select([sys.stdin], [], [], 0) == ([sys.stdin], [], [])
old_settings = termios.tcgetattr(sys.stdin)
t = time()
last_key = '' 
start()
reset_z()
try:
    tty.setcbreak(sys.stdin.fileno())
    while True:
        if has_error():
            red_light()
        if isData():
            c = sys.stdin.read(1)
            # print(c)
            if c == '.':
                accelerate()
            elif c == ',':
                decelerate()
            elif c != last_key:
                if c == '-':
                    stop()
                elif c == '=':
                    start()
                elif c == '1':
                    z_pos1()
                elif c == '2':
                    z_pos2()
                elif c == '3':
                    z_pos3()
                elif c == '4':
                    z_pos4()
                elif c == 'w':
                    run(v, 0, 0)
                elif c == 's':
                    run(-v, 0, 0)
                elif c == 'a':
                    run(0, v, 0)
                elif c == 'd':
                    run(0, -v, 0)
                elif c == 'q':
                    run(0, 0, v*2)
                elif c == 'e':
                    run(0, 0, -v*2)
            last_key = c
            t = time()
            if c == '\x1b':         # x1b is ESC
                break
        else:
            if time() - t > 0.1:
                # print('none')
                run(0, 0, 0)
                last_key = ''
                pass
            continue
finally:
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, old_settings)
    stop()