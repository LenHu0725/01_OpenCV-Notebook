/*****************************************************************************************
* Copyright        : BUPT
* Author           : hx
* Date             : 2017.07.25
* Description      : Show Knn
******************************************************************************************/

//----------------------------【头文件、命名空间包含部分】------------------------------
//			描述：包含程序所依赖的头文件和命名空间
//--------------------------------------------------------------------------------------
#include "ml.h"
#include "highgui.h"


//--------------------------------【main()函数】----------------------------------------
//		描述：控制台应用程序的入口函数，程序从这里开始
//--------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	const int K = 10; //每个输入向量的邻居个数
	int i, j, k, accuracy;
	float response;   //输出响应
	int train_sample_count = 100; //训练样本的数量
	CvRNG rng_state = cvRNG(-1);  //随机数发生器
	CvMat* trainData = cvCreateMat(train_sample_count, 2, CV_32FC1); //训练数据集，每一行有两个特征
	CvMat* trainClasses = cvCreateMat(train_sample_count, 1, CV_32FC1);//训练样本的响应
	IplImage* img = cvCreateImage(cvSize(500, 500), 8, 3); //绘制训练样本的图像
	float _sample[2];
	CvMat sample = cvMat(1, 2, CV_32FC1, _sample); //单个样本特征向量
	cvZero(img);

	CvMat trainData1, trainData2, trainClasses1, trainClasses2;

	// 形成训练样本集
	cvGetRows(trainData, &trainData1, 0, train_sample_count / 2);  //总样本中的前面一半样本
																   //第一类样本 ：每个特征的均值为200，标准差为50
	cvRandArr(&rng_state, &trainData1, CV_RAND_NORMAL, cvScalar(200, 200), cvScalar(50, 50));

	cvGetRows(trainData, &trainData2, train_sample_count / 2, train_sample_count);//总样本中的后面一半样本
																				  //第二类样本 ：每个特征的均值为300，标准差为50
	cvRandArr(&rng_state, &trainData2, CV_RAND_NORMAL, cvScalar(300, 300), cvScalar(50, 50));

	// 设置第一类样本的类别标签
	cvGetRows(trainClasses, &trainClasses1, 0, train_sample_count / 2);
	cvSet(&trainClasses1, cvScalar(1));
	// 设置第二类样本的类别标签
	cvGetRows(trainClasses, &trainClasses2, train_sample_count / 2, train_sample_count);
	cvSet(&trainClasses2, cvScalar(2));

	// 训练分类器
	CvKNearest knn(trainData, trainClasses, 0, false, K); //调用第二个构造函数
	CvMat* nearests = cvCreateMat(1, K, CV_32FC1); //一个样本的k个邻居的响应

	for (i = 0; i < img->height; i++)
	{
		for (j = 0; j < img->width; j++)
		{
			//构造一个测试样本，
			sample.data.fl[0] = (float)j;//第一维特征沿着列增长，横向分布
			sample.data.fl[1] = (float)i;//第二维特征沿着行增长，纵向分布

										 // 估计测试样本的响应，并获取输入样本的K个邻居的类别标签 
			response = knn.find_nearest(&sample, K, 0, 0, nearests, 0);

			//计算K个邻居中出现次数最多的那种类型的邻居的数目
			for (k = 0, accuracy = 0; k < K; k++)
			{
				if (nearests->data.fl[k] == response)
					accuracy++;
			}
			// 基于置信度accuracy的大小标记img图像中的每个像素位置的类别 
			cvSet2D(img, i, j, response == 1 ?
				(accuracy > 5 ? CV_RGB(180, 0, 0) : CV_RGB(180, 120, 0)) :
				(accuracy > 5 ? CV_RGB(0, 180, 0) : CV_RGB(120, 120, 0)));
		}
	}

	// 在img上画出原始的训练样本
	for (i = 0; i < train_sample_count / 2; i++)
	{
		CvPoint pt;
		pt.x = cvRound(trainData1.data.fl[i * 2]);
		pt.y = cvRound(trainData1.data.fl[i * 2 + 1]);
		cvCircle(img, pt, 2, CV_RGB(255, 0, 0), CV_FILLED);
		pt.x = cvRound(trainData2.data.fl[i * 2]);
		pt.y = cvRound(trainData2.data.fl[i * 2 + 1]);
		cvCircle(img, pt, 2, CV_RGB(0, 255, 0), CV_FILLED);
	}
	//显示分类结果
	cvNamedWindow("classifier result", 1);
	cvShowImage("classifier result", img);
	cvWaitKey(0);

	cvReleaseMat(&trainClasses);
	cvReleaseMat(&trainData);
	return 0;
}
