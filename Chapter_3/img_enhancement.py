# -*- coding: utf-8 -*-
"""
# project: Image Enhancement
# author:  xhj
# email:   1124418652@qq.com
# date:    2018/ 9/20
"""

import numpy as np 
import matplotlib.pyplot as plt
from PIL import Image 
from gray_scale_transform import *

def main():
	dir_path = os.path.join(os.path.abspath("."), "../src/")
	path = os.path.join(dir_path, "bone.jpg")
	img = open_img(path, "gray")
	img2  = blurry(img, "median")
	gray_separate(img)
if __name__ == '__main__':
	main()
