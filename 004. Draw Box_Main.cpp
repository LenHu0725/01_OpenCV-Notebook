/***************************************************************************************
 * Copyright        : BUPT
 * Author           : hx
 * Date             : 2017.07.21
 * Description      : 鼠标绘制矩形框
***************************************************************************************/

//------------------------------------【函数声明】--------------------------------------
//				描述：用鼠标画出矩形框
//--------------------------------------------------------------------------------------

#include <opencv2/opencv.hpp>

using namespace cv;

#define WINDOW_NAME "【程序窗口】"		//为窗口标题定义宏

//---------------------------------【全局函数声明】-------------------------------------
//				描述：全局函数声明
//--------------------------------------------------------------------------------------
void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle( cv::Mat& img,cv::Rect box );
void ShowHelpText();

//--------------------------------【全局变量声明部分】----------------------------------
//				描述：全局变量声明
//--------------------------------------------------------------------------------------
Rect	g_rectangle;
bool	g_bDrawingBox = false;	//是否进行绘制
RNG	g_rng(12345);

//--------------------------------【main()函数】----------------------------------
//				描述：全主函数从这里开始
//--------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//【1】准备参数
	g_rectangle = Rect(-1, -1, 0, 0);
	Mat srcImage(600, 800, CV_8UC3),tempImage;
	srcImage.copyTo(tempImage);
	g_rectangle = Rect(-1, -1, 0, 0);
	srcImage = Scalar::all(0);

	//【2】设置鼠标操作回调函数
	namedWindow(WINDOW_NAME);
	setMouseCallback(WINDOW_NAME,on_MouseHandle,(void*)&srcImage);

	//【3】程序主循环，当进行绘制的标识符为真时，进行绘制
	while (1)
	{
		srcImage.copyTo(tempImage);		//复制源图到临时变量
		if (g_bDrawingBox) DrawRectangle(tempImage, g_rectangle);	//当进行绘制的标识符为真，则进行绘制
		imshow( WINDOW_NAME, tempImage );
		if (waitKey(10) == 27) break;	//按下ESC键，程序退出
	}
	return 0;
}

//----------------------------【on_MouseHandle()函数】----------------------------------
//		描述：鼠标回调函数，根据不同的鼠标事件进行不同的操作
//--------------------------------------------------------------------------------------
void on_MouseHandle(int event, int x, int y, int flags, void* param)
{
	Mat& image = *(cv::Mat*) param;
	switch ( event)
	{
		
		//鼠标移动消息
	case EVENT_MOUSEMOVE:
	  {
		if (g_bDrawingBox)	//如果是否进行绘制的标识符为真，则记录下长宽到RECT型变量中
		{
			g_rectangle.width  = x - g_rectangle.x;
			g_rectangle.height = y - g_rectangle.y;
		}
	  }
		break;

		//左键按下消息
	case EVENT_LBUTTONDOWN:
	  {
		g_bDrawingBox = true;
		g_rectangle = Rect(x,y,0,0);	//记录起始点
	  }
	  break;

	  //左键抬起消息
	case EVENT_LBUTTONUP:
	  {
		g_bDrawingBox = false;	//置标识符为false
		//对宽和高小于0的处理
		if ( g_rectangle.width < 0 )
		{
			g_rectangle.x += g_rectangle.width;
			g_rectangle.width *= -1;
		}

		if (g_rectangle.height < 0 )
		{
			g_rectangle.y += g_rectangle.height;
			g_rectangle.height *= -1;
		}
		//调用函数进行绘制
		DrawRectangle( image, g_rectangle );
	  }
	  break;

	}

}

//---------------------------【DrawRectangle()函数】------------------------------------
//			描述：自定义的矩形绘制函数
//--------------------------------------------------------------------------------------
void DrawRectangle(cv::Mat& img, cv::Rect box)
{
	rectangle(img, box.tl(), box.br(), Scalar(g_rng.uniform(0, 255),
		g_rng.uniform(0, 255), g_rng.uniform(0, 255)));//随机颜色
}