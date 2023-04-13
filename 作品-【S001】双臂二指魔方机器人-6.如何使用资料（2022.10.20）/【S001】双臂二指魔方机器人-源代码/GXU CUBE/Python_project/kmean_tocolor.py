
# coding: utf-8

from sklearn.cluster import KMeans
import cv2
import numpy as np

a = []
b = []


def get_kmean_color(image_RGB):
    global a, b
    image_RGB = image_RGB.reshape((image_RGB.shape[0] * image_RGB.shape[1], 3))

    clt = KMeans(n_clusters=2)
    clt.fit(image_RGB)

    numLabels = np.arange(0, len(np.unique(clt.labels_)) + 1)  # 4

    (hist, _) = np.histogram(clt.labels_, bins=numLabels)
    hist = hist.astype("float")
    hist /= hist.sum()  # 权重
    #print(hist)

    clt.cluster_centers_
    #print(clt.cluster_centers_)
    #print(len(clt.cluster_centers_))

    for i in range(0, len(clt.cluster_centers_)):
        if ((clt.cluster_centers_[i][0] < 110) and (clt.cluster_centers_[i][1] < 105) and (clt.cluster_centers_[i][2] < 95)):     #颜色为黑色，舍去
            flag = False
        else:
            flag = True

        if (flag == True):
            a.append(hist[i])
            b.append(list(clt.cluster_centers_[i]))
    amax = a.index((max(a)))
    #print(a)
    #print(hist)
    #print(b)
    return b[amax]
    #print(amax)


    #print(b[amax])
    #print(b)


# image = cv2.imread("C:\\Users/13672/Desktop/Saved Pictures/cube/test1.png")
# image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
# rgb = get_kmean_color(image)
# print(b)
# b = []
# print(rgb)

