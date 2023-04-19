# -*- coding: utf-8 -*-

#################################

#win_gui

#################################
from Tkinter import *
import ttk
import funs
import math
import pyperclip #python实现复制粘贴
import tkMessageBox as mb 
from serial_cc import SerialCC
from gcode import Gcode
from files import Files

init_window = Tk()
init_window.resizable(width=False,height=False)

mySerial = SerialCC()
gcore = Gcode()
myFile=Files()

#################子窗口#####################
class WIN_FORM():
    def __init__(self,init_form_name):
        self.init_form_name=init_form_name
        self.life=False #是否已创建
        self.list_len=0 #数据列表长度
    
    def alive_i(self):
        print("i am ok!(。・`ω´・)")
    
    def on_closing(self):
        print("i will die? QAQ")
        #初始化        
        self.list_data_clear()
        self.life=False
        self.form.destroy()
        
    def creat_form(self,size):
        self.form=Toplevel()
        self.form.title(self.init_form_name)
        self.form.geometry(size)
        self.form.protocol("WM_DELETE_WINDOW",self.on_closing)
        self.life=True
    
    def copy_list(self):
        _list=""
        n_len=self.init_action_list.size()
        for i in range(0,n_len):
            _list+='"'+self.init_action_list.get(i)+"\\n"+'"'+','+'\n'
        pyperclip.copy(_list)
        self.init_path_label['text']="已复制:"+str(n_len)+"行"
        
    def run_list(self):
        n=self.init_action_list.size()
        for i in range(0,n):
            gcore.gc_add_line(self.init_action_list.get(i))
        gcore.gc_start(0x02)
        self.life=False
        
    def button_callback(self,w):
        for case in funs.switch(w):
            if case(0x00):
                #print("save")
                self.init_path_label['text']=myFile.file_save(self.init_action_list.size())
                break
            if case(0x01):
                #print("load")
                self.init_action_list.delete(0,END)
                self.init_path_label['text']=myFile.file_read()
                break
            if case(0x02):
                #print("copy")
                self.copy_list()
                break
            if case(0x03):
                #print("clear")
                self.list_data_clear()
                break
            if case(0x04):
                #print("run")
                self.run_list()
                break
    ######################form0############################            
    def list_data_add(self,data):
        try:
            self.init_action_list.insert(END,data)
            self.list_len=self.init_action_list.size()
            self.init_action_list.select_clear(0,self.list_len-1)
            self.init_action_list.select_set(END)
            self.init_action_list.see(END)
        except (AttributeError,TclError):
            return

    def list_data_init(self):
        gcore.h=str(root.z)
        gcore.f=root.init_v_entry.get()
        gcore.gc_init(root.x,root.y)
        for i in range(0,len(gcore.list)):
            self.list_data_add(gcore.list[i])
        gcore.gc_clear()
        
    def list_data_clear(self):
        self.init_action_list.delete(0,END)
        root.canvas_line_clear()
        self.list_data_init()
    
    #######################################################
        
    def add_button(self,name,n):
        for case in funs.switch(n):
            if case(0x00):
                self.init_save_btn=Button(self.form,text=name,\
                                        activeforeground="red",bg="gray",\
                                        command=lambda:self.button_callback(0x00))
                self.init_save_btn.grid(row=1,column=0,sticky=W)
                break
            if case(0x01):
                self.init_load_btn=Button(self.form,text=name,\
                                        activeforeground="red",bg="gray",\
                                        command=lambda:self.button_callback(0x01))
                self.init_load_btn.grid(row=1,column=1,sticky=W)
                break
            if case(0x02):
                self.init_copy_btn=Button(self.form,text=name,\
                                        activeforeground="red",bg="gray",\
                                        command=lambda:self.button_callback(0x02))
                self.init_copy_btn.grid(row=1,column=2,sticky=W)
                break
            if case(0x03):
                self.init_clear_btn=Button(self.form,text=name,\
                                        activeforeground="red",bg="gray",\
                                        command=lambda:self.button_callback(0x03))
                self.init_clear_btn.grid(row=1,column=3,sticky=W)
                break
            if case(0x04):
                self.init_run_btn=Button(self.form,text=name,\
                                        activeforeground="red",bg="gray",\
                                        command=lambda:self.button_callback(0x04))
                self.init_run_btn.grid(row=1,column=4,sticky=W)
                break
            
    def add_listbox(self,name,n):
        for case in funs.switch(n):
            if case(0x00):
                self.init_action_list=Listbox(self.form,heigh=22,width=45)
                self.init_action_list.grid(row=0,column=0,columnspan=5,sticky=W)
                break
            if case(0x01):
                break
    
    def add_label(self,name,n):
        for case in funs.switch(n):
            if case(0x00):
                self.init_path_label=ttk.Label(self.form,text=name,width=45)
                self.init_path_label.grid(row=2,column=0,columnspan=5,sticky=W)
                break
            if case(0x01):
                break
        
    def start_form(self):
        self.form.mainloop()

