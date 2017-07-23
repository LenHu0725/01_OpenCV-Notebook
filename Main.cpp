/**************************************************************************************
 * Copyright        : BUPT
 * Author           : hx
 * Date             : 2017.07.22
 * Description      : 
***************************************************************************************/

//--------------------------------------------------------------------------------------
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//-----------------------------��ȫ�ֺ����������֡�-------------------------------------
//							������ȫ�ֺ�������
//--------------------------------------------------------------------------------------
void colorReduce( Mat& inputImage,Mat& outputImage, int div );


//-------------------------------��main()������-----------------------------------------
//			����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼִ��
//--------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//��1������ԭʼͼ����ʾ
	Mat srcImage = imread("Lena.jpg");
	imshow("ԭʼͼ��",srcImage);

	//��2����ԭʼͼ�Ĳ����������������Ч��ͼ
	Mat dstImage;
	dstImage.create( srcImage.rows, srcImage.cols, srcImage.type() );	//Ч��ͼ�Ĵ�С��������ԭͼƬ��ͬ

	//��3����¼��ʼʱ��
	double time0 = static_cast<double>(getTickCount());

	//��4��������ɫ�ռ���������
	colorReduce(srcImage,dstImage,32);

	//��5����������ʱ�䲢���
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "�˷�������ʱ��Ϊ�� " << time0 << "��" << endl;		//�������ʱ��

	//��6����ʾЧ��ͼ
	imshow("Ч��ͼ", dstImage);
	waitKey(0);

}


//-----------------------------��colorReduce()������-----------------------------------
//				������ʹ�á�ָ����ʣ�C������[]�����������ɫ�ռ���������
//-------------------------------------------------------------------------------------
//������һ����ָ��������� 
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
	//����׼��
	outputImage = inputImage.clone();	//����ʵ�ε���ʱ����
	int rowNumber = outputImage.rows;	//����
	int colNumber = outputImage.cols*outputImage.channels();	//������ͨ����=ÿһ��Ԫ�صĸ���

	//˫��ѭ�����������е�����ֵ
	for (int i = 0; i < rowNumber; i++)
	{
		uchar* data = outputImage.ptr<uchar>(i);	//��ȡ��i�е��׵�ַ
		for ( int j = 0; j < colNumber; j++ )	//��ѭ��
		{
			//---------------����ʼ����ÿ�����ء�-----------------
			data[j] = data[j] / div*div + div / 2;
			//*data++ = *data/div*div+div/2;	//�ɽ����к����滻Ϊ�þ�
			//-------------------�����������---------------------
		}	//�д������
	}
}