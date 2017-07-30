/***************************************************************************************
* Copyright        : BUPT
* Author           : hx
* Date             : 2017.07.30
* Description      : Match Temple
***************************************************************************************/

//------------------------��ͷ�ļ��������ռ�������֡�----------------------------------
//						����������������������ͷ�ļ��������ռ�
//--------------------------------------------------------------------------------------
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

//------------------------------���궨�岿�֡�------------------------------------------
//							���������帨����
//--------------------------------------------------------------------------------------
#define WINDOW_NAME1 "��ԭʼͼƬ��"		//����ԭʼͼƬ������ʾ��
#define WINDOW_NAME2 "��Ч�����ڡ�"		//����Ч��ͼƬ������ʾ��

Mat g_srcImage; Mat g_templateImage; Mat g_resultImage;
int g_nMatchMethod;
int g_nMaxTrackbarNum = 5;

//---------------------------��ȫ�ֺ����������֡�---------------------------------------
//							������ȫ�ֺ���������
//--------------------------------------------------------------------------------------
void on_Matching(int, void*);

//------------------------------��Main()������------------------------------------------
//				����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼִ��
//--------------------------------------------------------------------------------------
int main(int argv, char** argc)
{
	//��1������ԭͼ���ģ���
	g_srcImage = imread("Test.png", 1);
	g_templateImage = imread("Template.png", 1);
	
	if (!g_srcImage.data) { printf("��ȡ���ͼƬ�ļ�����\n"); return false; }
	if (!g_srcImage.data) { printf("��ȡģ��ͼƬ�ļ�����\n"); return false; }


	//��2����������
	namedWindow(WINDOW_NAME1, CV_WINDOW_AUTOSIZE);
	namedWindow(WINDOW_NAME2, CV_WINDOW_AUTOSIZE);

	
	//��3������������������һ�γ�ʼ��
	createTrackbar("����", WINDOW_NAME1, &g_nMatchMethod, g_nMaxTrackbarNum, on_Matching);
	on_Matching(0, 0);

	waitKey(0);
	return 0;


}

//----------------------------��on_Matching()������--------------------------------------
//								�������ص�����
//---------------------------------------------------------------------------------------
void on_Matching(int, void*)
{
	//��1�����ֲ�������ʼ��
	Mat srcImage;
	g_srcImage.copyTo(srcImage);


	//��2����ʼ�����ڽ������ľ���
	int resultImage_cols = g_srcImage.cols - g_templateImage.cols + 1;
	int resultImage_rows = g_srcImage.rows - g_templateImage.rows + 1;
	g_resultImage.create(resultImage_cols, resultImage_rows, CV_32FC1);


	//��3������ƥ��ͱ�׼��
	matchTemplate(g_srcImage, g_templateImage, g_resultImage, g_nMatchMethod);
	normalize(g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat());


	//��4��ͨ������minMaxLoc��λ��ƥ���λ��
	double minValue; double maxValue; Point minLocation; Point maxLocation;Point matchaLocation;
	minMaxLoc(g_resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat());

	//��5�����ڷ���SQDIFF��SQDIFF_NORMED��ԽС����ֻ������ߵ�ƥ������������ķ�������ֵԽ��ƥ��Ч��Խ��
	//�˾�����OpenCV2��Ϊ��
	//if(g_nMatchMethod == CV_TM_SQDIFF || g_nMatchMethod == CV_TM_SQDIFF_NORMED )
	if (g_nMatchMethod == TM_SQDIFF || g_nMatchMethod== TM_SQDIFF_NORMED )
		{ matchaLocation = minLocation; }
	else
		{matchaLocation = maxLocation;}
	//��6�����ƾ��Σ�����ʾ���ս��
	rectangle(srcImage,
		matchaLocation, 
		Point(matchaLocation.x + g_templateImage.cols, matchaLocation.y + g_templateImage.rows),
		Scalar(0, 0, 255), 2, 8, 0);

	cout << "x:" << matchaLocation.x << "  " << "y:" << matchaLocation.y << endl;
	cout << "cols:" << g_templateImage.cols << "  " << "rows:" << g_templateImage.rows << endl;

	imshow(WINDOW_NAME1, srcImage);
	imshow(WINDOW_NAME2, g_resultImage);

}

