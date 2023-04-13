
import cv2
import numpy as np

def nothing(x):
    pass

lower_color = np.array([0, 0, 0])       # rgb
higher_color = np.array([0, 0, 0])

def get_hsv():
    lower_color[0] = cv2.getTrackbarPos("LB", "image")
    lower_color[1] = cv2.getTrackbarPos("LG", "image")
    lower_color[2] = cv2.getTrackbarPos("LR", "image")
    higher_color[0] = cv2.getTrackbarPos("HB", "image")
    higher_color[1] = cv2.getTrackbarPos("HG", "image")
    higher_color[2] = cv2.getTrackbarPos("HR", "image")

    print(lower_color, higher_color)


cv2.namedWindow("image", cv2.WINDOW_AUTOSIZE)

cv2.createTrackbar("LB", "image", 0, 255, nothing)
cv2.createTrackbar("HB", "image", 0, 255, nothing)
cv2.createTrackbar("LG", "image", 0, 255, nothing)
cv2.createTrackbar("HG", "image", 0, 255, nothing)
cv2.createTrackbar("LR", "image", 0, 255, nothing)
cv2.createTrackbar("HR", "image", 0, 255, nothing)


def threshold_cal(image, dst):
    global b, g, r
    rows, cows, ch  = dst.shape
    if ch == 3:
        for i in range(0, rows):
            for j in range(0, cows):
                x = i
                y = j
                b = image[y, x][0]
                g = image[y, x][1]
                r = image[y, x][2]
                if ((lower_color[0] <= b <= higher_color[0]) and (lower_color[1] <= g <= higher_color[1]) and (lower_color[2] <= r <= higher_color[2])):
                    dst[y, x][0] = 255
                    dst[y, x][1] = 255
                    dst[y, x][2] = 255
                else:
                    dst[y, x][0] = 0
                    dst[y, x][1] = 0
                    dst[y, x][2] = 0

hsv_h = hsv_s = hsv_v = 0
frame = cv2.imread("E:\\Python_project/cube_img/img_rgbd.jpg")
# frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)
# frame_hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
# frame_hsv = frame_hsv[0:100, 0:100]
dst = frame.copy()
dst = dst[0:300, 0:300]         # [ 61 199   0] [155 235 140]   [  5 185  55] [145 255 160]
#dst = dst[0:100, 100:200]          [ 49  25 200] [130 120 255]
#dst = dst[0:100, 200:300]          [ 44 115 200] [140 195 255]
#dst = dst[100:200, 0:100]              [75 50  0] [225 165 110]
#dst = dst[100:200, 100:200]            [165 192 202] [245 255 255]
#dst = dst[100:200, 200:300]            [  0 168 145] [100 255 255]
#dst = dst[200:300, 0:100]
#dst = dst[200:300, 100:200]
#dst = dst[200:300, 200:300]
Original = dst.copy()
cv2.imshow("Original", Original)
#list = get_area_hsv(frame_hsv)
while(True):
    #print(dst.shape)

    #hsv_mask = cv2.inRange(frame_hsv, lower_color, higher_color)
    get_hsv()
    threshold_cal(frame, dst)
    #cv2.imshow("frame", frame)
    #cv2.imshow("mask", hsv_mask)
    cv2.imshow("rgb", dst)

    c = cv2.waitKey(25)          #等待25ms
    if c == ord("q"):           #27为ESC的ASCII码    c == ord("q")，获取q键的ASCII码
        break

print(list)
print("Hello,world")
cv2.destroyAllWindows()

