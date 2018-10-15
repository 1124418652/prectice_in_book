import os
import sys
import cv2
import numpy as np
import matplotlib.pyplot as plt
from PIL import *
from math import *
from pylab import mpl
mpl.rcParams['font.sans-serif'] = ['SimHei']
mpl.rcParams['axes.unicode_minus'] = False

src_path = "F:\program\computer_version\prectice_in_book\Chapter_4\src"
img_path = os.path.join(src_path, "timg.jpg")

img = Image.open(img_path).convert("L").resize((100,100))

def fourier(img):
    if np.ndarray != type(img):
        try:
            img = np.array(img)
        except:
            print("Can't convert to numpy.ndarray!")

    rows, cols = img.shape
    Fu_real = np.zeros((rows, cols))
    Fu_image = np.zeros((rows, cols))
    Fv_real = np.zeros((rows, cols))
    Fv_image = np.zeros((rows, cols))
    Fuv = np.zeros((rows, cols))

    for x in range(rows):
        for y in range(cols):
            img[x][y] = img[x][y] * pow(-1, (x + y))
    
    for u in range(rows):
        for v in range(cols):
            for y in range(cols):
                Fv_real[u][v] += img[u][y] * cos(-2 * pi * v * y / cols)
                Fv_image[u][v] += img[u][y] * sin(-2 * pi * v * y / cols)
    
    for v in range(cols):
        for u in range(rows):
            for x in range(rows):
                Fu_real[u][v] += Fv_real[x][v] * cos(-2 * pi * u * x / rows) - \
                    Fv_image[x][v] * sin(-2 * pi * u * x / rows)
                Fu_image[u][v] += Fv_real[x][v] * sin(-2 * pi * u * x / rows) + \
                    Fv_image[x][v] * cos(-2 * pi * u * x / rows)
            Fuv[u][v] = pow(pow(Fu_real[u][v], 2) + pow(Fu_image[u][v], 2), 0.5) / rows
    # for u in range(rows):
    #     for v in range(cols):
    #         for x in range(rows):
    #             for y in range(cols):
    #                 Fu_real[u][v] += img[x][y] * cos(-2 * pi * (u * x / rows + v * y / cols)) * pow(-1, x+y)
    #                 Fu_image[u][v] += img[x][y] * sin(-2 * pi * (u * x / rows + v * y / cols)) * pow(-1, x+y)

    #         Fuv[u][v] = log(pow(Fu_real[u][v], 2) + pow(Fu_image[u][v], 2), 2)

    return Fuv
    
Fuv = fourier(img)

fig = plt.figure(figsize = (10, 10))

# 绘制原图像
ax1 = fig.add_subplot(221)
ax1.imshow(img)
ax1.set_title(u"原始图像")

# 绘制傅里叶变换的图像
ax2 = fig.add_subplot(222)
ax2.imshow(Image.fromarray(Fuv))
ax2.set_title(u"傅里叶变换幅度图像")

# 绘制傅里叶逆变换的图像
# ax3 = fig.add_subplot(223)
# ax3.imshow(Image.fromarray(f1))
# ax3.set_title(u"傅里叶逆变换")

plt.tight_layout()
plt.show()