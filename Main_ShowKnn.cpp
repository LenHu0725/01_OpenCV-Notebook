/*****************************************************************************************
* Copyright        : BUPT
* Author           : hx
* Date             : 2017.07.25
* Description      : Show Knn
******************************************************************************************/

//----------------------------��ͷ�ļ��������ռ�������֡�------------------------------
//			����������������������ͷ�ļ��������ռ�
//--------------------------------------------------------------------------------------
#include "ml.h"
#include "highgui.h"


//--------------------------------��main()������----------------------------------------
//		����������̨Ӧ�ó������ں�������������￪ʼ
//--------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	const int K = 10; //ÿ�������������ھӸ���
	int i, j, k, accuracy;
	float response;   //�����Ӧ
	int train_sample_count = 100; //ѵ������������
	CvRNG rng_state = cvRNG(-1);  //�����������
	CvMat* trainData = cvCreateMat(train_sample_count, 2, CV_32FC1); //ѵ�����ݼ���ÿһ������������
	CvMat* trainClasses = cvCreateMat(train_sample_count, 1, CV_32FC1);//ѵ����������Ӧ
	IplImage* img = cvCreateImage(cvSize(500, 500), 8, 3); //����ѵ��������ͼ��
	float _sample[2];
	CvMat sample = cvMat(1, 2, CV_32FC1, _sample); //����������������
	cvZero(img);

	CvMat trainData1, trainData2, trainClasses1, trainClasses2;

	// �γ�ѵ��������
	cvGetRows(trainData, &trainData1, 0, train_sample_count / 2);  //�������е�ǰ��һ������
																   //��һ������ ��ÿ�������ľ�ֵΪ200����׼��Ϊ50
	cvRandArr(&rng_state, &trainData1, CV_RAND_NORMAL, cvScalar(200, 200), cvScalar(50, 50));

	cvGetRows(trainData, &trainData2, train_sample_count / 2, train_sample_count);//�������еĺ���һ������
																				  //�ڶ������� ��ÿ�������ľ�ֵΪ300����׼��Ϊ50
	cvRandArr(&rng_state, &trainData2, CV_RAND_NORMAL, cvScalar(300, 300), cvScalar(50, 50));

	// ���õ�һ������������ǩ
	cvGetRows(trainClasses, &trainClasses1, 0, train_sample_count / 2);
	cvSet(&trainClasses1, cvScalar(1));
	// ���õڶ�������������ǩ
	cvGetRows(trainClasses, &trainClasses2, train_sample_count / 2, train_sample_count);
	cvSet(&trainClasses2, cvScalar(2));

	// ѵ��������
	CvKNearest knn(trainData, trainClasses, 0, false, K); //���õڶ������캯��
	CvMat* nearests = cvCreateMat(1, K, CV_32FC1); //һ��������k���ھӵ���Ӧ

	for (i = 0; i < img->height; i++)
	{
		for (j = 0; j < img->width; j++)
		{
			//����һ������������
			sample.data.fl[0] = (float)j;//��һά��������������������ֲ�
			sample.data.fl[1] = (float)i;//�ڶ�ά��������������������ֲ�

										 // ���Ʋ�����������Ӧ������ȡ����������K���ھӵ�����ǩ 
			response = knn.find_nearest(&sample, K, 0, 0, nearests, 0);

			//����K���ھ��г��ִ��������������͵��ھӵ���Ŀ
			for (k = 0, accuracy = 0; k < K; k++)
			{
				if (nearests->data.fl[k] == response)
					accuracy++;
			}
			// �������Ŷ�accuracy�Ĵ�С���imgͼ���е�ÿ������λ�õ���� 
			cvSet2D(img, i, j, response == 1 ?
				(accuracy > 5 ? CV_RGB(180, 0, 0) : CV_RGB(180, 120, 0)) :
				(accuracy > 5 ? CV_RGB(0, 180, 0) : CV_RGB(120, 120, 0)));
		}
	}

	// ��img�ϻ���ԭʼ��ѵ������
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
	//��ʾ������
	cvNamedWindow("classifier result", 1);
	cvShowImage("classifier result", img);
	cvWaitKey(0);

	cvReleaseMat(&trainClasses);
	cvReleaseMat(&trainData);
	return 0;
}