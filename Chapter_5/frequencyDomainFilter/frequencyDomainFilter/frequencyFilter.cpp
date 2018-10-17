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
	Mat gauss;		                                  // 高斯滤波器
	Mat butvos;                                       // 布特沃斯滤波器
	Mat ideal;                                        // 理想滤波器
	//cout << row << "," << col << endl;

	copyMakeBorder(src, padding, 0, row - src_row, 0, col - src_col, BORDER_CONSTANT, Scalar(0));
	padding.convertTo(padding, CV_32F);

	for (int i = 0; i < row; i++)
	{
		float *ptr = padding.ptr<float>(i);
		for (int j = 0; j < col; j++)
		{
			ptr[j] *= pow(-1, i + j);                 // 将傅里叶变换的谱图居中
		}
	}

	//cout << padding.size << endl;
	Mat planes[] = { Mat_<float>(padding), Mat::zeros(padding.size(), CV_32F) };      // 分别保存傅里叶变换的实部和虚部
	
	merge(planes, 2, complexI);
	dft(complexI, complexI);       /* 傅里叶变换 */                

	/* 频谱计算 */
	split(complexI, planes);
	magnitude(planes[0], planes[1], spectrum);       // 求解复数矩阵的模
	normalize(spectrum, spectrum, 0, 255, CV_MINMAX); // 将 spectrum 中的数值归一化到 0 ~ 255

	/* 频域滤波操作 */
	switch (type)
	{
	case GAUSS:
	{
		gauss.create(padding.size(), CV_32F);
		for (int i = 0; i < row; i++)
		{
			float *ptr_gauss = gauss.ptr<float>(i);     // 滤波器初始值设置
			for (int j = 0; j < col; j++)
			{
				float u = pow(i - row / 2, 2);
				float v = pow(j - col / 2, 2);
				ptr_gauss[j] = exp(-(u + v) / (2 * dd0));
			}
		}
		multiply(planes[0], gauss, planes[0]);
		multiply(planes[1], gauss, planes[1]);
		merge(planes, 2, dest);
		imshow("gauss kernel", gauss);
		waitKey(0);
		break;
	}
	case BUTVOS:
	{
		butvos.create(padding.size(), CV_32F);
		for (int i = 0; i < row; i++)
		{
			float *ptr_butvos = butvos.ptr<float>(i);
			for (int j = 0; j < col; j++)
			{
				float u = pow(i - row / 2, 2);
				float v = pow(j - col / 2, 2);
				ptr_butvos[j] = 1 / (1 + pow((u + v) / dd0, n));
			}
		}
		multiply(planes[0], butvos, planes[0]);
		multiply(planes[1], butvos, planes[1]);
		merge(planes, 2, dest);
		imshow("butvos kernel", butvos);
		waitKey(0);
		break;
	}
	case IDEAL:
	{
		ideal.create(padding.size(), CV_32F);
		for (int i = 0; i < row; i++)
		{
			float *ptr_ideal = ideal.ptr<float>(i);
			for (int j = 0; j < col; j++)
			{
				float u = pow(i - row / 2, 2);
				float v = pow(j - col / 2, 2);
				ptr_ideal[j] = u + v > dd0 ? 0.0 : 1.0;
			}
		}
		multiply(planes[0], ideal, planes[0]);
		multiply(planes[1], ideal, planes[1]);
		merge(planes, 2, dest);
		imshow("ideal kernel", ideal);
		waitKey(0);
		break;
	}
	default:
		break;
	}
	idft(dest, dest);
	split(dest, planes);
	magnitude(planes[0], planes[1], planes[0]);
	normalize(planes[0], planes[0], 1, 0, CV_MINMAX);
	imshow("dest", planes[0]);
	waitKey(0);
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