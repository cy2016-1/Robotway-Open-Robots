
import cv2
import numpy as np


def image_deal_u(img):
    #resu = cv2.resize(img, None, fx=0.5, fy=0.5, interpolation=cv2.INTER_CUBIC)
    # cv2.imshow("resu", resu)
    roiu = img[57:344, 248:756]
    # cv2.imshow("roiu", roiu)
    pts1 = np.float32([[313-248, 57-57], [248-248, 331-57], [756-248, 344-57], [706-248, 70-57]])
    pts2 = np.float32([[0, 0], [0, 90], [90, 90], [90, 0]])
    M = cv2.getPerspectiveTransform(pts1, pts2)
    dstu = cv2.warpPerspective(roiu, M, (90, 90))
    # cv2.imshow("dstu", dstu)
    img_rgbu = cv2.cvtColor(dstu, cv2.COLOR_BGR2RGB)
    # cv2.imshow("img_rgbu", img_rgbu)
    cv2.imwrite("E:\\Python_project/cube_img/img_rgbu.jpg", img_rgbu)
    return img_rgbu


def image_deal_r(img):
    # resr = cv2.resize(img, None, fx = 0.5, fy = 0.5, interpolation=cv2.INTER_CUBIC)
    # cv2.imshow("resr", resr)
    roir = img[38:398, 15:366]
    pts1 = np.float32([[22-15, 38-38], [15-15, 387-38], [361-15, 392-38], [366-15, 42-38]])
    pts2 = np.float32([[0, 0], [0, 90], [90, 90], [90, 0]])
    M = cv2.getPerspectiveTransform(pts1, pts2)
    dstr = cv2.warpPerspective(roir, M, (90, 90))
    # cv2.imshow("dstr", dstr)
    img_rgbr = cv2.cvtColor(dstr, cv2.COLOR_BGR2RGB)
    # cv2.imshow("img_rgbr", img_rgbr)
    cv2.imwrite("E:\\Python_project/cube_img/img_rgbr.jpg", img_rgbr)
    return img_rgbr


def image_deal_f(img):
    # resf = cv2.resize(img, None, fx = 0.5, fy = 0.5, interpolation=cv2.INTER_CUBIC)
    # cv2.imshow("resf", resf)
    roif = img[370:646, 249:762]
    # cv2.imshow("roif", roif)
    pts1 = np.float32([[249-249, 370-370], [306-249, 646-370], [703-249, 645-370], [762-249, 378-370]])
    pts2 = np.float32([[0, 0], [0, 90], [90, 90], [90, 0]])
    M = cv2.getPerspectiveTransform(pts1, pts2)
    dstf = cv2.warpPerspective(roif, M, (90, 90))
    # cv2.imshow("dstf", dstf)
    img_rgbf = cv2.cvtColor(dstf, cv2.COLOR_BGR2RGB)
    # cv2.imshow("img_rgbf", img_rgbf)
    cv2.imwrite("E:\\Python_project/cube_img/img_rgbf.jpg", img_rgbf)
    return img_rgbf


def image_deal_d(img):
    # resd = cv2.resize(img, None, fx=1, fy=1, interpolation=cv2.INTER_CUBIC)
    # cv2.imshow("resd", resd)
    rows, cols, ch = img.shape
    # 这里的第一个参数为旋转中心，第二个为旋转角度，第三个为旋转后的缩放因子
    # 可以通过设置旋转中心，缩放因子，以及窗口大小来防止旋转后超出边界的问题
    M = cv2.getRotationMatrix2D((cols / 2, rows / 2), 90, 1)
    # 第三个参数是输出图像的尺寸中心
    dst_d = cv2.warpAffine(img, M, (2 * cols, 2 * rows))

    roid = dst_d[17:284, 171:480]
    # cv2.imshow("roid", roid)
    pts1 = np.float32([[200-171, 30-17], [171-171, 284-17], [480-171, 270-17], [423-171, 17-17]])
    pts2 = np.float32([[0, 0], [0, 90], [90, 90], [90, 0]])
    M = cv2.getPerspectiveTransform(pts1, pts2)
    dstd = cv2.warpPerspective(roid, M, (90, 90))
    # cv2.imshow("dstd", dstd)
    img_rgbd = cv2.cvtColor(dstd, cv2.COLOR_BGR2RGB)
    cv2.imwrite("E:\\Python_project/cube_img/img_rgbd.jpg", img_rgbd)
    # cv2.imshow("img_rgbd", img_rgbd)
    return img_rgbd


def image_deal_l(img):
    # resl = cv2.resize(img, None, fx=0.5, fy=0.5, interpolation=cv2.INTER_CUBIC)
    # cv2.imshow("resl", resl)
    roil = img[52:425, 155:524]
    pts1 = np.float32([[155-155, 52-52], [160-155, 425-52], [524-155, 411-52], [520-155, 54-52]])
    pts2 = np.float32([[0, 0], [0, 90], [90, 90], [90, 0]])
    M = cv2.getPerspectiveTransform(pts1, pts2)
    dstl = cv2.warpPerspective(roil, M, (90, 90))
    # cv2.imshow("dstl", dstl)
    img_rgbl = cv2.cvtColor(dstl, cv2.COLOR_BGR2RGB)
    # cv2.imshow("img_rgbl", img_rgbl)
    cv2.imwrite("E:\\Python_project/cube_img/img_rgbl.jpg", img_rgbl)
    return img_rgbl


def image_deal_b(img):
    rows, cols, ch = img.shape
    # 这里的第一个参数为旋转中心，第二个为旋转角度，第三个为旋转后的缩放因子
    # 可以通过设置旋转中心，缩放因子，以及窗口大小来防止旋转后超出边界的问题
    M = cv2.getRotationMatrix2D((cols / 2, rows / 2), 90, 1)
    # 第三个参数是输出图像的尺寸中心
    dst_b = cv2.warpAffine(img, M, (2 * cols, 2 * rows))
    # resb = cv2.resize(img, None, fx=1, fy=1, interpolation=cv2.INTER_CUBIC)
    # cv2.imshow("resb", resb)
    roib = dst_b[297:508, 165:467]
    # cv2.imshow("roib", roib)

    pts1 = np.float32([[165-165, 315-297], [230-165, 508-297], [457-165, 498-297], [467-165, 297-297]])
    pts2 = np.float32([[0, 0], [0, 90], [90, 90], [90, 0]])
    M = cv2.getPerspectiveTransform(pts1, pts2)
    dstb = cv2.warpPerspective(roib, M, (90, 90))
    # cv2.imshow("dstb", dstb)
    img_rgbb = cv2.cvtColor(dstb, cv2.COLOR_BGR2RGB)
    # cv2.imshow("img_rgbb", img_rgbb)
    cv2.imwrite("E:\\Python_project/cube_img/img_rgbb.jpg", img_rgbb)
    return img_rgbb


