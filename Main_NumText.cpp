
/****************************************************************
* Copyright        : BUPT
* Author           : hx
* Date             : 2017.07.25
* Description      : Number Test
*****************************************************************/

//------------------------【头文件与命名空间包含部分】----------------------------------
//						描述：包含程序所依赖的头文件和命名空间
//--------------------------------------------------------------------------------------
#include <iostream>
#include <opencv2/opencv.hpp>
#include "windows.h"

using namespace std;
using namespace cv;


//------------------------------【宏定义部分】------------------------------------------
//							描述：定义辅助宏
//--------------------------------------------------------------------------------------
int ResultNum = 0;
vector<float> descriptors;//存放结果

CvSVM svm;
HOGDescriptor *hog = new HOGDescriptor(cvSize(28, 28), cvSize(14, 14), cvSize(7, 7), cvSize(7, 7), 18);


//-----------------------------【函数声明部分】-----------------------------------------
//							  描述：全局函数的声明
//--------------------------------------------------------------------------------------
int RecNum(string FileName);	//识别数字程序

int main()
{	
	// 【1】定义函数 读取库文件
	char NumCounter = '1';
	string FileName; string FileStr1; string FileStr2;
	svm.load("HOG_SVM_DATA.xml");// 加载训练好的xml文件，这里训练的是10K个手写数字
	FileStr1 = ".\\ROI\\";
	FileStr2 = ".jpg";


	// 【2】识别数字
	for (int i = 0; i <= 5; i++, NumCounter++) {
		FileName = FileStr1 + NumCounter + FileStr2;
		RecNum(FileName);
	}
	
	waitKey();
	return 0;
}


//---------------------------【RecNu()函数声明部分】------------------------------------
//							  描述：识别函数的声明
//--------------------------------------------------------------------------------------
int RecNum(string FileName)
{
	// 【1】定义变量 读取文件
	
	IplImage *test; 
	IplImage *CutImg = cvCreateImage(cvSize(50, 50), 8, 3);
	const char* StrBuff = FileName.c_str();
	//vector<float> descriptors;//存放结果
	char result[300]; // 存放预测结果
	cout << "RecNum() String Out:" << FileName << endl;
	//test = cvLoadImage("Pic.jpg", 1); // 待预测图片，用系统自带的画图工具随便手写
	test = cvLoadImage(StrBuff, 1); // 待预测图片，用系统自带的画图工具随便手写
	
	if (!test){
		cout << "not exist" << endl;
		return -1;
	}
	cout << "load image done" << endl;
	

	// 【2】分割图片
	for (int i = 0; i < 2; i++) {

		// 【1】设置ROI区域
		Rect srcRoi = Rect(50*i+5, 5, 50, 50);
		Rect desRoi = Rect(0, 0, 50, 50);
		cvSetImageROI(test, srcRoi);
		cvSetImageROI(CutImg, desRoi);
		cvCopy(test, CutImg);
		cvResetImageROI(test);
		cvResetImageROI(CutImg);

		// 【2】图像归一化处理
		IplImage* trainTempImg = cvCreateImage(cvSize(28, 28), 8, 3);
		cvZero(trainTempImg);
		cvResize(CutImg, trainTempImg);		// 调整src的大小为dst的大小
		//cvShowImage("ResText", trainTempImg);

		// 【3】测试图片特征点提取与匹配
		//HOGDescriptor *hog = new HOGDescriptor(cvSize(28, 28), cvSize(14, 14), cvSize(7, 7), cvSize(7, 7), 9);
		hog->compute(trainTempImg, descriptors, Size(1, 1), Size(0, 0)); //Hog特征计算
		//cout << "HOG dims: " << descriptors.size() << endl;  //打印Hog特征维数  ，这里是324
		CvMat* SVMtrainMat = cvCreateMat(1, descriptors.size(), CV_32FC1);
		int n = 0;
		for (vector<float>::iterator iter = descriptors.begin(); iter != descriptors.end(); iter++) {
			cvmSet(SVMtrainMat, 0, n, *iter);
			n++;
		}

		// 【4】检测结果输出
		float ret = svm.predict(SVMtrainMat);//检测结果
		sprintf(result, "%1.0f\r\n", ret);
		cvNamedWindow("dst", 1);
		cvShowImage("dst", trainTempImg);
		cvSaveImage("Turn.jpg", trainTempImg);
		cout << "result:" << result << endl;

	}



	// 【3】程序结束
	cvReleaseImage(&test);
	//cvReleaseImage(&trainTempImg);

	//ResultNum = (int)ret;

	return 0; 

}