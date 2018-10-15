#include "stdafx.h"
#include <time.h>
#include "noiceDefine.h"

double noice::gaussNoice(const double mean, const double var)
{
	const double epsilon = numeric_limits<double>::min();
	static bool flag = false;
	static double z0, z1;
	double u0, u1;
	flag = !flag;

	if (!flag)
	{
		//cout << z1 << endl;
		return z1 * var + mean;
	}

	do
	{
		u0 = rand() * 1.0 / RAND_MAX;
		u1 = rand() * 1.0 / RAND_MAX;
	} while (u0 <= epsilon || u1 <= epsilon);

	z0 = sqrt(-2.0 * log(u0)) * cos(2 * CV_PI * u1);
	z1 = sqrt(-2.0 * log(u0)) * sin(2 * CV_PI * u1);

	return z0 * var + mean;
}

void noice::addGaussNoice(const Mat &src, Mat &dest, double mean, double var, int k)
{
	srand(time(NULL));
	dest = src.clone();
	int rows = src.rows;
	int cols = src.cols;
	int tmp;

	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < cols; j++)
		{
			tmp = (int)dest.at<uchar>(i, j) + k * gaussNoice(mean, var);
			if (tmp < 0)
				tmp = 0;
			else if (tmp > 255)
				tmp = 255;
			dest.at<uchar>(i, j) = tmp;
		}
	}
}

void noice::spNoice(const Mat &img, Mat &dest, double snr)    // snr 表示信噪比
{
	int rows = img.rows;
	int cols = img.cols;
	int channel = img.channels();
	dest = img.clone();
	int NP = (1 - snr) * rows * cols;          // 椒盐噪声的个数
	int x, y;                            // 图像中的坐标
	int flag;                            // 用于指示椒噪声和盐噪声
	srand(time(NULL));

	for (int k = 0; k < NP; k++)
	{
		x = rand() % cols;
		y = rand() % rows;
		flag = rand() % 2;

		if (1 == channel)
		{
			if (0 == flag)
				dest.at<uchar>(y, x) = 0;      // 椒噪声
			else
				dest.at<uchar>(y, x) = 255;    // 盐噪声
		}

		else if (3 == channel)
		{
			if (0 == flag)
			{
				dest.at<Vec3b>(y, x)[0] = 0;
				dest.at<Vec3b>(y, x)[1] = 0;
				dest.at<Vec3b>(y, x)[2] = 0;
			}
			else
			{
				dest.at<Vec3b>(y, x)[0] = 255;
				dest.at<Vec3b>(y, x)[1] = 255;
				dest.at<Vec3b>(y, x)[2] = 255;
			}
		}
	}
}