#include "stdafx.h"
#include "frequencyFilter.h"

void opencvFilter(const Mat &src, Mat &dest, Mat &spectrum, int d0, int type, int n)
{
	int src_row = src.rows;
	int src_col = src.cols;
	int channel = src.channels();
	int row = getOptimalDFTSize(src_row);
	int col = getOptimalDFTSize(src_col);
	int dd0 = d0 * d0;
	Mat padding;                                      // ���ڴ洢�����ͼ��
	Mat complexI;                                     // ���ڴ洢����Ҷ�任���ʵ�����鲿��Ϣ
	Mat gaussBlur;		                              // ��˹�˲���
	Mat butvos;                                       // ������˹�˲���
	Mat ideal;                                        // �����˲���
	//cout << row << "," << col << endl;

	copyMakeBorder(src, padding, 0, row - src_row, 0, col - src_col, BORDER_CONSTANT, Scalar(0));
	padding.convertTo(padding, CV_32F);

	for (int i = 0; i < row; i++)
	{
		float *ptr_gauss = padding.ptr<float>(i);     // �˲�����ʼֵ����
		float *ptr_butvos = padding.ptr<float>(i);
		float *ptr_ideal = padding.ptr<float>(i);

		float *ptr = padding.ptr<float>(i);
		for (int j = 0; j < col; j++)
		{
			float u = pow(i - row / 2, 2);
			float v = pow(j - col / 2, 2);
			ptr[j] *= pow(-1, i + j);                 // ������Ҷ�任����ͼ����
			ptr_gauss[j] = exp(-(u + v) / (2 * dd0));
			ptr_butvos[j] = 1 / (1 + pow((u + v) / dd0, n));
			ptr_ideal[j] = u + v > dd0 ? 0.0 : 1.0;
		}
	}

	//cout << padding.size << endl;
	Mat planes[] = { Mat_<float>(padding), Mat::zeros(padding.size(), CV_32F) };      // �ֱ𱣴渵��Ҷ�任��ʵ�����鲿
	
	merge(planes, 2, complexI);
	dft(complexI, complexI);       /* ����Ҷ�任 */                

	split(complexI, planes);
	magnitude(planes[0], planes[1], planes[0]);       // ��⸴�������ģ
	spectrum = (planes[0]);
	normalize(spectrum, spectrum, 0, 255, CV_MINMAX); // �� spectrum �е���ֵ��һ���� 0 ~ 255
}

void frequencyFilter(const Mat &src, Mat &dest)
{
	int src_row = src.rows;
	int src_col = src.cols;
	int channel = src.channels();
	int row = getOptimalDFTSize(src_row);
	int col = getOptimalDFTSize(src_col);

	if (1 != channel)
	{
		cout << "Must input gray image!" << endl;
		exit(1);
	}

	Mat padding;
	copyMakeBorder(src, padding, 0, row - src_row, 0, col - src_col, BORDER_CONSTANT, Scalar(0));

	imshow("padding", padding);
	waitKey(0);
}