#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#define BUBBLE 0
#define QUICK 1
#define INSERT 2
#define BIINSERT 3
#define SELECT 4

using namespace std;
using namespace cv;

namespace filter {
	void adaptiveLocalFilter(const Mat &src, Mat &dest, double var, int size); /* 自适应局部滤波器 */
	void adaptiveMedianFilter(const Mat &src, Mat &dest, int maxSize = 9);                      /* 自适应中值滤波器 */
	int adaptiveMedian(const Mat &src, int row, int col, int kernalSize, int maxSize);
	template<typename T1>
	void listSort(T1 *arrIn, int length, int sortType = INSERT);
	template<typename T1>
	T1 selectMinKey(T1 *arrIn, int length, int begin);
};

template<typename T1>
T1 filter::selectMinKey(T1 *arrIn, int length, int begin)
{
	T1 min = arrIn[begin];
	int minIndex = begin;
	for (int i = begin; i < length; i++)
	{
		if (arrIn[i] < min)
		{
			min = arrIn[i];
			minIndex = i;
		}
	}

	return minIndex;
}

template<typename T1>                          // 模板的定义和声明只能放在同一个文件中
void filter::listSort(T1 *arrIn, int length, int sortType)
{
	if (INSERT == sortType)
	{
		/* 直接插入排序 */
		T1 tmp;
		for (int i = 1; i < length; i++)
		{
			int j = i - 1;
			tmp = arrIn[i];
			for (; j >= 0; j--)
			{
				if (tmp >= arrIn[j])
					break;
				arrIn[j + 1] = arrIn[j];
			}
			arrIn[j + 1] = tmp;
		}
	}

	else if (BIINSERT == sortType)
	{
		/* 折半插入排序 */
		T1 tmp;
		for (int i = 1; i < length; i++)
		{
			tmp = arrIn[i];
			int low = 0, high = i - 1;
			int m;
			
			while (low <= high)               // 利用折半查找，找到插入位置
			{
				m = (low + high) / 2;
				if (tmp > arrIn[m])
					low = m + 1;
				else
					high = m - 1;
			}

			int j = i - 1;
			for (; j >= high + 1; j--)
				arrIn[j + 1] = arrIn[j];
			arrIn[high + 1] = tmp;
		}
	}

	else if (BUBBLE == sortType)
	{
		/* 冒泡排序 */
		T1 tmp;
		for (int i = length - 1; i >= 1; i--)
		{
			for (int j = 0; j < i; j++)
			{
				if (arrIn[j] > arrIn[j + 1])
				{
					tmp = arrIn[j + 1];
					arrIn[j + 1] = arrIn[j];
					arrIn[j] = tmp;
				}
			}
		}
	}

	else if (SELECT == sortType)
	{
		/* 选择排序 */
		T1 tmp;
		for (int i = 0; i < length; i++)
		{
			int j = selectMinKey(arrIn, 8, i);
			if (j != i)
			{
				tmp = arrIn[j];
				arrIn[j] = arrIn[i];
				arrIn[i] = tmp;
			}
		}
	}

	else
	{
		cout << "Don't have this sort type!" << endl;
		exit(1);
	}
}