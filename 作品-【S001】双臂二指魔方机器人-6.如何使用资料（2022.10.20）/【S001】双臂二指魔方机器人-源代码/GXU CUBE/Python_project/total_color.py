
import cv2
import numpy as np
import rgb_num, rgb_encode, rgb_num, rgb_output,rgb_encode
import threading
import multiprocessing

output = ''
output_U = ''
output_R = ''
output_F = ''
output_D = ''
output_L = ''
output_B = ''

img_rgbu = []
img_rgbr = []
img_rgbf = []
img_rgbd = []
img_rgbl = []
img_rgbb = []

#img_rgbl = cv2.imread("C:\\Users/13672/Desktop/Saved Pictures/cube/img_rgbl.png") #读取照片
#img_rgbd = cv2.imread("C:\\Users/13672/Desktop/Saved Pictures/cube/img_rgbd.png")  # 读取照片
#img_rgbb = cv2.imread("C:\\Users/13672/Desktop/Saved Pictures/cube/img_rgbb.png")  # 读取照片

def pocess_u():
    global img_rgbu, img_rgbf
    capture = cv2.VideoCapture(3, cv2.CAP_DSHOW)  # 0是第一个摄像头，有多个摄像头则有0  1 2 3，读取视频填写路径即可
    capture.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
    capture.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
    capture.set(cv2.CAP_PROP_FOURCC,cv2.VideoWriter_fourcc('M','J','P','G'))
    ret, frame = capture.read()
    #c = cv2.waitKey(25)  # 等待25ms
    img_up = frame
    img_rgbu = rgb_output.image_deal_u(img_up)
    img_rgbf = rgb_output.image_deal_f(img_up)
    cv2.imwrite("E:\\Python_project/cube_img/img_up.jpg", img_up)
    #img_rgbu = cv2.imread("C:\\Users/13672/Desktop/Saved Pictures/cube/img_rgbu.png")  # 读取照片
    #img_rgbf = cv2.imread("C:\\Users/13672/Desktop/Saved Pictures/cube/img_rgbf.png")  # 读取照片
    print("1")

def pocess_r():
    global img_rgbr
    capture = cv2.VideoCapture(4, cv2.CAP_DSHOW)  # 0是第一个摄像头，有多个摄像头则有0  1 2 3，读取视频填写路径即可
    capture.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
    capture.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
    capture.set(cv2.CAP_PROP_FOURCC,cv2.VideoWriter_fourcc('M','J','P','G'))
    ret, frame = capture.read()
    #c = cv2.waitKey(25)  # 等待25ms
    img_right = frame
    img_rgbr = rgb_output.image_deal_r(img_right)
    cv2.imwrite("E:\\Python_project/cube_img/img_right.jpg", img_right)
    #img_rgbr = cv2.imread("C:\\Users/13672/Desktop/Saved Pictures/cube/img_rgbr.png")  # 读取照片
    print("2")

def pocess_d():
    global img_rgbd, img_rgbb
    capture = cv2.VideoCapture(1, cv2.CAP_DSHOW)  # 0是第一个摄像头，有多个摄像头则有0  1 2 3，读取视频填写路径即可
    capture.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
    capture.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
    capture.set(cv2.CAP_PROP_FOURCC,cv2.VideoWriter_fourcc('M','J','P','G'))
    ret, frame = capture.read()
    #c = cv2.waitKey(25)  # 等待25ms
    img_down = frame
    img_rgbd = rgb_output.image_deal_d(img_down)
    img_rgbb = rgb_output.image_deal_b(img_down)
    cv2.imwrite("E:\\Python_project/cube_img/img_down.jpg", img_down)
    print("3")

def pocess_l():
    global img_rgbl
    capture = cv2.VideoCapture(2, cv2.CAP_DSHOW)  # 0是第一个摄像头，有多个摄像头则有0  1 2 3，读取视频填写路径即可
    capture.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
    capture.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
    capture.set(cv2.CAP_PROP_FOURCC,cv2.VideoWriter_fourcc('M','J','P','G'))
    ret, frame = capture.read()
    #c = cv2.waitKey(25)  # 等待25ms
    img_left = frame
    img_rgbl = rgb_output.image_deal_l(img_left)
    cv2.imwrite("E:\\Python_project/cube_img/img_left.jpg", img_left)
    print("4")

def read_u():
    global output_U
    output_U = rgb_encode.color_encode_u(img_rgbu)


def read_r():
    global output_R
    output_R = rgb_encode.color_encode_r(img_rgbr)


def read_f():
    global output_F
    output_F = rgb_encode.color_encode_f(img_rgbf)


def read_d():
    global output_D
    output_D = rgb_encode.color_encode_d(img_rgbd)


def read_l():
    global output_L
    output_L = rgb_encode.color_encode_l(img_rgbl)


def read_b():
    global output_B
    output_B = rgb_encode.color_encode_b(img_rgbb)


def deal_color():
#if __name__ == '__main__':
    global output
    pocess = []
    p1 = threading.Thread(target=pocess_u)
    p2 = threading.Thread(target=pocess_r)
    p3 = threading.Thread(target=pocess_d)
    p4 = threading.Thread(target=pocess_l)
    pocess.append(p1)
    pocess.append(p2)
    pocess.append(p3)
    pocess.append(p4)
    for i in pocess:
        i.start()
    #for i in pocess:
        i.join()

    rgb_num.color_num(img_rgbu, img_rgbr, img_rgbf, img_rgbd, img_rgbl, img_rgbb)

    thread = []
    t1 = threading.Thread(target=read_u)
    t2 = threading.Thread(target=read_r)
    t3 = threading.Thread(target=read_f)
    t4 = threading.Thread(target=read_d)
    t5 = threading.Thread(target=read_l)
    t6 = threading.Thread(target=read_b)
    thread.append(t1)
    thread.append(t2)
    thread.append(t3)
    thread.append(t4)
    thread.append(t5)
    thread.append(t6)
    for i in thread:
        i.start()
    for i in thread:
        i.join()
    print(output_U)
    print(output_R)
    print(output_F)
    print(output_D)
    print(output_L)
    print(output_B)

    output = output_U + output_R + output_F + output_D + output_L + output_B
    print(output)
    location = 0;
    num = [0, 0, 0, 0, 0, 0]

    for i in range(0,54):
        if(output[i] == 'E'):
            location = i
        if(output[i] == 'U'):
            num[0] = num[0] + 1
        if (output[i] == 'R'):
            num[1] = num[1] + 1
        if (output[i] == 'F'):
            num[2] = num[2] + 1
        if (output[i] == 'D'):
            num[3] = num[3] + 1
        if (output[i] == 'L'):
            num[4] = num[4] + 1
        if (output[i] == 'B'):
            num[5] = num[5] + 1
    print(location,num)
    for i in range(0,6):
        if((num[i]) != 9):
            print(output[location])
            output = output.replace('E', '%s'%rgb_num.color_str[i])
    print(output)
deal_color()