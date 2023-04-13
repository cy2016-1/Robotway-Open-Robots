
import color_data, rgb_num, kmean_tocolor

rgbu_list = []
codeu_list = []
def color_encode_u(img_rgbu):
    global codeu_list
    rgbu_list = []
    codeu_list = []
    for i in range(0, 9):
        area = img_rgbu[color_data.area[i][0]:color_data.area[i][1], color_data.area[i][2]:color_data.area[i][3]]
        rgbu_list.append(kmean_tocolor.get_kmean_color(area))
        kmean_tocolor.a = []
        kmean_tocolor.b = []
        codeu_list.append(rgb_num.recognize_block_color(color_data.color_rgb_u, rgbu_list[i]))
    print('U:',rgbu_list)
    #print(''.join(codeu_list))
    return (''.join(codeu_list))

rgbr_list = []
coder_list = []
def color_encode_r(img_rgbr):
    global coder_list
    rgbr_list = []
    coder_list = []
    for i in range(0, 9):
        area = img_rgbr[color_data.area_r[i][0]:color_data.area_r[i][1], color_data.area_r[i][2]:color_data.area_r[i][3]]
        rgbr_list.append(kmean_tocolor.get_kmean_color(area))
        kmean_tocolor.a = []
        kmean_tocolor.b = []
        coder_list.append(rgb_num.recognize_block_color(color_data.color_rgb_r, rgbr_list[i]))
    print('R:',rgbr_list)
    return (''.join(coder_list))

rgbf_list = []
codef_list = []
def color_encode_f(img_rgbf):
    global codef_list
    rgbf_list = []
    codef_list = []
    for i in range(0, 9):
        area = img_rgbf[color_data.area[i][0]:color_data.area[i][1], color_data.area[i][2]:color_data.area[i][3]]
        rgbf_list.append(kmean_tocolor.get_kmean_color(area))
        kmean_tocolor.a = []
        kmean_tocolor.b = []
        codef_list.append(rgb_num.recognize_block_color(color_data.color_rgb_f, rgbf_list[i]))
    print('F:',rgbf_list)
    return (''.join(codef_list))

rgbd_list = []
coded_list = []
def color_encode_d(img_rgbd):
    global coded_list
    rgbd_list = []
    coded_list = []
    for i in range(0, 9):
        area = img_rgbd[color_data.area_d[i][0]:color_data.area_d[i][1], color_data.area_d[i][2]:color_data.area_d[i][3]]
        rgbd_list.append(kmean_tocolor.get_kmean_color(area))
        kmean_tocolor.a = []
        kmean_tocolor.b = []
        coded_list.append(rgb_num.recognize_block_color(color_data.color_rgb_d, rgbd_list[i]))
    print('D:',rgbd_list)
    return (''.join(coded_list))

rgbl_list = []
codel_list = []
def color_encode_l(img_rgbl):
    global codel_list
    rgbl_list = []
    codel_list = []
    for i in range(0, 9):
        area = img_rgbl[color_data.area[i][0]:color_data.area[i][1], color_data.area[i][2]:color_data.area[i][3]]
        rgbl_list.append(kmean_tocolor.get_kmean_color(area))
        kmean_tocolor.a = []
        kmean_tocolor.b = []
        codel_list.append(rgb_num.recognize_block_color(color_data.color_rgb_l, rgbl_list[i]))
    print('L',rgbl_list)
    return (''.join(codel_list))

rgbb_list = []
codeb_list = []
def color_encode_b(img_rgbb):
    global codeb_list
    rgbb_list = []
    codeb_list = []
    for i in range(0, 9):
        area = img_rgbb[color_data.area_b[8-i][0]:color_data.area_b[8-i][1], color_data.area_b[8-i][2]:color_data.area_b[8-i][3]]
        rgbb_list.append(kmean_tocolor.get_kmean_color(area))
        kmean_tocolor.a = []
        kmean_tocolor.b = []
        codeb_list.append(rgb_num.recognize_block_color(color_data.color_rgb_b, rgbb_list[i]))
    print('B:',rgbb_list)
    return (''.join(codeb_list))




