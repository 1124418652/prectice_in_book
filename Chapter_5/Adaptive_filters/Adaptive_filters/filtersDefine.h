#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

namespace filter {
	void adaptiveLocalFilter(const Mat &src, Mat &dest, double var, int size);
	void adaptiveMedianFilter(const Mat &src, Mat &dest);
};