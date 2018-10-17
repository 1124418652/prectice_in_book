#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void opencvFilter(const Mat &src, Mat &dest, Mat &spectrum,int d0, int type = 1, int n = 1);
void frequencyFilter(const Mat &src, Mat &dest);