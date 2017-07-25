/****************************************************************
* Copyright        : BUPT
* Author           : hx
* Date             : 2017.07.25
* Description      : ��/������ �� ��ñ/��ñ �� ��ʴ/����
*****************************************************************/

//----------------------------��ͷ�ļ��������ռ�������֡�------------------------------
//						����������������������ͷ�ļ��������ռ�
//--------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

//--------------------------------��ȫ�ֱ����������֡�-----------------------------------
//							������ȫ�ֱ�������
//---------------------------------------------------------------------------------------
Mat g_srcImage, g_dstImage;		//ԭʼͼ��Ч��ͼ
int g_nElementShape;			//Ԫ�ؽṹ����״

//�������ܵ�TrackBarλ�ò���
int g_nMaxIteratonNum = 10;
int g_nOpenCloseNum = 0;
int g_nErodeDilateNum = 0;
int g_nTopBlackHatNum = 0;


//--------------------------------��ȫ�ֺ����������֡�-----------------------------------
//							������ȫ�ֺ�������
//---------------------------------------------------------------------------------------
static void on_OpenClose(int, void*);		//�ص�����
static void on_ErodeDilate(int, void*);		//�ص�����
static void on_TopBlackHat(int, void*);		//�ص�����
static void ShowHelpText();					//������ʾ

//---------------------------------��main()������----------------------------------------
int main(int argc, char** argv)
{
	//����Դͼ
	g_srcImage = imread("Lenna.jpg");		//����Ŀ¼����Ҫ��һ����ΪLenna.jpg���ز�ͼ
	if (!g_srcImage.data) { printf("��ȡsrcImage�ļ�����!	\n"); return false; }

	//��ʾԭʼͼ
	namedWindow("��ԭʼͼ��");
	imshow("��ԭʼͼ��", g_srcImage);
	
	//��������ͼ�񴰿�
	namedWindow("��������/�����㡿", WINDOW_AUTOSIZE );
	namedWindow("����ʴ/���͡�", WINDOW_AUTOSIZE );
	namedWindow("����ñ/��ñ��", WINDOW_AUTOSIZE );

	//������ֵ
	g_nOpenCloseNum = 9;
	g_nErodeDilateNum = 9;
	g_nTopBlackHatNum = 2;

	//�ֱ�Ϊ�������ڴ���������
	createTrackbar("����ֵ", "��������/�����㡿", 
		&g_nOpenCloseNum, g_nMaxIteratonNum * 2 + 1, on_OpenClose);
	createTrackbar("����ֵ", "����ʴ/���͡�", 
		&g_nErodeDilateNum, g_nMaxIteratonNum * 2 + 1, on_ErodeDilate);
	createTrackbar("����ֵ", "��ñ/��è", 
		&g_nTopBlackHatNum, g_nMaxIteratonNum * 2 + 1, on_TopBlackHat);

	//��ѯ��ȡ������Ϣ
	while (true)
	{
		int c;

		//������ֵ
		on_OpenClose(g_nOpenCloseNum, 0);
		on_ErodeDilate(g_nErodeDilateNum, 0);
		on_TopBlackHat(g_nTopBlackHatNum, 0);

		//��ȡ����
		c = waitKey(0);

		//���¼��̰���Q����ESC�������˳�
		if ((char)c == 'q' || (char)c == 27)
			break;
		//���°�������1��ʹ����Բ��Elliptic���ṹԪ�ؽṹԪ��MORPH_ELLIPSE
		else if ((char)c == 49)		//���̰���1��ASC����Ϊ49
			{g_nElementShape = MORPH_ELLIPSE;}
		//���°���2��ʹ�þ��Σ�Rectangle������Ԫ��MORPH_RECT
		else if ((char)c == 50)	//����2��ASC����Ϊ50
			{g_nElementShape = MORPH_RECT;}
		else if ((char)c == 51)	//����3��ASC����Ϊ51
			{g_nElementShape = MORPH_CROSS;}
		else if ((char)c == ' ')
		{g_nElementShape = (g_nElementShape + 1) % 3;}
	}


	return 0;
}


//---------------------------��on_OpenClose����������---------------------------------
//					��������������/�����㡿���ڵĻص�����
//------------------------------------------------------------------------------------
static void on_OpenClose(int, void*)
{
	//ƫ��������
	int offset = g_nOpenCloseNum - g_nMaxIteratonNum;		//ƫ����
	int Absolute_offset = offset > 0 ? offset : -offset;	//ƫ��������ֵ
	//�Զ����
	Mat element = getStructuringElement(g_nElementShape,
		Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset));
	//���в���
	if (offset < 0)
	{
		//�˾�����OpenCV2�İ汾Ϊ��
		//morphologyEx(g_srcImage,g_dstImage,CV_MOP_OPEN,element);
		//�˾�����OpenCV3�汾Ϊ��
		morphologyEx(g_srcImage, g_dstImage, MORPH_OPEN, element);
		//��ʾͼ��
		imshow("��������/�����㡿",g_dstImage);
	}

}

//---------------------------��on_ErodeDilate()������---------------------------------
//				����������ʴ/���͡����ڵĻص�����
//------------------------------------------------------------------------------------
static void on_ErodeDilate(int, void*)
{
	//ƫ�����Ķ���
	int offset = g_nErodeDilateNum - g_nMaxIteratonNum;		//ƫ����
	int Absolute_offset = offset > 0 ? offset : -offset;	//ƫ��������ֵ
	//�Զ����
	Mat element = getStructuringElement(g_nElementShape,
		Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset));
	//���в���
	if (offset < 0)
		erode(g_srcImage, g_dstImage, element);
	else
		dilate(g_srcImage, g_dstImage, element);
	//��ʾͼ��
	imshow("����ʴ/���͡�", g_dstImage);
}

//--------------------------��on_TopBlackHat����������---------------------------------
//					����������ñ����/��ñ���㡿���ڵĻص�����
//-------------------------------------------------------------------------------------
static void on_TopBlackHat(int, void*)
{
	//ƫ�����Ķ���
	int offset = g_nTopBlackHatNum - g_nMaxIteratonNum;		//ƫ����
	int Absolute_offset = offset > 0 ? offset : -offset;	//ƫ��������ֵ
	//�Զ����
	Mat element = getStructuringElement(g_nElementShape,
		Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset));
	//���в���
	if (offset < 0)
		morphologyEx(g_srcImage, g_dstImage, MORPH_TOPHAT, element);
	else
		morphologyEx(g_srcImage, g_dstImage, MORPH_BLACKHAT, element);
	//��ʾͼ��
	imshow("����ñ/��ñ��", g_dstImage);
}
