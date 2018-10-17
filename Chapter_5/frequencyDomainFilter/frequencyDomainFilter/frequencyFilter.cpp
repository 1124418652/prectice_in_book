#include "stdafx.h"
#include "frequencyFilter.h"

void opencvFilter(const Mat &src, Mat &dest, Mat &spectrum, int d0, int type, int n)
{
	int src_row = src.rows;
	int src_col = src.cols;
	int channel = src.channels();
	int row = getOptimalDFTSize(src_row);
	int col = getOptimalDFTSize(src_col);
	int dd0 = d0 * d0;
	Mat padding;                                      // 用于存储填充后的图像
	Mat complexI;                                     // 用于存储傅里叶变换后的实部和虚部信息
	Mat gaussBlur;		                              // 高斯滤波器
	Mat butvos;                                       // 布特沃斯滤波器
	Mat ideal;                                        // 理想滤波器
	//cout << row << "," << col << endl;

	copyMakeBorder(src, padding, 0, row - src_row, 0, col - src_col, BORDER_CONSTANT, Scalar(0));
	padding.convertTo(padding, CV_32F);

	for (int i = 0; i < row; i++)
	{
		float *ptr_gauss = padding.ptr<float>(i);     // 滤波器初始值设置
		float *ptr_butvos = padding.ptr<float>(i);
		float *ptr_ideal = padding.ptr<float>(i);

		float *ptr = padding.ptr<float>(i);
		for (int j = 0; j < col; j++)
		{
			float u = pow(i - row / 2, 2);
			float v = pow(j - col / 2, 2);
			ptr[j] *= pow(-1, i + j);                 // 将傅里叶变换的谱图居中
			ptr_gauss[j] = exp(-(u + v) / (2 * dd0));
			ptr_butvos[j] = 1 / (1 + pow((u + v) / dd0, n));
			ptr_ideal[j] = u + v > dd0 ? 0.0 : 1.0;
		}
	}

	//cout << padding.size << endl;
	Mat planes[] = { Mat_<float>(padding), Mat::zeros(padding.size(), CV_32F) };      // 分别保存傅里叶变换的实部和虚部
	
	merge(planes, 2, complexI);
	dft(complexI, complexI);       /* 傅里叶变换 */                

	split(complexI, planes);
	magnitude(planes[0], planes[1], planes[0]);       // 求解复数矩阵的模
	spectrum = (planes[0]);
	normalize(spectrum, spectrum, 0, 255, CV_MINMAX); // 将 spectrum 中的数值归一化到 0 ~ 255
}

void frequencyFilter(const Mat &src, Mat &dest)
{
	int src_row = src.rows;
	int src_col = src.cols;
	int channel = src.channels();
	int row = getOptimalDFTSize(src_row);
	int col = getOptimalDFTSize(src_col);

	if (1 != channel)
	{
		cout << "Must input gray image!" << endl;
		exit(1);
	}

	Mat padding;
	copyMakeBorder(src, padding, 0, row - src_row, 0, col - src_col, BORDER_CONSTANT, Scalar(0));

	imshow("padding", padding);
	waitKey(0);
}