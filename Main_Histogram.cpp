/*****************************************************************************************
* Copyright        : BUPT
* Author           : hx
* Date             : 2017.07.25
* Description      : Histogram
******************************************************************************************/

//----------------------------��ͷ�ļ��������ռ�������֡�------------------------------
//			����������������������ͷ�ļ��������ռ�
//--------------------------------------------------------------------------------------
#include "cv.h"  
#include "highgui.h"  
#include "iostream"

using namespace cv;
using namespace std;


//--------------------------------��ȫ�ֺ����������֡�-----------------------------------
//				������ȫ�ֺ�������
//---------------------------------------------------------------------------------------
int HistogramMaxgrayColor(IplImage* srcPic = NULL);


//--------------------------------��main()������----------------------------------------
//		����������̨Ӧ�ó������ں�������������￪ʼ
//--------------------------------------------------------------------------------------
int main( int argc,char* argv )
{
	// ��1���������
	IplImage* src = cvLoadImage("PIC.jpg");
	IplImage* gray_dst = cvCreateImage(cvGetSize(src), 8, 1);

	cvCvtColor(src, gray_dst, CV_BGR2GRAY);
	int buffer=0;


	// ��2������ֱ��ͼ
	buffer = HistogramMaxgrayColor(gray_dst);
	cout << "���Ҷ�ֵΪ		��" << buffer << endl << endl;

	// ��3����������
	cvWaitKey(0);
	cvReleaseImage(&src);
	cvReleaseImage(&gray_dst);

	return 0;
}


//------------------��HistogramMaxgrayColor����������---------------------------------
//						������������ֱ��ͼ������
//------------------------------------------------------------------------------------
int HistogramMaxgrayColor(IplImage* srcPic)
{
	// һάά��  
	int dims = 1;
	// ֱ��ͼ�ĳߴ�  
	int size = 256;
	// ֱ��ͼ�ĸ߶�
	int height = 500;
	// ������Ҷ�ֵ
	int MaxGrayColor = 0;
	// �Ҷ�ͼ�ķ�Χ0��255  
	float range[] = { 0, 256 };
	float *ranges[] = { range };

	// ����һάֱ��ͼ  
	CvHistogram* hist;
	hist = cvCreateHist(dims, &size, CV_HIST_ARRAY, ranges, 1);

	// ����Ҷ�ͼ��һάֱ��ͼ  
	cvCalcHist(&srcPic, hist, 0, 0);
	// ��һ��ֱ��ͼ  
	cvNormalizeHist(hist, 1.0);

	int scale = 2;
	//����ͼ��������ʾֱ��ͼ  
	IplImage* hist_img = cvCreateImage(cvSize(size* scale, height), 8, 3);
	//ͼ������  
	cvZero(hist_img);

	//����ֱ��ͼ����󷽿�ֵ,��ʼ��Ϊ0  
	float max_value = 0;
	cvGetMinMaxHistValue(hist, 0, &max_value, 0, 0);

	//����ֱ��ͼ  
	for (int i = 0; i<size; i++)
	{
		float bin_val = cvQueryHistValue_1D(hist, i);   //����i�ĸ���  
		int intensity = cvRound(bin_val* height / max_value);  // ���Ƶĸ߶�  
		cvRectangle(hist_img,
			cvPoint(i* scale, height - 1),
			cvPoint((i + 1)* scale - 1, height - intensity),
			CV_RGB(255, 255, 255));
		// ��ȡ�������ʱ�Ҷ�ֵ
		if (bin_val == max_value)
			MaxGrayColor = i;
	}

	//cvShowImage("Histogram", hist_img);

	cvReleaseImage(&hist_img);

	//cvDestroyWindow("gray");
	//cvDestroyWindow("Histogram");
	
	return MaxGrayColor;

}

