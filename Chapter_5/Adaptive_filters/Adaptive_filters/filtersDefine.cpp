#include "stdafx.h"
#include <cmath>
#include "filtersDefine.h"

void filter::adaptiveLocalFilter(const Mat &src, Mat &dest, double sigma, int size)
{
	int half_size = size / 2;
	int channel = src.channels();
	double mean;                  // �ֲ���ֵ
	double variable;              // �ֲ�����
	int temp;
	Mat tmp = Mat::ones(src.rows + size - 1, src.cols + size - 1, src.type());       // tmp Ϊ�� src ���������ͼƬ
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
			variable = variable > sigma ? sigma / variable : 1;        // �� sigma >= variable ʱ������Ϊ1
			temp = src.at<uchar>(i, j) - variable * (src.at<uchar>(i, j) - mean);
			if (temp < 0)
				dest.at<uchar>(i, j) = 0;
			else if (temp > 255)
				dest.at<uchar>(i, j) = 255;
			dest.at<uchar>(i, j) = temp;
		}
	}
}

int filter::adaptiveMedian(const Mat &src, int row, int col, int kernalSize, int maxSize)
{
	int half_kernalSize = kernalSize / 2;
	int arrSize = kernalSize * kernalSize;                             // ѡ���������ݵĸ���
	int min, max, med, zxy = src.at<uchar>(row, col);
	int *arrIn = new int[arrSize];
	int k = 0;                                                         // ��¼ arrIn ������

	for (int i = -half_kernalSize; i <= half_kernalSize; i++)
	{
		for (int j = -half_kernalSize; j <= half_kernalSize; j++)
		{
			arrIn[k] = (int)src.at<uchar>(row + i, col + j);
			k++;
		}
	}

	listSort(arrIn, arrSize);
	min = arrIn[0];
	max = arrIn[arrSize - 1];
	med = arrIn[arrSize / 2];
	delete[] arrIn;

	if (med > min && med < max)         // process A
	{
		// turn to Process B
		if (zxy > min && zxy < max)
			return zxy;
		else
			return med;
	}
	else
	{
		if (kernalSize < maxSize)
		{
			kernalSize += 2;
			return adaptiveMedian(src, row, col, kernalSize, maxSize); // �ݹ�ִ�н��� A
		}
		else
			return med;
	}
}

void filter::adaptiveMedianFilter(const Mat &src, Mat &dest, int maxSize)
{
	int size = 3;                      // ��ʼ�˾���ĳߴ�
	int half_maxSize = maxSize / 2;
	int row = src.rows;
	int col = src.cols;
	Mat tmp;
	dest.create(src.size(), src.type());
	cv::copyMakeBorder(src, tmp, half_maxSize, half_maxSize, half_maxSize,  
		half_maxSize, cv::BorderTypes::BORDER_ISOLATED);              // �����˾����ԭʼͼƬ�������
	
	for (int i = half_maxSize; i < row + half_maxSize; i++)
	{
		for (int j = half_maxSize; j < col + half_maxSize; j++)
		{
			dest.at<uchar>(i - half_maxSize, j - half_maxSize) = adaptiveMedian(tmp, i, j, 3, maxSize);
		}
	}
}