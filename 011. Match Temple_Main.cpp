/***************************************************************************************
* Copyright        : BUPT
* Author           : hx
* Date             : 2017.07.30
* Description      : Match Temple
***************************************************************************************/

//------------------------【头文件与命名空间包含部分】----------------------------------
//						描述：包含程序所依赖的头文件和命名空间
//--------------------------------------------------------------------------------------
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

//------------------------------【宏定义部分】------------------------------------------
//							描述：定义辅助宏
//--------------------------------------------------------------------------------------
#define WINDOW_NAME1 "【原始图片】"		//定义原始图片窗口显示宏
#define WINDOW_NAME2 "【效果窗口】"		//定义效果图片窗口显示宏

Mat g_srcImage; Mat g_templateImage; Mat g_resultImage;
int g_nMatchMethod;
int g_nMaxTrackbarNum = 5;

//---------------------------【全局函数声明部分】---------------------------------------
//							描述：全局函数的声明
//--------------------------------------------------------------------------------------
void on_Matching(int, void*);

//------------------------------【Main()函数】------------------------------------------
//				描述：控制台应用程序的入口函数，我们的程序从这里开始执行
//--------------------------------------------------------------------------------------
int main(int argv, char** argc)
{
	//【1】载入原图像和模板块
	g_srcImage = imread("Test.png", 1);
	g_templateImage = imread("Template.png", 1);
	
	if (!g_srcImage.data) { printf("读取检测图片文件出错！\n"); return false; }
	if (!g_srcImage.data) { printf("读取模板图片文件出错！\n"); return false; }


	//【2】创建窗口
	namedWindow(WINDOW_NAME1, CV_WINDOW_AUTOSIZE);
	namedWindow(WINDOW_NAME2, CV_WINDOW_AUTOSIZE);

	
	//【3】创建滑动条并进行一次初始化
	createTrackbar("方法", WINDOW_NAME1, &g_nMatchMethod, g_nMaxTrackbarNum, on_Matching);
	on_Matching(0, 0);

	waitKey(0);
	return 0;


}

//----------------------------【on_Matching()函数】--------------------------------------
//								描述：回调函数
//---------------------------------------------------------------------------------------
void on_Matching(int, void*)
{
	//【1】给局部变量初始化
	Mat srcImage;
	g_srcImage.copyTo(srcImage);


	//【2】初始化用于结果输出的矩阵
	int resultImage_cols = g_srcImage.cols - g_templateImage.cols + 1;
	int resultImage_rows = g_srcImage.rows - g_templateImage.rows + 1;
	g_resultImage.create(resultImage_cols, resultImage_rows, CV_32FC1);


	//【3】进行匹配和标准化
	matchTemplate(g_srcImage, g_templateImage, g_resultImage, g_nMatchMethod);
	normalize(g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat());


	//【4】通过函数minMaxLoc定位最匹配的位置
	double minValue; double maxValue; Point minLocation; Point maxLocation;Point matchaLocation;
	minMaxLoc(g_resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat());

	//【5】对于方法SQDIFF和SQDIFF_NORMED，越小的数只有这更高的匹配结果，而其余的方法，数值越大匹配效果越好
	//此句代码的OpenCV2版为：
	//if(g_nMatchMethod == CV_TM_SQDIFF || g_nMatchMethod == CV_TM_SQDIFF_NORMED )
	if (g_nMatchMethod == TM_SQDIFF || g_nMatchMethod== TM_SQDIFF_NORMED )
		{ matchaLocation = minLocation; }
	else
		{matchaLocation = maxLocation;}
	//【6】绘制矩形，并显示最终结果
	rectangle(srcImage,
		matchaLocation, 
		Point(matchaLocation.x + g_templateImage.cols, matchaLocation.y + g_templateImage.rows),
		Scalar(0, 0, 255), 2, 8, 0);

	cout << "x:" << matchaLocation.x << "  " << "y:" << matchaLocation.y << endl;
	cout << "cols:" << g_templateImage.cols << "  " << "rows:" << g_templateImage.rows << endl;

	imshow(WINDOW_NAME1, srcImage);
	imshow(WINDOW_NAME2, g_resultImage);

}

