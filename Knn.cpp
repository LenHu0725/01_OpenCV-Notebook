/*****************************************************************************************
* Copyright        : BUPT
* Author           : hx
* Date             : 2017.07.25
* Description      : Knn
******************************************************************************************/

//----------------------------��ͷ�ļ��������ռ�������֡�------------------------------
//			����������������������ͷ�ļ��������ռ�
//--------------------------------------------------------------------------------------
#include "stdafx.h"
#include "opencv2\opencv.hpp"
#include "windows.h"
#include <iostream>

using namespace std;
using namespace cv;
using namespace cv::ml;


//--------------------------------��main()������----------------------------------------
//		����������̨Ӧ�ó������ں�������������￪ʼ
//--------------------------------------------------------------------------------------
int main()
{
	Mat img = imread("digits.png");
	Mat gray;
	cvtColor(img, gray, CV_BGR2GRAY);
	int b = 20;
	int m = gray.rows / b;   //ԭͼΪ1000*2000
	int n = gray.cols / b;   //�ü�Ϊ5000��20*20��Сͼ��
	Mat data, labels;   //��������
	for (int i = 0; i < n; i++)
	{
		int offsetCol = i*b; //���ϵ�ƫ����
		for (int j = 0; j < m; j++)
		{
			int offsetRow = j*b;  //���ϵ�ƫ����
								  //��ȡ20*20��С��
			Mat tmp;
			gray(Range(offsetRow, offsetRow + b), Range(offsetCol, offsetCol + b)).copyTo(tmp);
			data.push_back(tmp.reshape(0, 1));  //���л��������������
			labels.push_back((int)j / 5);  //��Ӧ�ı�ע
		}

	}
	data.convertTo(data, CV_32F); //uchar��ת��Ϊcv_32f
	int samplesNum = data.rows;
	int trainNum = 3000;
	Mat trainData, trainLabels;
	trainData = data(Range(0, trainNum), Range::all());   //ǰ3000������Ϊѵ������
	trainLabels = labels(Range(0, trainNum), Range::all());

	//ʹ��KNN�㷨
	int K = 5;
	Ptr<TrainData> tData = TrainData::create(trainData, ROW_SAMPLE, trainLabels);
	Ptr<KNearest> model = KNearest::create();
	model->setDefaultK(K);
	model->setIsClassifier(true);
	model->train(tData);

	//Ԥ�����
	double train_hr = 0, test_hr = 0;
	Mat response;
	// compute prediction error on train and test data
	for (int i = 0; i < samplesNum; i++)
	{
		Mat sample = data.row(i);
		float r = model->predict(sample);   //�������н���Ԥ��
											//Ԥ������ԭ�����ȣ����Ϊ1������Ϊ0
		r = std::abs(r - labels.at<int>(i)) <= FLT_EPSILON ? 1.f : 0.f;

		if (i < trainNum)
			train_hr += r;  //�ۻ���ȷ��
		else
			test_hr += r;
	}

	test_hr /= samplesNum - trainNum;
	train_hr = trainNum > 0 ? train_hr / trainNum : 1.;

	printf("accuracy: train = %.1f%%, test = %.1f%%\n",
		train_hr*100., test_hr*100.);
	waitKey(0);
	system("pause");
	return 0;
}