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

//-----------------------------【全局函数声明部分】-------------------------------------
//							描述：全局函数声明
//--------------------------------------------------------------------------------------
void colorReduce( Mat& inputImage,Mat& outputImage, int div );


//-------------------------------【main()函数】-----------------------------------------
//			描述：控制台应用程序的入口函数，我们的程序从这里开始执行
//--------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//【1】创建原始图并显示
	Mat srcImage = imread("Lena.jpg");
	imshow("原始图像",srcImage);

	//【2】按原始图的参数规格来创建创建效果图
	Mat dstImage;
	dstImage.create( srcImage.rows, srcImage.cols, srcImage.type() );	//效果图的大小、类型与原图片相同

	//【3】记录起始时间
	double time0 = static_cast<double>(getTickCount());

	//【4】调用颜色空间所见函数
	colorReduce(srcImage,dstImage,32);

	//【5】计算运行时间并输出
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "此方法运行时间为： " << time0 << "秒" << endl;		//输出运行时间

	//【6】显示效果图
	imshow("效果图", dstImage);
	waitKey(0);

}


//-----------------------------【colorReduce()函数】-----------------------------------
//				描述：使用【指针访问：C操作符[]】方法版的颜色空间缩减函数
//-------------------------------------------------------------------------------------
//【方法一】用指针访问像素 
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
	//参数准备
	outputImage = inputImage.clone();	//复制实参到临时变量
	int rowNumber = outputImage.rows;	//行数
	int colNumber = outputImage.cols*outputImage.channels();	//列数×通道数=每一行元素的个数

	//双重循环，遍历所有的像素值
	for (int i = 0; i < rowNumber; i++)
	{
		uchar* data = outputImage.ptr<uchar>(i);	//获取第i行的首地址
		for ( int j = 0; j < colNumber; j++ )	//列循环
		{
			//---------------【开始处理每个像素】-----------------
			data[j] = data[j] / div*div + div / 2;
			//*data++ = *data/div*div+div/2;	//可将上行函数替换为该句
			//-------------------【处理结束】---------------------
		}	//行处理结束
	}
}