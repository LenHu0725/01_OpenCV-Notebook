
/****************************************************************
* Copyright        : BUPT
* Author           : hx
* Date             : 2017.07.25
* Description      : Number Test
*****************************************************************/

//------------------------��ͷ�ļ��������ռ�������֡�----------------------------------
//						����������������������ͷ�ļ��������ռ�
//--------------------------------------------------------------------------------------
#include <iostream>
#include <opencv2/opencv.hpp>
#include "windows.h"

using namespace std;
using namespace cv;


//------------------------------���궨�岿�֡�------------------------------------------
//							���������帨����
//--------------------------------------------------------------------------------------
int ResultNum = 0;
vector<float> descriptors;//��Ž��

CvSVM svm;
HOGDescriptor *hog = new HOGDescriptor(cvSize(28, 28), cvSize(14, 14), cvSize(7, 7), cvSize(7, 7), 18);


//-----------------------------�������������֡�-----------------------------------------
//							  ������ȫ�ֺ���������
//--------------------------------------------------------------------------------------
int RecNum(string FileName);	//ʶ�����ֳ���

int main()
{	
	// ��1�����庯�� ��ȡ���ļ�
	char NumCounter = '1';
	string FileName; string FileStr1; string FileStr2;
	svm.load("HOG_SVM_DATA.xml");// ����ѵ���õ�xml�ļ�������ѵ������10K����д����
	FileStr1 = ".\\ROI\\";
	FileStr2 = ".jpg";


	// ��2��ʶ������
	for (int i = 0; i <= 5; i++, NumCounter++) {
		FileName = FileStr1 + NumCounter + FileStr2;
		RecNum(FileName);
	}
	
	waitKey();
	return 0;
}


//---------------------------��RecNu()�����������֡�------------------------------------
//							  ������ʶ����������
//--------------------------------------------------------------------------------------
int RecNum(string FileName)
{
	// ��1��������� ��ȡ�ļ�
	
	IplImage *test; 
	IplImage *CutImg = cvCreateImage(cvSize(50, 50), 8, 3);
	const char* StrBuff = FileName.c_str();
	//vector<float> descriptors;//��Ž��
	char result[300]; // ���Ԥ����
	cout << "RecNum() String Out:" << FileName << endl;
	//test = cvLoadImage("Pic.jpg", 1); // ��Ԥ��ͼƬ����ϵͳ�Դ��Ļ�ͼ���������д
	test = cvLoadImage(StrBuff, 1); // ��Ԥ��ͼƬ����ϵͳ�Դ��Ļ�ͼ���������д
	
	if (!test){
		cout << "not exist" << endl;
		return -1;
	}
	cout << "load image done" << endl;
	

	// ��2���ָ�ͼƬ
	for (int i = 0; i < 2; i++) {

		// ��1������ROI����
		Rect srcRoi = Rect(50*i+5, 5, 50, 50);
		Rect desRoi = Rect(0, 0, 50, 50);
		cvSetImageROI(test, srcRoi);
		cvSetImageROI(CutImg, desRoi);
		cvCopy(test, CutImg);
		cvResetImageROI(test);
		cvResetImageROI(CutImg);

		// ��2��ͼ���һ������
		IplImage* trainTempImg = cvCreateImage(cvSize(28, 28), 8, 3);
		cvZero(trainTempImg);
		cvResize(CutImg, trainTempImg);		// ����src�Ĵ�СΪdst�Ĵ�С
		//cvShowImage("ResText", trainTempImg);

		// ��3������ͼƬ��������ȡ��ƥ��
		//HOGDescriptor *hog = new HOGDescriptor(cvSize(28, 28), cvSize(14, 14), cvSize(7, 7), cvSize(7, 7), 9);
		hog->compute(trainTempImg, descriptors, Size(1, 1), Size(0, 0)); //Hog��������
		//cout << "HOG dims: " << descriptors.size() << endl;  //��ӡHog����ά��  ��������324
		CvMat* SVMtrainMat = cvCreateMat(1, descriptors.size(), CV_32FC1);
		int n = 0;
		for (vector<float>::iterator iter = descriptors.begin(); iter != descriptors.end(); iter++) {
			cvmSet(SVMtrainMat, 0, n, *iter);
			n++;
		}

		// ��4����������
		float ret = svm.predict(SVMtrainMat);//�����
		sprintf(result, "%1.0f\r\n", ret);
		cvNamedWindow("dst", 1);
		cvShowImage("dst", trainTempImg);
		cvSaveImage("Turn.jpg", trainTempImg);
		cout << "result:" << result << endl;

	}



	// ��3���������
	cvReleaseImage(&test);
	//cvReleaseImage(&trainTempImg);

	//ResultNum = (int)ret;

	return 0; 

}