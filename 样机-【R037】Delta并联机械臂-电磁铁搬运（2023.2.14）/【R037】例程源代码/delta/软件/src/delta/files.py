# -*- coding: utf-8 -*-
#################################

#files

#################################
import tkFileDialog
import win

class Files():
    
    def __init__(self):
        self.os_str=""
        
    #文件保存
    def file_save(self,_len):
        self.f=tkFileDialog.asksaveasfile(title="选择文件",\
                                            filetypes=[\
                                            ('Nc','*.nc'),\
                                            ('Gcode','*.gcode'),\
                                            ('Txt','*.txt'),\
                                             ('All Files', '*')
                                            ])
        if self.f is None:
            return
        for i in range(0,_len):
            self.os_str = win.root.action_form.init_action_list.get(i)+'\n'
            self.f.write(self.os_str)
        self.f.close()
        return self.f        
        
    #文件读取
    def file_read(self):
        self.f=tkFileDialog.askopenfilename(title="选择文件",\
                                            filetypes=[\
                                            ('Nc','*.nc'),\
                                            ('Gcode','*.gcode'),\
                                            ('Txt','*.txt'),\
                                             ('All Files', '*')
                                            ])
        if self.f is None:
            return
        try:
            self.of=open(self.f,'r')
            for line in self.of:
                end=win.root.action_form.init_action_list.size()
                win.root.action_form.init_action_list.insert(end,line.strip())     
                win.root.action_form.init_action_list.see(end)
            self.of.close()
            return self.f
        except (IOError):
            return
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        