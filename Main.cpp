/******************************************************************************************
 * Copyright        : BUPT
 * Author           : hx
 * Date             : 2017.07.21
 * Description      : 含有椒盐噪声的图像均值滤波后 用Canny算法检测边缘
*******************************************************************************************/

//----------------------------【头文件、命名空间包含部分】-----------------------------------
//							描述：包含程序所使用的头文件和命名空间
//-------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

//-------------------------------【main()函数】----------------------------------------------
int main()
{
	//【0】载入原始图
	Mat srcImage = imread( "Lenna_Noise.jpg" );			//读取图片
	imshow( "【原始图】Canny边缘检测",srcImage );		//显示原图
	Mat dstImage, edge, grayImage;			//参数定义

	//【1】创建与src同类型和大小的矩阵(dst)
	dstImage.create(srcImage.size(), srcImage.type());

	//【2】将原图像转化为灰度图像
	cvtColor( srcImage,grayImage,COLOR_BGR2GRAY );

	//【3】先使用 3×3 内核降噪
	blur( grayImage,edge,Size(3,3) );

	//【4】运行Canny算子
	Canny( edge, edge, 3, 9, 3 );							//Canny算子两个阈值选择问题

	//【5】显示效果图
	imshow("【效果图】Canny边缘检测", edge);

	waitKey(0);

	return 0;

}