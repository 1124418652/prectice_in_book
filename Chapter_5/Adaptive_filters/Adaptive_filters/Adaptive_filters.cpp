// Adaptive_filters.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "filtersDefine.h"
#include "../../noice/noice/noiceDefine.h"

using namespace std;
using namespace cv;

int main()
{
	string path = "../../../src/timg.jpg";
	Mat img = imread(path);
	Mat tmp;

	if (img.empty())
	{
		cout << "Can't open the image!" << endl;
		exit(1);
	}
	
	//resize(img, img, Size(640, 480));
	cvtColor(img, img, CV_BGR2GRAY);

	
	Mat noice(img.size(), img.type());
	RNG rng(time(NULL));
	rng.fill(noice, RNG::NORMAL, 0, 10);
	add(img, noice, img);

	//noice::spNoice(img, img,0.9);


	//filter::adaptiveLocalFilter(img, tmp, 100, 5);

	/** 测试排序算法
	int arrIn[] = { 2,1,5,3,6,5,9,7 };
	filter::listSort(arrIn, 8, SELECT);
	for (int i = 0; i < 8; i++)
	{
		cout << arrIn[i] << endl;
	}
	*/

	filter::adaptiveLocalFilter(img, tmp, 100, 5);
	imshow("img", img);
	imshow("dest", tmp);
	//imshow("img", img);
	waitKey(0);

    return 0;
}

