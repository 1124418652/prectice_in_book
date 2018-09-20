# -*- coding: utf-8 -*-
"""
# project: Gauss
# author:  xhj
# email:   1124418652@qq.com
# date:    2018/ 9/20
"""
import math
import numpy as np 
import matplotlib.pyplot as plt 


def cal_guass(size, sigma = 1):
	n = (size - 1) / 2
	kernal = np.zeros((size, size))

	for h in range(size):
		for w in range(size):
			kernal[h][w] = (1 / (2 * math.pi * sigma * sigma)) *\
				math.exp(- (pow(abs(h - n), 2) + pow(abs(w - n), 2)) / (2 * pow(sigma, 2)))

	min_v = kernal.min()
	kernal = (kernal / min_v).astype(np.int32)

	return kernal

def main():
	kernal = cal_guass(3, 0.840896)
	print(kernal)

if __name__ == '__main__':
	main()