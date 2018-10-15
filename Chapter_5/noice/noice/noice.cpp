// noice.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "noiceDefine.h"

using namespace std;
using namespace cv;

int main()
{
	string path = "../../../src/timg.jpg";
	Mat img = imread(path);
	Mat dest, dest2, img1;

	if (img.empty())
	{
		cout << "Can't open the image!" << endl;
		exit(1);
	}

	resize(img,img, Size(640, 480));
	cvtColor(img, img1, CV_BGR2GRAY);
	noice::addGaussNoice(img1, dest, 0, 10, 1);
	noice::spNoice(img, dest2, 0.9);
	/*
	Mat noice(img.size(), img.type());
	RNG rng(time(NULL));
	rng.fill(noice, RNG::NORMAL, 0, 10);
	add(img, noice, dest);
	*/

	namedWindow("gauss noice");
	namedWindow("sp noice");
	imshow("gauss noice", dest);
	imshow("sp noice", dest2);
	waitKey(0);

    return 0;
}

