# -*- coding: utf-8 -*-
#########################################################################
# File Name: test.py
# Author: Hejun Xu
# mail: 1124418652@qq.com
# Created Time: 2018年10月31日 星期三 12时04分54秒
#########################################################################

import os

basePath = os.getcwd()
path = os.path.join(basePath, "file_filter.py")
print(os.stat(path))
