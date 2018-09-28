## 一维离散傅里叶变换 
傅里叶变换公式：\begin{equation}F(u)=\sum_{x=0}^{M-1}f(x)e^{-j2\pi\frac xM u},\qquad(u=0,1,...,M-1)\end{equation}
傅里叶逆变换公式：\begin{equation}f(x)=\frac 1M \sum_{u=0}^{M-1}F(u)e^{j2\pi\frac uM x}, \qquad(x=0,1,...,M-1)\end{equation}