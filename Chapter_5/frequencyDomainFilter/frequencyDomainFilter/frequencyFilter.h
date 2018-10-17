#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

#define GAUSS 0
#define BUTVOS 1
#define IDEAL 2

using namespace std;
using namespace cv;

void opencvFilter(const Mat &src, Mat &dest, Mat &spectrum, int d0, int type = 0, int n = 1);
void frequencyFilter(const Mat &src, Mat &dest);