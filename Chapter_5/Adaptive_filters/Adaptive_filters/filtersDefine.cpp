#include "stdafx.h"
#include <cmath>
#include "filtersDefine.h"

void filter::adaptiveLocalFilter(const Mat &src, Mat &dest, double sigma, int size)
{
	int half_size = size / 2;
	int channel = src.channels();
	double mean;                  // 局部均值
	double variable;              // 局部方差
	int temp;
	Mat tmp = Mat::ones(src.rows + size - 1, src.cols + size - 1, src.type());       // tmp 为对 src 进行填充后的图片
	dest.create(src.rows, src.cols, src.type());
	//tmp.create(src.rows + size - 1, src.cols + size - 1, src.type());
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			if (1 == channel)
				tmp.at<uchar>(i + half_size, j + half_size) = src.at<uchar>(i, j);
			else if (3 == channel)
				tmp.at<Vec3b>(i + half_size, j + half_size) = src.at<Vec3b>(i, j);
		}
	}

	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			mean = 0;
			variable = 0;
			for (int x = -half_size; x <= half_size; x++)
			{
				for (int y = -half_size; y <= half_size; y++)
				{
					mean += tmp.at<uchar>(i + half_size - x, j + half_size - y);
				}
			}
			mean /= (size * size);
			for (int x = -half_size; x <= half_size; x++)
			{
				for (int y = -half_size; y <= half_size; y++)
				{
					variable += pow(tmp.at<uchar>(i + half_size - x, j + half_size - y) - mean, 2);
				}
			}
			variable /= (size * size);
			variable = variable > sigma ? sigma / variable : 1;
			temp = src.at<uchar>(i, j) - variable * (src.at<uchar>(i, j) - mean);
			if (temp < 0)
				dest.at<uchar>(i, j) = 0;
			else if (temp > 255)
				dest.at<uchar>(i, j) = 255;
			dest.at<uchar>(i, j) = temp;
		}
	}
}

void filter::adaptiveMedianFilter(const Mat &src, Mat &dest)
{

}