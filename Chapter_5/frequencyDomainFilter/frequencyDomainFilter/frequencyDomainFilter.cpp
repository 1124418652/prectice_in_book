// frequencyDomainFilter.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "frequencyFilter.h"

using namespace std;
using namespace cv;

int main()
{
	string path = "../../../src/er.jpg";
	Mat img = imread(path, IMREAD_GRAYSCALE);
	Mat dest;
	Mat spectrum;

	if (img.empty()) {
		cout << "Can't open the image!" << endl;
		exit(1);
	}

	opencvFilter(img, dest, spectrum,10);

	namedWindow("Source Image");
	imshow("Source Image", img);
	waitKey(0);


    return 0;
}

