// Adaptive_filters.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "filtersDefine.h"

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
	
	resize(img, img, Size(640, 480));
	cvtColor(img, img, CV_BGR2GRAY);

	Mat noice(img.size(), img.type());
	RNG rng(time(NULL));
	rng.fill(noice, RNG::NORMAL, 0, 10);
	add(img, noice, img);

	filter::adaptiveLocalFilter(img, tmp, 100, 5);

	imshow("dest", tmp);
	imshow("img", img);
	waitKey(0);

    return 0;
}

