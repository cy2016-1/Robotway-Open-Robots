# -*- coding: utf-8 -*-

#################################

#serial

#################################
import serial
import serial.tools.list_ports
#import threading
import time
import tkMessageBox as mb  
import binascii
import win
from gcode import Gcode

gc=Gcode()

class SerialCC():
    
    def __init__(self):
        self.ser=serial
        self.port_list = []
        self.baud_list = [300,1200,2400,4800,9600,14400,19200,28800,38400,57600,115200]
        self.port_index=0
        self.baud_index=0
        self.connect_state = False #连接状态标志
        self.rev_data=""
        
        #串口读取线程
        #self.t1 = threading.Thread(target=self.serial_read)
        #self.t1.setDaemon(True)#守护线程
        #self.t1.start()
    
    #串口初始化
    def serial_init(self):
        _list = list(serial.tools.list_ports.comports())
        if len(_list) == 0:
            self.port_list='null'
        else:
            for i in range(0,len(_list)):
                self.port_list.append(_list[i][0])
        return self.port_list
    
    #更新设备号
    def serial_list_update(self,event):
        win.root.init_serial_comboxlist['value']=self.serial_init(); 
        self.port_list=[]
    
    #更新波特率
    def baud_list_update(self,event):
        win.root.init_baud_comboxlist['value']=self.baud_list
        
    #设备连接
    def serial_connect(self,event):
        self.port_index=win.root.init_serial_comboxlist.current()
        self.baud_index=win.root.init_baud_comboxlist.current()
        
        #已连接，点击断开
        if self.connect_state: 
            self.ser.close()
            self.connect_state=False
            win.root.init_connect_button['text']="连接"
            win.root.list_clear() #列表清空
            win.root.axis_init() #控件初始化
            win.root.list_add("close success")
            win.root.unlock_state=False
        #未连接，点击连接
        else:
            try:
                self.ser = serial.Serial(
                    win.root.init_serial_comboxlist['value'][self.port_index],
                    int(win.root.init_baud_comboxlist['value'][self.baud_index])
                    )
            
                if self.ser.isOpen():
                    time.sleep(1.5)
                    self.connect_state=True
                    win.root.init_connect_button['text']="已连接"
                    win.root.list_add("open success")
            except:
                mb.showerror("错误","串口打开失败")
                
    #串口发送
    def serial_write(self,data):
        if self.connect_state:
            self.serial_write_norev(data)
            self.serial_read()
            #self.ser.write(binascii.a2b_hex(data)) #hex发送
            #print("send success",data)
            
    def serial_write_norev(self,data):
        self.ser.write(data.encode('utf-8')) #utf-8编码发送
            
        
    #串口读取    
    def serial_read(self):
        if self.connect_state:
            while True:
                data=self.ser.readline()
                if data=='':
                    continue
                else:
                    self.rev_data=data.strip()
                    if self.rev_data=="ok":
                        #print(self.rev_data)
                        break
        else:
            print("no serial port")

            

        
        
        
        
        
        
        
        
        
        
        
        
        
        
        

