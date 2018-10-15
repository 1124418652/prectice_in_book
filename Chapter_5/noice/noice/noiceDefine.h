#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

namespace noice
{
	double gaussNoice(const double mean, const double var);
	void addGaussNoice(const Mat &src, Mat &dest, double mean, double var, int k);
	void spNoice(const Mat &img, Mat &dest, double snr);
};