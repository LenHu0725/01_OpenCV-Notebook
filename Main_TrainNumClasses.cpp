/****************************************************************
* Copyright        : BUPT
* Author           : hx
* Date             : 2017.07.25
* Description      : Train Number Classes
*****************************************************************/

//------------------------��ͷ�ļ��������ռ�������֡�----------------------------------
//					����������������������ͷ�ļ��������ռ�
//--------------------------------------------------------------------------------------
#include "stdafx.h"
#include "windows.h"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;


//------------------------------��Main()������------------------------------------------
//				����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼִ��
//--------------------------------------------------------------------------------------
int main()
{
	// ��1���������
	vector<string> img_path;	//�����ļ�������
	vector<int> img_catg;
	vector<float>descriptors;	//���HOG�������
	int nLine = 0;
	string buf;


	// ��2����ȡ�洢ѵ�������ļ�
	ifstream svm_data("Result Num.txt");	//ѵ������ͼƬ��·����д�����txt�ļ��У�ʹ��bat�������ļ����Եõ����txt�ļ�
	unsigned long n;
	while (svm_data)	//��ѵ�������ļ����ζ�ȡ����
	{
		if (getline(svm_data, buf))
		{
			nLine++;
			if (nLine % 2 == 0)	//ע����������ͼƬȫ·����ż�����Ǳ�ǩ
			{
				img_catg.push_back(atoi(buf.c_str()));	//atoi���ַ���ת�������ͣ���־(0,1��2��...��9)
														//ע����������Ҫ��������𣬷�������
			}
			else
			{
				img_path.push_back(buf);//ͼ��·��
			}
		}
	}
	svm_data.close();//�ر��ļ�


	// ��3�������ĵ�����
	CvMat *data_mat, *res_mat;
	int nImgNum = nLine / 2; // nImgNum������������ֻ���ı�������һ�룬��һ���Ǳ�ǩ
	data_mat = cvCreateMat(nImgNum, 648, CV_32FC1);  // �ڶ���������������������������descriptors�����ֵ�����ģ�
													 // ������descriptors.size()����õ����Ҷ��ڲ�ͬ��С������ѵ��ͼƬ�����ֵ�ǲ�ͬ��
													 // ����ԭ����HOG��ȡͼƬ������ʽ�йأ��ɲο���ϸ˵��
	cvSetZero(data_mat);
	// ���;���,�洢ÿ�����������ͱ�־
	res_mat = cvCreateMat(nImgNum, 1, CV_32FC1);
	cvSetZero(res_mat);


	// ��4��ѵ��ѵ����ͼƬ ��ȡͼ������
	IplImage* src;
	IplImage* trainImg = cvCreateImage(cvSize(28, 28), 8, 3);// ����ͼƬ��С
	// ����HOG����
	//HOGDescriptor *hog = new HOGDescriptor(cvSize(28, 28), cvSize(14, 14), cvSize(7, 7), cvSize(7, 7), 9);	//Ĭ�ϴ洢���ݷ�ʽ
	HOGDescriptor *hog = new HOGDescriptor(cvSize(28, 28), cvSize(14, 14), cvSize(7, 7), cvSize(7, 7), 18);

	for (string::size_type i = 0; i < img_path.size(); i++)
	{
		src = cvLoadImage(img_path[i].c_str(), 1);
		if (src == NULL)
		{
			cout << " can not load the image: " << img_path[i].c_str() << endl;
			continue;
		}
		//cout << "deal with\t" << img_path[i].c_str() << ends;
		
		cvResize(src, trainImg);
		//HOGDescriptor *hog = new HOGDescriptor(cvSize(28, 28), cvSize(14, 14), cvSize(7, 7), cvSize(7, 7), 9);
		//vector<float>descriptors;//��Ž��
		hog->compute(trainImg, descriptors, Size(1, 1), Size(0, 0)); //Hog��������
		cout << "HOG dims: " << descriptors.size() << endl;
		n = 0;
		for (vector<float>::iterator iter = descriptors.begin(); iter != descriptors.end(); iter++){
			cvmSet(data_mat, i, n, *iter);//�洢HOG����
			n++;}
		cvmSet(res_mat, i, 0, img_catg[i]);
		cout << "Done !!!: " << img_path[i].c_str() << " " << img_catg[i] << endl;
		

	}


	// ��5������SVM ���������洢��.xml�ļ���
	CvSVM svm;//�½�һ��SVM
	CvSVMParams param;//������SVMѵ����ز���
	CvTermCriteria criteria;
	criteria = cvTermCriteria(CV_TERMCRIT_EPS, 1000, FLT_EPSILON);
	param = CvSVMParams(CvSVM::C_SVC, CvSVM::RBF, 10.0, 0.09, 1.0, 10.0, 0.5, 1.0, NULL, criteria);
	svm.train(data_mat, res_mat, NULL, NULL, param);//ѵ������
													//����ѵ���õķ�����
	svm.save("HOG_SVM_DATA.xml");
	cout << "HOG_SVM_DATA.xml is saved !!! \n exit program" << endl;
	cvReleaseMat(&data_mat);
	cvReleaseMat(&res_mat);
	cvReleaseImage(&trainImg);


	// ��6��������־�����������
	system("pause");
	return 0;
}