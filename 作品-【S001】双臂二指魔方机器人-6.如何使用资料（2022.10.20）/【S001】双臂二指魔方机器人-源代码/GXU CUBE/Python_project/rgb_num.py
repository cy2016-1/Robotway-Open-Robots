

import color_data
import kmean_tocolor

point_roi = [32, 57, 35, 57]        # 中间色块区域
hsv_h = hsv_s = hsv_v = 0


def recognize_mid_color(hsv_color, mid_hsv):            #hsv_color  橙 蓝 绿 红 白 黄  num U R F D L B
    if ((hsv_color[0][0] <= mid_hsv[0] <= hsv_color[1][0]) and (hsv_color[0][1] <= mid_hsv[1] <= hsv_color[1][1]) and (
            hsv_color[0][2] <= mid_hsv[2] <= hsv_color[1][2])):
        return 0
    elif ((hsv_color[2][0] <= mid_hsv[0] <= hsv_color[3][0]) and (hsv_color[2][1] <= mid_hsv[1] <= hsv_color[3][1]) and (
            hsv_color[2][2] <= mid_hsv[2] <= hsv_color[3][2])):
        return 1
    elif ((hsv_color[4][0] <= mid_hsv[0] <= hsv_color[5][0]) and (hsv_color[4][1] <= mid_hsv[1] <= hsv_color[5][1]) and (
            hsv_color[4][2] <= mid_hsv[2] <= hsv_color[5][2])):
        return 2
    elif ((hsv_color[6][0] <= mid_hsv[0] <= hsv_color[7][0]) and (hsv_color[6][1] <= mid_hsv[1] <= hsv_color[7][1]) and (
            hsv_color[6][2] <= mid_hsv[2] <= hsv_color[7][2])):
        return 3
    elif ((hsv_color[8][0] <= mid_hsv[0] <= hsv_color[9][0]) and (hsv_color[8][1] <= mid_hsv[1] <= hsv_color[9][1]) and (
            hsv_color[8][2] <= mid_hsv[2] <= hsv_color[9][2])):
        return 4
    elif ((hsv_color[10][0] <= mid_hsv[0] <= hsv_color[11][0]) and (hsv_color[10][1] <= mid_hsv[1] <= hsv_color[11][1]) and (
            hsv_color[10][2] <= mid_hsv[2] <= hsv_color[11][2])):
        return 5
    else:
        return 6


def color_deal(image_rgb, rgb_color):
    mid_area = image_rgb[point_roi[0]: point_roi[1], point_roi[2]: point_roi[3]]
    mid_rgb = kmean_tocolor.get_kmean_color(mid_area)
    kmean_tocolor.a = []
    kmean_tocolor.b = []
    print(mid_rgb)
    return recognize_mid_color(rgb_color, mid_rgb)

color_str = 'URFDLBE'
co_num = []
color_numstr = ['E', 'E', 'E', 'E', 'E', 'E', 'E']


def color_num(img_rgbu, img_rgbr, img_rgbf, img_rgbd, img_rgbl, img_rgbb):
    global color_numstr, co_num
    co_num = []
    co_num.append(color_deal(img_rgbu, color_data.color_rgb_u))
    co_num.append(color_deal(img_rgbr, color_data.color_rgb_r))
    co_num.append(color_deal(img_rgbf, color_data.color_rgb_f))
    co_num.append(color_deal(img_rgbd, color_data.color_rgb_d))
    co_num.append(color_deal(img_rgbl, color_data.color_rgb_l))
    co_num.append(color_deal(img_rgbb, color_data.color_rgb_b))
    print(co_num)
    for i in range(0, 6):
        color_numstr[co_num[i]] = color_str[i]


def recognize_block_color(hsv_color, area_hsv):            #hsv_color  绿 红 蓝 橙 黄 白  num U R F D L B
    if ((hsv_color[0][0] <= area_hsv[0] <= hsv_color[1][0]) and (hsv_color[0][1] <= area_hsv[1] <= hsv_color[1][1]) and (
            hsv_color[0][2] <= area_hsv[2] <= hsv_color[1][2])):
        return color_numstr[0]
    if ((hsv_color[2][0] <= area_hsv[0] <= hsv_color[3][0]) and (hsv_color[2][1] <= area_hsv[1] <= hsv_color[3][1]) and (
            hsv_color[2][2] <= area_hsv[2] <= hsv_color[3][2])):
        return color_numstr[1]
    if ((hsv_color[4][0] <= area_hsv[0] <= hsv_color[5][0]) and (hsv_color[4][1] <= area_hsv[1] <= hsv_color[5][1]) and (
            hsv_color[4][2] <= area_hsv[2] <= hsv_color[5][2])):
        return color_numstr[2]
    if ((hsv_color[6][0] <= area_hsv[0] <= hsv_color[7][0]) and (hsv_color[6][1] <= area_hsv[1] <= hsv_color[7][1]) and (
            hsv_color[6][2] <= area_hsv[2] <= hsv_color[7][2])):
        return color_numstr[3]
    if ((hsv_color[8][0] <= area_hsv[0] <= hsv_color[9][0]) and (hsv_color[8][1] <= area_hsv[1] <= hsv_color[9][1]) and (
            hsv_color[8][2] <= area_hsv[2] <= hsv_color[9][2])):
        return color_numstr[4]
    if ((hsv_color[10][0] <= area_hsv[0] <= hsv_color[11][0]) and (hsv_color[10][1] <= area_hsv[1] <= hsv_color[11][1]) and (
            hsv_color[10][2] <= area_hsv[2] <= hsv_color[11][2])):
        return color_numstr[5]
    else:
        return 'E'




