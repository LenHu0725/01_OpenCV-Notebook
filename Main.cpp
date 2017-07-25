/*****************************************************************************************
* Copyright        : BUPT
* Author           : hx
* Date             : 2017.07.25
* Description      : 
******************************************************************************************/


//----------------------------��ͷ�ļ��������ռ�������֡�-----------------------------
//							�����������������õ�ͷ�ļ�
//-------------------------------------------------------------------------------------
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
using namespace cv;

//----------------------------------���궨�岿�֡�-------------------------------------
//							������������������
//-------------------------------------------------------------------------------------
#define WINDOW_NAME1 "ԭʼͼ"				//Ϊ��ʾ���ڶ����

//-------------------------------��ȫ�ֱ����������֡�----------------------------------
//								������ȫ�ֱ���
//-------------------------------------------------------------------------------------
Mat g_srcImage; Mat g_hsvImage; Mat g_hueImage;
int g_bins = 30;	//ֱ��ͼ���

//-------------------------------��ȫ�ֺ����������֡�----------------------------------
//							������ȫ�ֺ�������
//-------------------------------------------------------------------------------------
void on_BinChange(int, void*);

//---------------------------------��Main()������--------------------------------------
//							����:����������￪ʼ
//-------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//��1����ȡԴͼ�񣬲�ת����HSV�ռ�
	g_srcImage = imread("Hand_1.jpg");
	if (!g_srcImage.data) 
		{ printf("��ȡͼƬ�ļ�������ȷ��Ŀ¼���Ƿ���imread����ָ��ͼƬ���ڣ�\n"); return false; }
	cvtColor(g_srcImage, g_hsvImage, COLOR_BGR2HSV);

	//��2������Hueɫ��ͨ��
	g_hueImage.create(g_hsvImage.size(), g_hsvImage.depth());
	int ch[] = { 0,0 };
	//������ʾͼ��
	imshow("HSV�ļ�", g_hsvImage);
	mixChannels(&g_hsvImage, 1, &g_hueImage, 1, ch, 1);

	//��3������Trackbar������bin����Ŀ
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	createTrackbar("ɫ�����", WINDOW_NAME1, &g_bins, 180, on_BinChange);
	on_BinChange(0, 0);

	//��4����ʾЧ��ͼ
	imshow(WINDOW_NAME1, g_srcImage);

	//�ȴ��û�����
	waitKey(0);
	return 0;

}

//----------------------------��on_HoughLines()������----------------------------------
//						��������Ӧ�������ƶ���Ϣ�Ļص�����
//-------------------------------------------------------------------------------------
void on_BinChange(int, void*)
{
	//��1������׼��
	MatND hist;
	int histSize = MAX(g_bins, 2);
	float hue_range[] = { 0, 180 };
	const float* ranges = { hue_range };

	//��2������ֱ��ͼ����һ��
	calcHist(&g_hueImage, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
	normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

	//��3�����㷴��ͶӰ
	MatND backproj;
	calcBackProject(&g_hueImage, 1, 0, hist, backproj, &ranges, 1, true);

	//��4����ʾ����ͶӰ
	imshow("����ͶӰͼ", backproj);

	//��5������ֱ��ͼ�Ĳ�������
	int w = 400; int h = 400;
	int bin_w = cvRound((double)w / histSize);
	Mat histImg = Mat::zeros(w, h, CV_8UC3);

	//��6������ֱ��ͼ
	for (int i = 0; i < g_bins; i++)
	{
		rectangle(histImg, Point(i*bin_w, h), Point((i + 1)*bin_w,
			h - cvRound(hist.at<float>(i)*h / 255.0)), Scalar(100, 123, 255), -1);
	}

	//��7����ʾֱ��ͼ����
	imshow("ֱ��ͼ", histImg);
}


