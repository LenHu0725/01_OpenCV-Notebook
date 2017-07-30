//----------------------------------������˵����----------------------------------------
//		����˵�����ο���OpenCV������š����׳���SURF��������
//		����������SURF��������
//		�����������ò���ϵͳ��	Windows 10 64bit
//		������������IDE�汾��	Visual Stuido 2015
//		������������Opencv�汾��2.4.9
//--------------------------------------------------------------------------------------


//--------------------------��ͷ�ļ��������ռ�������֡�--------------------------------
//				���������������ͷ�ļ�����������ռ�
//--------------------------------------------------------------------------------------
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <iostream>
using namespace cv;
using namespace std;

//--------------------------------��main()������----------------------------------------
//				����������̨Ӧ�ó������ں�������������￪ʼ
//--------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//��1�������ز�ͼ
	Mat srcImage1 = imread("srcImage_1.jpg", 1);
	Mat srcImage2 = imread("srcImage_2.jpg", 1);
	if (!srcImage1.data || !srcImage2.data) {
		printf("��ȡ�ļ����������Ƿ���ԭͼ��~   /n"); return 233;
	}

	//��2��ʹ��SURF���Ӽ��ؼ���
	int minHessian = 700;	//SURF�㷨�еĵ�Hessian��ֵ
	SurfFeatureDetector detector(minHessian);	//����һ��SurfFeatureDetector(SURF)������������
	std::vector<KeyPoint> keyPoint1, keyPoint2;	//vectorģ���࣬����������͵Ķ�̬����

	//��3������detect��������SURF�����ؼ��㣬������vector��
	detector.detect(srcImage1, keyPoint1);
	detector.detect(srcImage2, keyPoint2);

	//��4������������
	SurfDescriptorExtractor extractor;
	Mat descriptors1, descriptors2;
	extractor.compute(srcImage1, keyPoint1, descriptors1);
	extractor.compute(srcImage2, keyPoint2, descriptors2);

	//��5��ʹ��BruteForce����ƥ��
	//ʵ����һ��ƥ����
	BruteForceMatcher< L2<float> >matcher;
	std::vector <DMatch> matches;
	//ƥ������ͼ�е������ӣ�descriptors��
	matcher.match(descriptors1, descriptors2, matches);

	//��6�����ƴ�����ͼ����ƥ����Ĺؼ���
	Mat imgMatches;
	drawMatches(srcImage1, keyPoint1, srcImage2, keyPoint2, matches, imgMatches);	//���л���

	//��7����ʾЧ��ͼ
	namedWindow("ƥ��ͼ", WINDOW_NORMAL );
	imshow("ƥ��ͼ", imgMatches);
	waitKey(0);
	return 0;

}



