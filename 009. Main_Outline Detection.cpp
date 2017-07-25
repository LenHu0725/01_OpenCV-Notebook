/****************************************************************
* Copyright        : BUPT
* Author           : hx
* Date             : 2017.07.25
* Description      : 开/闭运算 、 顶帽/黑帽 、 腐蚀/膨胀
*****************************************************************/

//----------------------------【头文件、命名空间包含部分】------------------------------
//			描述：包含程序所依赖的头文件和命名空间
//--------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

//--------------------------------【全局变量声明部分】-----------------------------------
//				描述：全局变量声明
//---------------------------------------------------------------------------------------
Mat g_srcImage, g_dstImage;		//原始图和效果图
int g_nElementShape;			//元素结构的形状

//变量接受的TrackBar位置参数
int g_nMaxIteratonNum = 10;
int g_nOpenCloseNum = 0;
int g_nErodeDilateNum = 0;
int g_nTopBlackHatNum = 0;


//--------------------------------【全局函数声明部分】-----------------------------------
//				描述：全局函数声明
//---------------------------------------------------------------------------------------
static void on_OpenClose(int, void*);		//回调函数
static void on_ErodeDilate(int, void*);		//回调函数
static void on_TopBlackHat(int, void*);		//回调函数
static void ShowHelpText();					//文字显示

//---------------------------------【main()函数】----------------------------------------
int main(int argc, char** argv)
{
	//载入源图
	g_srcImage = imread("Lenna.jpg");		//工程目录下需要有一张名为Lenna.jpg的素材图
	if (!g_srcImage.data) { printf("读取srcImage文件错误!	\n"); return false; }

	//显示原始图
	namedWindow("【原始图】");
	imshow("【原始图】", g_srcImage);
	
	//创建三个图像窗口
	namedWindow("【开运算/闭运算】", WINDOW_AUTOSIZE );
	namedWindow("【腐蚀/膨胀】", WINDOW_AUTOSIZE );
	namedWindow("【顶帽/黑帽】", WINDOW_AUTOSIZE );

	//参数赋值
	g_nOpenCloseNum = 9;
	g_nErodeDilateNum = 9;
	g_nTopBlackHatNum = 2;

	//分别为三个窗口创建滚动条
	createTrackbar("迭代值", "【开运算/闭运算】", 
		&g_nOpenCloseNum, g_nMaxIteratonNum * 2 + 1, on_OpenClose);
	createTrackbar("迭代值", "【腐蚀/膨胀】", 
		&g_nErodeDilateNum, g_nMaxIteratonNum * 2 + 1, on_ErodeDilate);
	createTrackbar("迭代值", "顶帽/黑猫", 
		&g_nTopBlackHatNum, g_nMaxIteratonNum * 2 + 1, on_TopBlackHat);

	//轮询获取按键信息
	while (true)
	{
		int c;

		//参数赋值
		on_OpenClose(g_nOpenCloseNum, 0);
		on_ErodeDilate(g_nErodeDilateNum, 0);
		on_TopBlackHat(g_nTopBlackHatNum, 0);

		//获取按键
		c = waitKey(0);

		//按下键盘按键Q或者ESC，程序退出
		if ((char)c == 'q' || (char)c == 27)
			break;
		//按下按键按键1，使用椭圆（Elliptic）结构元素结构元素MORPH_ELLIPSE
		else if ((char)c == 49)		//键盘按键1的ASCⅡ码为49
			{g_nElementShape = MORPH_ELLIPSE;}
		//按下按键2，使用矩形（Rectangle）机构元素MORPH_RECT
		else if ((char)c == 50)	//键盘2的ASCⅡ码为50
			{g_nElementShape = MORPH_RECT;}
		else if ((char)c == 51)	//键盘3的ASCⅡ码为51
			{g_nElementShape = MORPH_CROSS;}
		else if ((char)c == ' ')
		{g_nElementShape = (g_nElementShape + 1) % 3;}
	}


	return 0;
}


//---------------------------【on_OpenClose（）函数】---------------------------------
//			描述：【开运算/闭运算】窗口的回调函数
//------------------------------------------------------------------------------------
static void on_OpenClose(int, void*)
{
	//偏移量定义
	int offset = g_nOpenCloseNum - g_nMaxIteratonNum;		//偏移量
	int Absolute_offset = offset > 0 ? offset : -offset;	//偏移量绝对值
	//自定义核
	Mat element = getStructuringElement(g_nElementShape,
		Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset));
	//进行操作
	if (offset < 0)
	{
		//此句代码的OpenCV2的版本为：
		//morphologyEx(g_srcImage,g_dstImage,CV_MOP_OPEN,element);
		//此句代码的OpenCV3版本为：
		morphologyEx(g_srcImage, g_dstImage, MORPH_OPEN, element);
		//显示图像
		imshow("【开运算/闭运算】",g_dstImage);
	}

}

//---------------------------【on_ErodeDilate()函数】---------------------------------
//			描述：【腐蚀/膨胀】窗口的回调函数
//------------------------------------------------------------------------------------
static void on_ErodeDilate(int, void*)
{
	//偏移量的定义
	int offset = g_nErodeDilateNum - g_nMaxIteratonNum;		//偏移量
	int Absolute_offset = offset > 0 ? offset : -offset;	//偏移量绝对值
	//自定义核
	Mat element = getStructuringElement(g_nElementShape,
		Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset));
	//进行操作
	if (offset < 0)
		erode(g_srcImage, g_dstImage, element);
	else
		dilate(g_srcImage, g_dstImage, element);
	//显示图像
	imshow("【腐蚀/膨胀】", g_dstImage);
}

//--------------------------【on_TopBlackHat（）函数】---------------------------------
//			描述：【顶帽运算/黑帽运算】窗口的回调函数
//-------------------------------------------------------------------------------------
static void on_TopBlackHat(int, void*)
{
	//偏移量的定义
	int offset = g_nTopBlackHatNum - g_nMaxIteratonNum;		//偏移量
	int Absolute_offset = offset > 0 ? offset : -offset;	//偏移量绝对值
	//自定义核
	Mat element = getStructuringElement(g_nElementShape,
		Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset));
	//进行操作
	if (offset < 0)
		morphologyEx(g_srcImage, g_dstImage, MORPH_TOPHAT, element);
	else
		morphologyEx(g_srcImage, g_dstImage, MORPH_BLACKHAT, element);
	//显示图像
	imshow("【顶帽/黑帽】", g_dstImage);
}
