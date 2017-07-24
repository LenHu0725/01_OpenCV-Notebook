/***************************************************************************************
 * Copyright        : BUPT
 * Author           : hx
 * Date             : 2017.07.23
 * Description      : Show Shape
****************************************************************************************/

//-----------------------------��ͷ�ļ��������ռ�������֡�-----------------------------
//						����������������ʹ�õ�ͷ�ļ��������ռ�
//--------------------------------------------------------------------------------------
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//---------------------------------���궨�岿�֡�---------------------------------------
//								  ����:���帨����
//--------------------------------------------------------------------------------------
#define WINDOW_WIDTH 600				//���崰�ڴ�С�ĺ�


//----------------------------------��main()������--------------------------------------
//				����������̨Ӧ�ó�����ں��������ǵĳ�������￪ʼִ��
//--------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//����ͼ��ͼ��ߴ��С
	CvSize sz;				//����ͼ��ߴ�
	sz.height = WINDOW_WIDTH;
	sz.width = WINDOW_WIDTH;

	CvPoint centerpoint;	//����ͼ��ԭ��
	centerpoint.x = WINDOW_WIDTH / 2;
	centerpoint.y = WINDOW_WIDTH / 2;

	CvSize ellsize;			//��Բ���ȣ��������
	ellsize.width = WINDOW_WIDTH / 4;
	ellsize.height = WINDOW_WIDTH / 16;

	//��¼��ʼʱ��
	double time0 = static_cast<double>(getTickCount());

	//����ʹ�� Mat mtx(atomImage)	ת��IplImage Ϊ Mat
	IplImage *atomImage = cvCreateImage( sz, IPL_DEPTH_8U,3 );

	//����ͬʱ����ʹ��Rect( x, y, width, height );
	cvEllipse(atomImage, centerpoint, ellsize, 0, 0, 365, cvScalar(42, 68, 212), 2, 8, 0);

	//��������ʱ�䲢���
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "�˷�������ʱ��Ϊ�� " << time0 << "��" << endl;		//�������ʱ�� ���д�����ʾ����using namespace std
	
	cvShowImage("��ʾͼ��", atomImage);

	waitKey(0);

}
