# -*- coding: utf-8 -*-
#################################

#gcode

#################################
import threading
import win

class Gcode():
    def __init__(self):
        self.list=[] #空列表
        self.h=""  #z轴高度
        self.f=""  #速度
        self.t_flag=False #线程标志
        self.which=0 #测试标志
        
        self.t1 = threading.Thread(target=self.gc_process)
        self.t1.setDaemon(True)#守护线程
        self.t1.start()
        
    def gc_init(self,b_x,b_y): #b_x/b_y　起始位置
        self.list.append("G90")
        self.list.append("G0 X0 Y0"+" Z"+self.h)
        self.list.append("M5 S255")
        self.list.append("F"+str(self.f))
        self.list.append("G0 X"+str(b_x)+" Y"+str(b_y)+" Z"+self.h)
        self.list.append("M3")
        
    def gc_add_point(self,x,y):
        self.list.append("G1 X"+str(x)+" Y"+str(y) + " Z"+self.h)
        
    def gc_add_line(self,line):
        self.list.append(line)
        
    def gc_end(self):
        self.list.append("M5")
        self.list.append("M5")
        self.list.append("G0 X0 Y0"+" Z"+self.h)
        
    def gc_clear(self):
        del self.list[:]
        
    def gc_process(self,):
        while True:
            if self.t_flag:
                for i in range(0,len(self.list)):
                    win.root.axis_send(self.list[i])
                    #win.mySerial.serial_read()
                self.gc_clear()
                self.t_flag=False
                print(self.which)
                if self.which==0x02:    #记录点测试完成后修改子窗体开启标志
                    win.root.action_form.life=True
            else:
                continue

    def gc_start(self,w): #开始哪类测试
        self.t_flag=True
        self.which=w
        #0x00 圆测试
        #0x01 矩形测试
        #0x02 记录点测试
        
        
        
        
        
        
        
        