# coding=utf-8
import serial
import time

#solveList = ['U1', 'U2', 'U3', 'D1', 'D2', 'D3', 'L1', 'L2', 'L3',
#            'R1', 'R2', 'R3', 'F1', 'F2', 'F3', 'B1', 'B2', 'B3']
#stepList = ['0', '1', '2', '3', '4', '5', '6', '7', '8',
#            '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']


def send_arduino(com, txt):
    """Send command to arduino"""
    try:
        x = serial.Serial('COM5', 9600,timeout=1)
        data_solve = txt
        if x.isOpen() > 0:
            print("open com")
            time.sleep(2)
            x.write(data_solve.encode())
            time.sleep(30)
            x.close()
    except:
        print('Cannot open com.')


