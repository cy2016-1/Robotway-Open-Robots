
import cv2
import numpy as np

point = [(389, 219), (557, 380), (722, 218), (553, 103)]



def define_roi():

    img2 = img[90:390, 380:725]
    #cv2.imshow("img2", img2)
    relove_roi(img2)

def roi_change(image):
    # rows, cols, ch = image.shape
    #pts1 = np.float32([[10, 9], [14, 269], [274, 264], [269, 8]])
    #pts1 = np.float32([[10, 13], [11, 249], [248, 247], [248, 12]])
    #pts1 = np.float32([[11, 8], [17, 228], [237, 223], [230, 6]])
    #pts1 = np.float32([[10, 8], [19, 243], [251, 235], [250, 6]])
    #pts1 = np.float32([[4, 4], [8, 239], [243, 235], [244, 4]])
    pts1 = np.float32([[0, 0], [0, image.shape[1]], [image.shape[0], image.shape[1]], [image.shape[0], 0]])
    pts2 = np.float32([[0, 0], [0, 90], [90, 90], [90, 0]])
    M = cv2.getPerspectiveTransform(pts1, pts2)
    dst = cv2.warpPerspective(image, M, (90, 90))
    cv2.imshow("dst", dst)
    cv2.imwrite("C:/Users/13672/Desktop/Saved Pictures/cube/img_rgbb.png", dst)
    #gray_deal(dst)

def relove_roi(image):
    rows, cols, ch = image.shape
    # 这里的第一个参数为旋转中心，第二个为旋转角度，第三个为旋转后的缩放因子
    # 可以通过设置旋转中心，缩放因子，以及窗口大小来防止旋转后超出边界的问题
    M = cv2.getRotationMatrix2D((cols / 2, rows / 2), 90, 1)
    # 第三个参数是输出图像的尺寸中心
    dst2 = cv2.warpAffine(image, M, (2 * cols, 2 * rows))
    cv2.imshow("dst2", dst2)
    #roi_change(dst2)
    cv2.imwrite("E:\\Python_project/cube_img/dst2.jpg", dst2)

def gray_deal(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    ret, thresh1 = cv2.threshold(gray, 110, 240, cv2.THRESH_BINARY)
    cv2.imshow("thresh1", thresh1)

    res = cv2.bitwise_and(image, image, mask = thresh1)
    cv2.imshow("res", res)

    ROIS = [[143, 242], [245, 244]]
    print(ROIS[0])
    mid_hsv = [[0, 0, 0], [0, 0, 0]]
    for i in range(0, len(ROIS)):
        mid_hsv[i] = color_point(ROIS[i][0], ROIS[i][1], res)
    print(mid_hsv, len(mid_hsv))
    color_define(mid_hsv)

    #color_recognize(res)
    #blurred = cv2.GaussianBlur(gray, (3, 3), 0)
    #cv2.imshow("blurred", blurred)

    canny = cv2.Canny(thresh1, 50, 200, L2gradient = True)
    cv2.imshow("canny", canny)

    kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (2, 2))

    binary_dilated = cv2.dilate(canny, kernel, iterations=5)
    cv2.imshow("binary_dilated", binary_dilated)

    # 中值滤波
    #blur = cv2.medianBlur(image, 5)
    #cv2.imshow("blur", blur)

    canny_deal(binary_dilated, image)
    contours, hierarchy = cv2.findContours(binary_dilated, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    img = cv2.drawContours(image, contours, -1, (0, 255, 0), 1)
    cv2.imshow("img", img)

def canny_deal(image,img):
    (contours, hierarchy) = cv2.findContours(image.copy(), cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    candidates = []
    hierarchy = hierarchy[0]

    index = 0
    pre_cX = 0
    pre_cY = 0
    center = []
    for component in zip(contours, hierarchy):
        contour = component[0]
        peri = cv2.arcLength(contour, True)
        approx = cv2.approxPolyDP(contour, 0.1 * peri, True)
        area = cv2.contourArea(contour)
        corners = len(approx)

        # compute the center of the contour
        M = cv2.moments(contour)

        if M["m00"]:
            cX = int(M["m10"] / M["m00"])
            cY = int(M["m01"] / M["m00"])
        else:
            cX = None
            cY = None

        if 14000 < area < 20000 and cX is not None:
            tmp = {'index': index, 'cx': cX, 'cy': cY, 'contour': contour}
            center.append(tmp)
            index += 1

    center.sort(key=lambda k: (k.get('cy', 0)))
    row1 = center[0:3]
    row1.sort(key=lambda k: (k.get('cx', 0)))
    row2 = center[3:6]
    row2.sort(key=lambda k: (k.get('cx', 0)))
    row3 = center[6:9]
    row3.sort(key=lambda k: (k.get('cx', 0)))

    center.clear()
    center = row1 + row2 + row3

    for component in center:
        candidates.append(component.get('contour'))

    cv2.drawContours(img, candidates, -1, (0, 0, 255), 3)

    cv2.imshow("image", img)

def color_recognize(image):

    image_hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
    cv2.imshow("hsv", image_hsv)

    ROIS = np.array([[34, 36, 30, 30], [224, 37, 30, 30]])
     #       [], (129, 133, 30, 30), [230, 137, 30, 30],
     #       (35, 227, 30, 30), (131, 231, 30, 30), (229, 230, 30, 30)]
    for i in ROIS:
        rectangles = cv2.rectangle(image, ROIS[i], color=[0, 255, 255])

    cv2.imshow("rectangles", rectangles)

def color_point(x1, y1, res):
    color = res[y1, x1]
    mid_color = (color[0], color[1], color[2])
    print(mid_color)
    return (mid_color)

blue = [(84, 102, 159), (255, 255, 255)]

def color_define(mids):
    s = ''
    for rgb in mids:
        if ((178 <= rgb[0] <= 255) and (75 <= rgb[1] <= 255) and (75 <= rgb[2] <= 148)):
            s += 'D'
        else:
            s += 'B'
    print(s)

# 创建图像与窗口并将窗口与回调函数绑定
img = cv2.imread("E:\\Python_project/cube_img/img_d.jpg")
#img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
#roi_change(img)
relove_roi(img)
cv2.imshow("img", img)
#cv2.imwrite("C:/Users/13672/Desktop/Saved Pictures/cube/img_rgbu.png", img)

#define_roi()


while True:
    key = cv2.waitKey(1) & 0xFF
    if key == 27:
        break

cv2.destroyAllWindows()
