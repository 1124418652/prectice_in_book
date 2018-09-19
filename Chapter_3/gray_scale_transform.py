# -*- coding: utf-8 -*-
"""
# project: the algrithom of gray scale transfrom
# author:  xhj
# email:   1124418652@qq.com
# date:    2018/ 9/18
"""

import os
import sys
import time
import numpy as np
import matplotlib.pyplot as plt
from PIL import *
from math import pow
from scipy.interpolate import interp1d

dir_path = os.path.join(os.path.abspath('.'), "../src/")

def open_img(path, type = "RGB"):
	img = Image.open(path)

	if "RGB" != type.upper():
		img = img.convert("L")

	return img

# 幂率变换，进行灰度尺度的缩放
def gama_trans(img, y = 0.4):
	c = 255 / (pow(255, y))

	if type(np.array([1, 2])) != type(img):
		img = np.array(img)

	height, width = img.shape
	res = np.zeros((height, width))

	for h in range(height):
		for w in range(width):
			res[h][w] = c * pow(img[h][w], y)

	return res

# 灰度分段线性变换
def separate_trans(img, r1 = 0, s1 = 0, r2 = 255, s2 = 255):
	if type(np.array([1])) != type(img):
		img = np.array(img)

	height, width = img.shape
	res = np.zeros((height, width))

	for h in range(height):
		for w in range(width):
			_tmp = img[h][w]

			if _tmp < r1:
				res[h][w] = int(s1 / r1 * _tmp)

			elif _tmp >= r1 and _tmp < r2:
				res[h][w] = int((s2 - s1) / (r2 - r1) * _tmp + r1)

			else:
				res[h][w] = int((255 - s2) / (255 - r1) * _tmp + r2)

	return res

# 比特平面分层
def _num2bit(num):
	b = np.zeros(8)
	i = 0

	while num > 0:
		b[i] = num % 2 
		num = int(num / 2)
		i += 1

	return b

def gray_separate(img):
    if type(np.array([1])) != type(img):
        img = np.array(img)

    height, width = img.shape
    res = np.zeros((8, height, width))

    for layer in range(8):
        for h in range(height):
            for w in range(width):
            	num = img[h][w]
            	res[layer][h][w] = _num2bit(num)[layer] * 128

    fig = plt.figure()
    for layer in range(8):
    	img = Image.fromarray(res[layer])
    	ax = fig.add_subplot(2, 4, layer + 1)
    	title = "layer: " + str(layer)
    	ax.set_title(title)
    	ax.imshow(img)
    plt.show()

# histogram equalization
def hist_equal(img):
	if type(np.array([1,2])) != img:
		img = np.array(img)

	if 2 == len(img.shape):          # 单通道图像
		accumulate = np.zeros(256)
		height, width = img.shape
		img = img.flatten()
		
		for val in img:
			accumulate[val] += 1 

		cum = accumulate.cumsum()
		cum = cum / cum[-1] * 255
		f = interp1d(range(256), cum, kind="linear")
		im2 = f(img)

		fig = plt.figure()
		ax1 = fig.add_subplot(131)
		ax1.plot(range(256), accumulate)
		ax2 = fig.add_subplot(132)
		ax2.imshow(Image.fromarray(img.reshape((height, width))))
		ax3 = fig.add_subplot(133)
		ax3.imshow(Image.fromarray(im2.reshape(height, width)))
		plt.show()

def show_img(img):
	if type(np.array([1, 2])) == type(img):
		img = Image.fromarray(img)

	plt.imshow(img)
	plt.show()

def main():
	path = os.path.join(dir_path, "lena.jpg")
	img = open_img(path, "gray")
	# gray_separate(img)
	hist_equal(img)

if __name__ == '__main__':
	main()
