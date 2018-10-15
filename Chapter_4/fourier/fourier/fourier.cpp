// fourier.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <math.h>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <iostream>

#define PI 3.1415926

using namespace std;
using namespace cv;

bool fft(const Mat &res, Mat &dst);

int main()
{
	
	string path = "../../src/timg.jpg";
	Mat im1 = imread(path);
	Mat im1_gray;
	Mat fouriers;
	clock_t start;

	if (im1.empty())
	{
		cout << "Can't open the image!" << endl;
		exit(0);
	}

	cvtColor(im1, im1_gray, CV_BGR2GRAY);
	resize(im1_gray, im1_gray, Size(200, 200));
	imshow("im1_gray", im1_gray);
	waitKey(0);
	//dft(im1_gray, im1_gray);
	fft(im1_gray, fouriers);
	//imshow("im1", im1);
	//imshow("im1_gray", im1_gray);
	waitKey(0);
	return 0;
	/*
	Mat srcImage = imread("../../src/people.jpg", 0);	
	if (!srcImage.data) 
	{
		cout << "����ͼ�����������ļ�" << endl;		
		return false; 
	}	
	imshow("ԭʼͼ��", srcImage); 	//������ͼ����չ����ѵĳߴ磬�߽�ʹ��0���в���	
	int m = getOptimalDFTSize(srcImage.rows);
	int n = getOptimalDFTSize(srcImage.cols);	//����ӵ����س�ʼ��Ϊ0	
	Mat padded;
	copyMakeBorder(srcImage, padded, m - srcImage.rows, 0, n - srcImage.cols, 0, BORDER_CONSTANT, Scalar::all(0)); 	//Ϊ����Ҷ�任�Ľ������洢�ռ�(��Ϊʵ�����鲿)	
																													//��planes����ϲ���Ϊһ����ͨ��������complexI
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI); 	//�͵ؽ�����ɢ����Ҷ�任	
	dft(complexI, complexI); 	//������ת��Ϊ��ֵ����Ϊ��log(1+sqrt(Re(DFT(I))^2+Im(DFT(I))^2))	
	split(complexI, planes);	//����ͨ�������Ϊ������ͨ������								
								//planes[0] = Re(DFT(I)),planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]);
	Mat MagnitudeImage = planes[0]; 	//���ж����߶ȷ���	
	MagnitudeImage += Scalar::all(1);	
	log(MagnitudeImage, MagnitudeImage);	//����Ȼ���� 	
																				//���к����·ֲ�����ͼ������	
																				//���������к������У�����Ƶ�׼���	
	MagnitudeImage = MagnitudeImage(Rect(0, 0, MagnitudeImage.cols &-2, MagnitudeImage.rows &-2));	//����е� & -2 ��λ��������Ϊ-2�Ķ�����Ϊ�����һλΪ0�������Ϊ1�������֮��Ľ��Ϊ�����λ��1���	
																									//ʵ�ֽ�ԭ����������Ϊż��	
																									//�������и���Ҷͼ���е����ޣ�ʹ��ԭ��λԭͼ������	
	int cx = MagnitudeImage.cols / 2;	
	int cy = MagnitudeImage.rows / 2;
	Mat q0(MagnitudeImage, Rect(0, 0, cx, cy));		//ROI��������Ϸ�	
	Mat q1(MagnitudeImage, Rect(cx, 0, cx, cy));	//ROI��������Ϸ�	
	Mat q2(MagnitudeImage, Rect(0, cy, cx, cy));	//ROI��������·�	
	Mat q3(MagnitudeImage, Rect(cx, cy, cx, cy));	//ROI��������·� 	
													//�������ޣ����������½���	
	Mat tmp;	
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);	//�������ޣ����������½��н���	
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2); 	//��һ������0~1֮��ĸ�����������任Ϊ����ͼ�ĸ�ʽ	
	normalize(MagnitudeImage, MagnitudeImage, 0, 1, CV_MINMAX); 	//��ʾЧ��ͼ	
	imshow("Ƶ�׷�ֵ", MagnitudeImage); 
	waitKey();
	return 0;
	*/
}

bool fft(const Mat &res, Mat &dst)
{
	double height = (double)res.rows;
	double width = (double)res.cols;
	int val = 0;

	double **_tmp11 = new double*[height];
	double **_tmp12 = new double*[height];
	for (int i = 0; i < height; i++)
	{
		_tmp11[i] = new double[width];
		_tmp12[i] = new double[width];
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			_tmp11[i][j] = 0;
			_tmp12[i][j] = 0;
		}
	}

	Mat _tmp1(height, width, CV_8UC1, Scalar(0));
	Mat _tmp2(height, width, CV_8UC1, Scalar(0));
	Mat _tmp(height, width, CV_8UC1, Scalar(0));
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			for (int u = 0; u < width; u++) {
				val = res.at<uchar>(i, u);
				_tmp11[i][j] += val * cos(2 * PI * (u-width/2) * j / width);
				_tmp12[i][j] -= val * sin(2 * PI * (u-width/2) * j / width);
			}
			_tmp1.at<uchar>(i, j) = pow((pow(_tmp11[i][j], 2) + pow(_tmp12[i][j], 2)), 0.5);
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			for (int v = 0; v < height; v++) {
				val = _tmp1.at<uchar>(v, j);
				_tmp11[i][j] += val * cos(2 * PI * (v-height/2) * i / width);
				_tmp12[i][j] -= val * sin(2 * PI * (v - height / 2) * j / width);
			}
			_tmp2.at<uchar>(i, j) = log(1+pow((pow(_tmp11[i][j], 2) + pow(_tmp12[i][j], 2)), 0.5)) * 100;
		}
	}
	
	/*
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			for (int x = 0; x < height; x++)
			{
				for (int y = 0; y < width; y++)
				{
					val = res.at<uchar>(x, y);
					_tmp11[i][j] += val * cos(2 * PI * (x * i / height + y * j / width));
					_tmp12[i][j] -= val * sin(2 * PI * (x * i / height + y * j / width));
					//cout << 2 * PI * (x * i / height + y * j / width) << endl;
				}
			}
			cout << _tmp11[i][j] << endl;
			_tmp.at<uchar>(i, j) = pow(pow(_tmp11[i][j], 2) + pow(_tmp12[i][j], 2), 0.5);
		}
		cout << i << endl;
	}
	*/
	resize(_tmp2, _tmp2, Size(1000, 1000));
	imshow("_tmp", _tmp2);
	waitKey(0);
	return true;
}