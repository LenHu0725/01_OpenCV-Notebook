/*****************************************************************************************
 * Copyright        : BUPT
 * Author           : hx
 * Date             : 2017.07.25
 * Description      : Read and write XML
******************************************************************************************/

//-----------------------��ͷ�ļ��������ռ�������֡�--------------------------------
//		    ����������������ʹ�õ�ͷ�ļ��������ռ�
//-----------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <time.h>

using namespace cv;


//--------------------------------��main()������--------------------------------------
//				������ȫ�����������￪ʼ
//------------------------------------------------------------------------------------
int main( int argc, char** argv )
{
	//��ʼ��
	FileStorage Text("test.xml", FileStorage::WRITE);

	//��ʼ�ļ�д��
	Text << "frameCount" << 5;
	time_t rawtime; time(&rawtime);
	Text << "calibrationDate" << asctime(localtime(&rawtime));
	Mat cameraMatrix = (Mat_<double>(3, 3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);
	Mat distCoeffs = (Mat_<double>(5, 1) << 0.1, 0.01, -0.001, 0, 0);
	Text << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;
	Text << "features" << "[";
	for (int i = 0; i < 3; i++)
	{
		int x = rand() % 640;
		int y = rand() % 480;
		uchar lbp = rand() % 256;
		Text << "{:" << "x" << x << "y" << y << "lbp" << "[:";
		for (int j = 0; j < 8; j++)
			Text << ((lbp >> j) & 1);
		Text << "]" << "}";
	}
	Text << "]";
	Text.release();

	//�ļ�����No element name has been given����ʾ��ע�����¼���
	//vectorԪ��Ҫע���ڵ�һ��Ԫ��ǰ���ϡ�[���������һ��Ԫ��ǰ����"]"
	//����map�ṹ�Ĳ���ʹ�õķ�����"{"��"}"
	//http://blog.csdn.net/yang_xian521/article/details/6897684
	printf("�ļ���ȡ��ϣ����ڹ���Ŀ¼�²鿴�����ļ�~");
	getchar();

	return 0;
}