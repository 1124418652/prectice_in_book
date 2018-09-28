import numpy as np
import matplotlib.pyplot as plt
from pylab import mpl
mpl.rcParams['font.sans-serif'] = ['SimHei']
mpl.rcParams['axes.unicode_minus'] = False
from math import pi, cos, sin, pow

a = np.zeros(100)
a[40: 60] = 1

def fourier(fx):
    num = len(fx)
    Fu_real = np.zeros(num)
    Fu_image = np.zeros(num)
    Fu_value = np.zeros(num)
    
    for u in range(num):
        for x in range(num):
            Fu_real[u] += fx[x] * cos(-2 * pi * x / num * u) * pow(-1, x)    # 将 fx 乘以 pow(-1,x) 可以将傅里叶变换的低频移到图片中间
            #print("\tu=", u, "x=", x, "\t", x*cos(2 * pi * x / num * u))
            Fu_image[u] -= fx[x] * sin(2 * pi * u / num * x) * pow(-1, x)
        Fu_value[u] = pow(pow(Fu_real[u], 2) + pow(Fu_image[u], 2), 0.5)

    return Fu_value, Fu_real, Fu_image

def infourier(Fu_real, Fu_image):
    num = len(Fu_real)
    fx = np.zeros(num)
    
    for x in range(num):
        for u in range(num):
            fx[x] += 1 / num * (Fu_real[u] * cos(2 * pi * x / num * u) - Fu_image[u] * sin(2 * pi * u / num * x)) * pow(-1, x)
    
    return fx

Fu_value, Fu_real, Fu_image = fourier(a)
fx = infourier(Fu_real, Fu_image)
#print(fx)

fig = plt.figure()

#绘制原函数的图像
ax1 = fig.add_subplot(221)
ax1.plot(a)
ax1.set_title(u"原函数")
ax1.set_xlabel(u"x")
ax1.set_ylabel(u"f(x)")

#绘制傅里叶变换的谱图
ax2 = fig.add_subplot(222)
ax2.plot(Fu_value)
ax2.set_title(u"傅里叶变换谱图")
ax2.set_xlabel(u"u")
ax2.set_ylabel(u"|F(u)|")

#绘制傅里叶逆变换的图像
ax3 = fig.add_subplot(223)
ax3.plot(fx)
ax3.set_title(u"傅里叶逆变换")
ax3.set_xlabel(u"x")
ax3.set_ylabel(u"fx")

plt.tight_layout()        #设置子图之间的间距
plt.show()