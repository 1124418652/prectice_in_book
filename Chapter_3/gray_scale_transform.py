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

dir_path = os.path.join(os.path.abspath('.'), "../src/")

def open_img(path, type = "RGB"):
	img = Image.open(path)

	if "RGB" != type.upper():
		img = img.convert("L")

	return img

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

def gray_separate(img):
    if type(np.array([1])) != type(img):
        img = np.array(img)

    height, width = img.shape
    res = np.zeros((8, height, width))

    for layer in np.linspace(1, 8, 8):
        for h in range(height):
            for w in range(width):


def show_img(img):
	if type(np.array([1, 2])) == type(img):
		img = Image.fromarray(img)

	plt.imshow(img)
	plt.show()

def main():
	path = os.path.join(dir_path, "lena.jpg")
	img = open_img(path, "gray")
	show_img(img)
	show_img(separate_trans(img, 50, 150, 200, 200))

if __name__ == '__main__':
	main()
