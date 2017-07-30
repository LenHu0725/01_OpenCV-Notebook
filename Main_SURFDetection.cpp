//----------------------------------������˵����----------------------------------------
//	����˵�����ο���OpenCV������š����׳���SURF���
//	����������SURF��������
//	�����������ò���ϵͳ��	Windows 10 64bit
//	������������IDE�汾��	Visual Stuido 2015
//	������������Opencv�汾��3.2.0
//--------------------------------------------------------------------------------------

//----------------------------��ͷ�ļ��������ռ�������֡�------------------------------
//					����������������������ͷ�ļ��������ռ�
//--------------------------------------------------------------------------------------
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

//--------------------------------��main()������----------------------------------------
//					����������̨Ӧ�ó������ں�������������￪ʼ
//--------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//��0���ı�console����ɫ���������
	system("color 27");
	//ShowHelpText();
	
	//��1������Դͼ����ʾ
	Mat srcImage1 = imread("MatchTemplate_Img.jpg", 1);
	Mat srcImage2 = imread("MatchTemplate_Temple2.jpg", 2);
	if (!srcImage1.data || !srcImage2.data)	//����Ƿ��ȡ�ɹ�
	{
		printf("ԭͼƬ��ȡ������ȷ����Ŀ¼���Ƿ����֮��ͼƬ~��"); return false;
	}

	imshow("ԭʼͼ1", srcImage1);
	imshow("ԭʼͼ2", srcImage2);

	//��2��������Ҫ�õ��ı�������
	int minHessian = 400;//����SURF�е�hessian��ֵ������������
	//�ڿ��У�typedef SURF SurfFeatureDetector;   typedef SURF SurfDescriptorExtractor;���������ǵȼ۵ģ������� 
	SURF detector(minHessian);//����һ��SurfFeatureDetector(SURF)������������
	std::vector<KeyPoint> keypoints_1, keypoints_2;
		//vectorģ�������ܹ�����������͵Ķ�̬���飬�ܹ�����������͵Ķ�̬���飬�ܹ����Ӻ�ѹ������

	//��3������detect��������SURF�����ؼ��㣬������vector������
	detector.detect(srcImage1, keypoints_1);
	detector.detect(srcImage2, keypoints_2);

	//��4�����������ؼ���
	Mat img_keypoints_1; Mat img_keypoints_2;
	drawKeypoints(srcImage1, keypoints_1, img_keypoints_1,
		Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(srcImage2, keypoints_2, img_keypoints_2,
		Scalar::all(-1), DrawMatchesFlags::DEFAULT);

	//��5����ʾЧ��ͼ
	imshow("��������Ч��ͼ1", img_keypoints_1);
	imshow("��������Ч��ͼ2", img_keypoints_2);

	waitKey(0);
	return 0;
}
