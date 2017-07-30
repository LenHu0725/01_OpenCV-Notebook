/*****************************************************************************************
* Copyright        : BUPT
* Author           : hx
* Date             : 2017.07.25
* Description      : Histogram
******************************************************************************************/

//----------------------------【头文件、命名空间包含部分】------------------------------
//			描述：包含程序所依赖的头文件和命名空间
//--------------------------------------------------------------------------------------
#include "cv.h"  
#include "highgui.h"  
#include "iostream"

using namespace cv;
using namespace std;


//--------------------------------【全局函数声明部分】-----------------------------------
//				描述：全局函数声明
//---------------------------------------------------------------------------------------
int HistogramMaxgrayColor(IplImage* srcPic = NULL);


//--------------------------------【main()函数】----------------------------------------
//		描述：控制台应用程序的入口函数，程序从这里开始
//--------------------------------------------------------------------------------------
int main( int argc,char* argv )
{
	// 【1】定义变量
	IplImage* src = cvLoadImage("PIC.jpg");
	IplImage* gray_dst = cvCreateImage(cvGetSize(src), 8, 1);

	cvCvtColor(src, gray_dst, CV_BGR2GRAY);
	int buffer=0;


	// 【2】计算直方图
	buffer = HistogramMaxgrayColor(gray_dst);
	cout << "最大灰度值为		：" << buffer << endl << endl;

	// 【3】结束程序
	cvWaitKey(0);
	cvReleaseImage(&src);
	cvReleaseImage(&gray_dst);

	return 0;
}


//------------------【HistogramMaxgrayColor（）函数】---------------------------------
//						描述：【绘制直方图函数】
//------------------------------------------------------------------------------------
int HistogramMaxgrayColor(IplImage* srcPic)
{
	// 一维维数  
	int dims = 1;
	// 直方图的尺寸  
	int size = 256;
	// 直方图的高度
	int height = 500;
	// 输出最大灰度值
	int MaxGrayColor = 0;
	// 灰度图的范围0到255  
	float range[] = { 0, 256 };
	float *ranges[] = { range };

	// 创建一维直方图  
	CvHistogram* hist;
	hist = cvCreateHist(dims, &size, CV_HIST_ARRAY, ranges, 1);

	// 计算灰度图的一维直方图  
	cvCalcHist(&srcPic, hist, 0, 0);
	// 归一化直方图  
	cvNormalizeHist(hist, 1.0);

	int scale = 2;
	//创建图像，用于显示直方图  
	IplImage* hist_img = cvCreateImage(cvSize(size* scale, height), 8, 3);
	//图像置零  
	cvZero(hist_img);

	//计算直方图的最大方块值,初始化为0  
	float max_value = 0;
	cvGetMinMaxHistValue(hist, 0, &max_value, 0, 0);

	//绘制直方图  
	for (int i = 0; i<size; i++)
	{
		float bin_val = cvQueryHistValue_1D(hist, i);   //像素i的概率  
		int intensity = cvRound(bin_val* height / max_value);  // 绘制的高度  
		cvRectangle(hist_img,
			cvPoint(i* scale, height - 1),
			cvPoint((i + 1)* scale - 1, height - intensity),
			CV_RGB(255, 255, 255));
		// 获取数量最多时灰度值
		if (bin_val == max_value)
			MaxGrayColor = i;
	}

	//cvShowImage("Histogram", hist_img);

	cvReleaseImage(&hist_img);

	//cvDestroyWindow("gray");
	//cvDestroyWindow("Histogram");
	
	return MaxGrayColor;

}

