
# coding: utf-8

from sklearn.cluster import KMeans
import matplotlib.pyplot as plt
import argparse
import cv2
import numpy as np

image = cv2.imread("E:\\Python_project/cube_img/img_rgbr.jpg")
image = image[60:90, 25:58]  #下
#image = image[31:60, 60:90]  #右
#image = image[30:60, 0:30]  #左
#image = image[0:24, 65:90]
#image = image[65:90, 0:24]
#image = image[33:57, 0:24]
image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

# show our image
plt.figure()
plt.axis("off")				# 做正方形，关闭坐标轴
plt.imshow(image)

image = image.reshape((image.shape[0] * image.shape[1], 3))

clt = KMeans(n_clusters=3)
clt.fit(image)

numLabels =np.arange(0, len(np.unique(clt.labels_)) + 1)		# 4

(hist, _) = np.histogram(clt.labels_, bins = numLabels)
hist = hist.astype("float")
hist /= hist.sum()			# 权重
print(hist)

clt.cluster_centers_
print(clt.cluster_centers_)
print(len(clt.cluster_centers_))
bar = np.zeros((50, 300, 3), dtype = "uint8")
startX = 0
for (percent, color) in zip(hist, clt.cluster_centers_):
		# plot the relative percentage of each cluster
		endX = startX + (percent * 300)
		cv2.rectangle(bar, (int(startX), 0), (int(endX), 50),
			color.astype("uint8").tolist(), -1)
		startX = endX

plt.figure()
plt.axis("off")
plt.imshow(bar)
plt.show()

