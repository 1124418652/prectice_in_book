# -*- coding: utf-8 -*-
"""
# project: Fourier Transformation
# author: xhj
# email: 1124418652@qq.com
# date: 2018 9/22
"""

import numpy as np
from PIL import Image
from math import exp, cos, pi
import matplotlib.pyplot as plt

def open_img(path, mode = "gray"):
    img = Image.open(path)

    if "gray" == mode.lower():
        img = img.convert("L")

    return img

def fourier_trans(img):
    if type(np.array([1,2])) != type(img):
        img = np.array(img)

    height, width = img.shape
    res = np.zeros((height, width))

    for u in [int(height/2)]:
        for v in range(width):
            for h in [int(height/2)]:
                for w in range(width):
                    res[u][v] += img[h][w] * cos(2 * pi * (u * h / height + v * w / width))

    return res

def main():
    path = "src/timg.jpg"
    img1 = open_img(path)
    res = fourier_trans(img1)
    fig = plt.figure()
    ax1 = fig.add_subplot(121)
    ax1.imshow(img1)
    ax2 = fig.add_subplot(122)
    ax2.imshow(Image.fromarray(res))
    plt.show()

if __name__ == '__main__':
    main()