#################主窗口#####################
class WIN_GUI():   
        
        def __init__(self,init_window_name):
            self.init_window_name = init_window_name
            self.send_cmd=""
            self.min_z=-200.00 #z轴下降最大值
            self.max_z=0.00
            self.r=40.0
            self.x=0.0
            self.y=0.0
            self.z=0.0
            self.origin_x=5.0 #canvas圆起始点
            self.origin_y=5.0
            self.center_x=210.0 #canvas圆中心
            self.center_y=210.0
            self.end_x=415.0 #canvas圆终点
            self.end_y=415.0
            self.last_p_x=self.center_x #上一点x位置，
            self.last_p_y=self.center_y #上一点y位置
            self.m_d=20.0 #默认移动距离
            self.m_v=3500.0 #默认移动速度
            self.unlock_state=False
            #############子窗口#################
            self.action_form=WIN_FORM("Action")
            self.help_form=WIN_FORM("Help?")
       
       #设置窗口
        def set_init_window(self):
            self.init_window_name.title("Delta")
            self.init_window_name.geometry("640x480")    
        
        #listbox添加项
        def list_add(self,item): 
            self.init_data_list.insert(END,item)  
            self.init_data_list.see(END)
            if self.action_form.life:
                self.action_form.list_data_add(item) #子窗口动作添加
            
        #listbox清空
        def list_clear(self):
            self.init_data_list.delete(0,END)
            
        #G类型判断
        def g_type_select(self):
            if self.action_form.life:
                self.g_type="G1 X"
            else:
                self.g_type="G0 X"
            return self.g_type
            
        #坐标发送
        def axis_send(self,data):
            self.send_cmd=data
            #print(self.send_cmd)
            self.init_xd_label['text']=self.x
            self.init_yd_label['text']=self.y
            self.init_zd_label['text']=self.z
            #print(self.unlock_state)
            if self.unlock_state:
                self.list_add(self.send_cmd)
                mySerial.serial_write(self.send_cmd+'\n')
            else:
                mb.showwarning("警告","设备未解锁")
            
        #坐标初始化
        def axis_init(self):
            self.x=0.0
            self.y=0.0
            self.z=0.0
            self.last_p_x=self.center_x
            self.last_p_y=self.center_y
            self.init_xd_label['text']="0.00"
            self.init_yd_label['text']="0.00"
            self.init_zd_label['text']="0.00"
            self.init_z_scale.set(self.max_z)  
            self.canvas_point(self.center_x,self.center_y)
            self.canvas.delete("text")
            self.canvas.delete("line")
            #self.axis_send("G0 X0 Y0 Z0")
            
        #canvas画布初始化
        def canvas_init(self):
            self.canvas.create_oval(self.origin_x,self.origin_y,\
                                    self.end_x,self.end_y,fill="white")          
            self.canvas.create_line(0,210,420,210,fill="gray")
            self.canvas.create_line(210,0,210,420,fill="gray")
            self.canvas_point(self.center_x,self.center_y)
            
        #控件复位
        def reset_window(self):
            self.axis_init()
            
        #canvas画点
        def canvas_point(self,x,y):
            r_=2 #半径
            self.canvas.delete("sign")
            self.canvas.create_oval(x-r_,y-r_,\
                                    x+r_,y+r_,\
                                    fill="red",tags="sign")    
        
        #canvas画线
        def canvas_line(self,x,y):
            self.canvas.create_line(self.last_p_x,self.last_p_y,x,y,fill="red",tags="line")
            self.last_p_x=x
            self.last_p_y=y
            
        def canvas_line_clear(self):
            self.canvas.delete("line")
                
        #解锁函数
        def unlock_callback(self,event):
            self.reset_window()
            self.list_add("device reset...")
            mySerial.serial_write_norev("$H\n")
            self.unlock_state=True
            
        #canvas回调函数
        def canvas_callback(self,event,w):            
            x=round(funs.map_(event.x,\
                              self.origin_x,self.end_x,\
                              -self.r,self.r),2)
            y=round(funs.map_(event.y,\
                              self.origin_x,self.end_x,\
                              self.r,-self.r),2)
            z=self.init_z_scale.get()
            r=40.0
            r_2=x * x + y * y            
            if r_2 < (r * r):
                for case in funs.switch(w):
                    if case(0x00):                      #0x00按下发送
                        if self.z<self.max_z:
                            self.x=x
                            self.y=y
                            self.z=z
                            #绘制圆来表示所在位置
                            self.canvas_point(event.x,event.y)  
                            #绘制两点轨迹
                            self.canvas_line(event.x,event.y)
                            #设置速度
                            mySerial.serial_write("F"+str(self.init_v_entry.get())+'\n')
                            #发送坐标
                            self.axis_send(self.g_type_select() +str(self.x)+\
                                            " Y"+str(self.y)+\
                                            " Z"+str(self.z))
                        else:
                            mb.showwarning("警告","超出限位\n请下降z轴")
                        break
                    if case(0x01):                      #0x01鼠标移动
                        #删除之前的坐标点
                        self.canvas.delete("text")
                        #实时绘制坐标点
                        self.canvas.create_text(380,10,\
                                                tex=str(x)+","+str(y),\
                                                tags="text")
                        break
            else:
                self.canvas.delete("text")
                
        #scale滑动条回调函数
        def scale_callback(self,event):
            val=self.init_z_scale.get()
            if val <= self.max_z:
                if self.unlock_state:
                    self.init_zd_label['text']=val
            else:
                mb.showwarning("警告","数值不在范围内")
                
        #垂直移动
        def z_move(self):
            if mySerial.connect_state:
                self.z=self.init_z_scale.get()
                if self.z==0:
                    self.reset_window()                    
                self.axis_send(self.g_type_select() + str(self.x)+\
                               " Y"+str(self.y)+\
                               " Z"+str(self.z))
            else:
                mb.showerror("错误","串口未连接")
                self.axis_init()
                
        #鼠标释发送scale数值到串口
        def z_send(self,event):
            self.z_move()
            
        #按钮回调函数
        def button_callback(self,w):
            try:
                if mySerial.connect_state:
                    self.frm_control.focus_set()
                    for case in funs.switch(w):
                        if case(0x00):                          #0x00复位按钮
                            #self.reset_window()
                            break;
                        if case(0x01):                          #0x01上移按钮
                            #print("up")
                            self.init_z_scale.set(
                                    self.init_z_scale.get()+\
                                    float(self.init_dis_entry.get())
                                )
                            self.z_move()
                            break
                        if case(0x02):                          #0x02下降按钮
                            #print("down")
                            self.init_z_scale.set(
                                    self.init_z_scale.get()-\
                                    float(self.init_dis_entry.get())
                                )
                            self.z_move()
                            break
                        if case(0x03):                          #0x03抓取按钮
                            self.axis_send("M3")
                            break
                        if case(0x04):                          #0x04释放按钮
                            self.axis_send("M5")
                            break
                        if case(0x05):                          #0x05画圆测试按钮
                            self.move_circle()
                            break
                        if case(0x06):
                            self.reset_window()
                            self.axis_send("G92 X0 Y0 Z0")      #0X06零点设置按钮
                            break
                        if case(0x07):                          #0x07矩形测试
                            self.move_rect()
                            break
                        if case(0x08):                          #0x08设置动作组
                            self.show_form0()
                            break
                else:
                    mb.showerror("错误","串口未连接")
            except ValueError:
                mb.showerror("错误","请输入距离")

        #走圆形
        def move_circle(self):
            if self.z<self.max_z:
                gcore.h=str(self.z)
                gcore.f=self.init_v_entry.get()
                
                gcore.gc_init(self.r,0)
                theta=0
                while theta<=360:
                    x=round(self.r*math.cos(math.radians(theta)),2)
                    y=round(self.r*math.sin(math.radians(theta)),2)
                    #print(x,y,theta)
                    gcore.gc_add_point(x,y)
                    theta=theta+5
                
                gcore.gc_end()
                gcore.gc_start(0x00)
            else:
                mb.showerror("警告","请下降z轴")            

        #走矩形                
        def move_rect(self):
            if self.z<self.max_z:
                a=30 #宽
                b=30 #高
                gcore.h=str(self.z)
                gcore.f=self.init_v_entry.get()
                
                gcore.gc_init(a,0)
                gcore.gc_add_point(0,b)
                gcore.gc_add_point(-a,0)
                gcore.gc_add_point(0,-b)
                gcore.gc_add_point(a,0)
                gcore.gc_end()
                
                gcore.gc_start(0x01) #开启
                
            else:
                mb.showerror("警告","请下降z轴")            
    
        ###################添加控件及窗体#################################
        #动作组窗口
        def show_form0(self):
            if self.action_form.life: #已创建
                self.action_form.alive_i()
            else:                   #未创建
                #self.reset_window() #初始化
                self.action_form.creat_form("320x460")
                self.action_form.add_listbox("动作列表",0x00)
                #初始化列表数据
                self.action_form.list_data_clear()
                self.action_form.add_button("保存",0x00)
                self.action_form.add_button("加载",0x01)
                self.action_form.add_button("复制",0x02)
                self.action_form.add_button("清空",0x03)
                self.action_form.add_button("运行",0x04)
                self.action_form.add_label("",0x00)
                
                
                self.action_form.start_form()
        #帮助窗口
        def show_form1(self):
            if self.help_form.life:
                self.help_form.alive_i()
            else:
                self.help_form.creat_form("240x480")
                self.help_form.start_form()
        #主窗口
        def set_init_controls(self):
            #各容器
            self.frm_serial = Frame(width=380,height=25) #串口配置区
            self.frm_serial.grid(row=0,column=0,sticky=W) 
            self.frm_draw = Frame(width=420,height=420,bg="red") #坐标点击区
            self.frm_draw.grid(row=1,column=0,sticky=W)
            self.frm_control = Frame(width=180,height=420,bd=1,relief=RAISED) #控制按键区
            self.frm_control.grid(row=1,column=1,padx=15,pady=15,sticky=W)

            self.frm_serial.grid_propagate(0)
            self.frm_draw.grid_propagate(0)
            self.frm_control.grid_propagate(0)
            ###################串口部分######################
            #连接状态标签
            self.init_serial_label = ttk.Label(self.frm_serial, text="串口号")
            self.init_serial_label.grid(row=0, column=0)
            #串口号下拉列表     
            self.init_serial_comboxlist = ttk.Combobox(self.frm_serial,width=12,\
                                                        state='readonly')
            self.init_serial_comboxlist['value']=mySerial.serial_init()
            self.init_serial_comboxlist.current(0)
            mySerial.port_list=[]
            self.init_serial_comboxlist.bind("<Button-1>", mySerial.serial_list_update)
            self.init_serial_comboxlist.grid(row=0,column=1);
            
            #波特率标签
            self.init_baud_label = ttk.Label(self.frm_serial, text="波特率")
            self.init_baud_label.grid(row=0, column=2)
            #波特率列表
            self.init_baud_comboxlist = ttk.Combobox(self.frm_serial,width=12,\
                                                     state='readonly') #设置为只读模式
            self.init_baud_comboxlist['value']=mySerial.baud_list
            self.init_baud_comboxlist.current(4)
            self.init_baud_comboxlist.bind("<Button-1>", mySerial.baud_list_update)
            self.init_baud_comboxlist.grid(row=0,column=3);
            #连接按钮
            self.init_connect_button = Button(
                                                self.frm_serial,
                                                activeforeground="red",
                                                #bd=0,
                                                bg="gray",
                                                text="连接")
            self.init_connect_button.bind("<Button-1>",mySerial.serial_connect)
            self.init_connect_button.grid(row=0, column=4)
            ####################定位部分######################
            self.canvas = Canvas(self.frm_draw,width=420,height=420)
            self.canvas.bind("<Motion>",lambda event,w=0x01:self.canvas_callback(event,w))
            self.canvas.bind("<Button-1>",lambda event,w=0x00:self.canvas_callback(event,w))
            self.canvas.grid(row=0,column=0,sticky=W)
            self.canvas_init()
            
            ###################控制部分######################
            #x坐标显示
            self.init_x_label=ttk.Label(self.frm_control,text="X:")
            self.init_x_label.grid(row=0,column=0,sticky=W)
            self.init_xd_label=ttk.Label(self.frm_control,width=10,text="0.00")
            self.init_xd_label.grid(row=0,column=1,sticky=W)
            #y坐标显示
            self.init_y_label=ttk.Label(self.frm_control,text="Y:")
            self.init_y_label.grid(row=1,column=0,sticky=W)
            self.init_yd_label=ttk.Label(self.frm_control,width=10,text="0.00")
            self.init_yd_label.grid(row=1,column=1,sticky=W)
            #z坐标显示
            self.init_z_label=ttk.Label(self.frm_control,text="Z:")
            self.init_z_label.grid(row=2,column=0,sticky=W)
            self.init_zd_label=ttk.Label(self.frm_control,width=10,text="0.00")
            self.init_zd_label.grid(row=2,column=1,sticky=W)
            #z轴高度调整控件
            self.init_z_scale=Scale(self.frm_control,from_=self.max_z,\
                                        to=self.min_z,\
                                        width=10,length=100,showvalue=False,\
                                        sliderlength=15,resolution=0.1,\
                                        command=self.scale_callback)  
            self.init_z_scale.bind("<ButtonRelease-1>",self.z_send)
            self.init_z_scale.grid(row=3,column=0,sticky=E)
            #复位按钮
            self.init_res_button=Button(
                                        self.frm_control,\
                                        activeforeground="red",\
                                        #bd=0,\
                                        bg="gray",\
                                        text="解锁/复位",\
                                        )
            self.init_res_button.bind("<Button-1>",self.unlock_callback)
            self.init_res_button.grid(row=3,column=2,sticky=W)
            #移动距离
            self.init_dis_label=ttk.Label(self.frm_control,text="距离（mm）:")
            self.init_dis_label.grid(row=4,column=1,sticky=W)
            self.init_dis_entry=Entry(self.frm_control,width=10,validate="focusout")
            self.init_dis_entry.insert(0,self.m_d)
            self.init_dis_entry.grid(row=5,column=1,sticky=W)
            #运动速度
            self.init_v_label=ttk.Label(self.frm_control,text="速度（mm/min）:")
            self.init_v_label.grid(row=6,column=1,columnspan=2,sticky=W)
            self.init_v_entry=Entry(self.frm_control,width=10,validate="focusout")
            self.init_v_entry.insert(0,self.m_v)
            self.init_v_entry.grid(row=7,column=1,sticky=W)
            #上移按钮
            self.init_up_button=Button(
                                        self.frm_control,\
                                        activeforeground="red",\
                                        #bd=0,\
                                        bg="gray",\
                                        text="上升",\
                                        command=lambda:self.button_callback(0x01))
            
            self.init_up_button.grid(row=8,column=1,sticky=W)
            #下降按钮
            self.init_down_button=Button(
                                        self.frm_control,\
                                        activeforeground="red",\
                                        #bd=0,\
                                        bg="gray",\
                                        text="下降",\
                                        command=lambda:self.button_callback(0x02))
            
            self.init_down_button.grid(row=8,column=2,sticky=W)            
            #抓取按钮
            self.init_get_button=Button(
                                        self.frm_control,\
                                        activeforeground="red",\
                                        #bd=0,\
                                        bg="gray",\
                                        text="抓取",\
                                        command=lambda:self.button_callback(0x03))
            
            self.init_get_button.grid(row=9,column=1,sticky=W)             
            #释放按钮
            self.init_put_button=Button(
                                        self.frm_control,\
                                        activeforeground="red",\
                                        #bd=0,\
                                        bg="gray",\
                                        text="释放",\
                                        command=lambda:self.button_callback(0x04))
            
            self.init_put_button.grid(row=9,column=2,sticky=W)     
            #零点设置按钮
            self.init_origin_button=Button(
                                        self.frm_control,\
                                        activeforeground="red",\
                                        #bd=0,\
                                        bg="gray",\
                                        text="设置零点",\
                                        command=lambda:self.button_callback(0x06))
            self.init_origin_button.grid(row=10,column=1,sticky=W)
            #动作设置按钮
            self.init_action_button=Button(
                                        self.frm_control,\
                                        activeforeground="red",\
                                        #bd=0,\
                                        bg="gray",\
                                        text="添加动作",\
                                        command=lambda:self.button_callback(0x08))
            self.init_action_button.grid(row=10,column=2,sticky=W)
            #测试按钮(圆形)
            self.init_circle_button=Button(
                                        self.frm_control,\
                                        activeforeground="red",\
                                        #bd=0\
                                        bg="gray",\
                                        text="圆形测试",\
                                        command=lambda:self.button_callback(0x05))
            self.init_circle_button.grid(row=11,column=1,sticky=W)
            #测试按钮(矩形)
            self.init_rect_button=Button(
                                        self.frm_control,\
                                        activeforeground="red",\
                                        #bd=0,\
                                        bg="gray",\
                                        text="矩形测试",\
                                        command=lambda:self.button_callback(0x07))
            self.init_rect_button.grid(row=11,column=2,sticky=W)            
            #数据显示
            self.init_data_list=Listbox(self.frm_control,height=2,width=21)
            self.init_data_list.grid(row=12,column=1,columnspan=3,sticky=W)      
            self.init_data_list.insert(END,"G0 X0 Y0 Z0")
            
            
root = WIN_GUI(init_window)
          
def win_start():
    root.set_init_window()
    root.set_init_controls()
    
    init_window.mainloop()
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
                 