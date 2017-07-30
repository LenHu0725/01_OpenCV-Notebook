/****************************************************************
* Copyright        : BUPT
* Author           : hx
* Date             : 2017.07.25
* Description      : Train Number Classes
*****************************************************************/

//------------------------【头文件与命名空间包含部分】----------------------------------
//		    描述：包含程序所依赖的头文件和命名空间
//--------------------------------------------------------------------------------------
#include "stdafx.h"
#include "windows.h"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;


//------------------------------【Main()函数】------------------------------------------
//		描述：控制台应用程序的入口函数，我们的程序从这里开始执行
//--------------------------------------------------------------------------------------
int main()
{
	// 【1】定义变量
	vector<string> img_path;	//输入文件名变量
	vector<int> img_catg;
	vector<float>descriptors;	//存放HOG特征结果
	int nLine = 0;
	string buf;


	// 【2】读取存储训练样本文件
	ifstream svm_data("Result Num.txt");	//训练样本图片的路径都写在这个txt文件中，使用bat批处理文件可以得到这个txt文件
	unsigned long n;
	while (svm_data)	//将训练样本文件依次读取进来
	{
		if (getline(svm_data, buf))
		{
			nLine++;
			if (nLine % 2 == 0)	//注：奇数行是图片全路径，偶数行是标签
			{
				img_catg.push_back(atoi(buf.c_str()));	//atoi将字符串转换成整型，标志(0,1，2，...，9)
														//注意这里至少要有两个类别，否则会出错
			}
			else
			{
				img_path.push_back(buf);//图像路径
			}
		}
	}
	svm_data.close();//关闭文件


	// 【3】处理文档数据
	CvMat *data_mat, *res_mat;
	int nImgNum = nLine / 2; // nImgNum是样本数量，只有文本行数的一半，另一半是标签
	data_mat = cvCreateMat(nImgNum, 648, CV_32FC1);  // 第二个参数，即矩阵的列是由下面的descriptors的输出值决定的，
													 // 可以由descriptors.size()输出得到，且对于不同大小的输入训练图片，这个值是不同的
													 // 具体原理与HOG提取图片特征方式有关，可参考详细说明
	cvSetZero(data_mat);
	// 类型矩阵,存储每个样本的类型标志
	res_mat = cvCreateMat(nImgNum, 1, CV_32FC1);
	cvSetZero(res_mat);


	// 【4】训练训练集图片 提取图像特征
	IplImage* src;
	IplImage* trainImg = cvCreateImage(cvSize(28, 28), 8, 3);// 定义图片大小
	// 处理HOG特征
	//HOGDescriptor *hog = new HOGDescriptor(cvSize(28, 28), cvSize(14, 14), cvSize(7, 7), cvSize(7, 7), 9);	//默认存储数据方式
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
		//vector<float>descriptors;//存放结果
		hog->compute(trainImg, descriptors, Size(1, 1), Size(0, 0)); //Hog特征计算
		cout << "HOG dims: " << descriptors.size() << endl;
		n = 0;
		for (vector<float>::iterator iter = descriptors.begin(); iter != descriptors.end(); iter++){
			cvmSet(data_mat, i, n, *iter);//存储HOG特征
			n++;}
		cvmSet(res_mat, i, 0, img_catg[i]);
		cout << "Done !!!: " << img_path[i].c_str() << " " << img_catg[i] << endl;
		

	}


	// 【5】创建SVM 并将特征存储到.xml文件中
	CvSVM svm;//新建一个SVM
	CvSVMParams param;//这里是SVM训练相关参数
	CvTermCriteria criteria;
	criteria = cvTermCriteria(CV_TERMCRIT_EPS, 1000, FLT_EPSILON);
	param = CvSVMParams(CvSVM::C_SVC, CvSVM::RBF, 10.0, 0.09, 1.0, 10.0, 0.5, 1.0, NULL, criteria);
	svm.train(data_mat, res_mat, NULL, NULL, param);//训练数据
													//保存训练好的分类器
	svm.save("HOG_SVM_DATA.xml");
	cout << "HOG_SVM_DATA.xml is saved !!! \n exit program" << endl;
	cvReleaseMat(&data_mat);
	cvReleaseMat(&res_mat);
	cvReleaseImage(&trainImg);


	// 【6】结束标志按任意键结束
	system("pause");
	return 0;
}
