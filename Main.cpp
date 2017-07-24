/***************************************************************************************
 * Copyright        : BUPT
 * Author           : hx
 * Date             : 2017.07.23
 * Description      : Show Shape
****************************************************************************************/

//-----------------------------【头文件、命名空间包含部分】-----------------------------
//						描述：包含程序所使用的头文件和命名空间
//--------------------------------------------------------------------------------------
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//---------------------------------【宏定义部分】---------------------------------------
//								  描述:定义辅助宏
//--------------------------------------------------------------------------------------
#define WINDOW_WIDTH 600				//定义窗口大小的宏


//----------------------------------【main()函数】--------------------------------------
//				描述：控制台应用程序入口函数，我们的程序从这里开始执行
//--------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//定义图像图像尺寸大小
	CvSize sz;				//定义图像尺寸
	sz.height = WINDOW_WIDTH;
	sz.width = WINDOW_WIDTH;

	CvPoint centerpoint;	//定义图像原点
	centerpoint.x = WINDOW_WIDTH / 2;
	centerpoint.y = WINDOW_WIDTH / 2;

	CvSize ellsize;			//椭圆长度，长轴短轴
	ellsize.width = WINDOW_WIDTH / 4;
	ellsize.height = WINDOW_WIDTH / 16;

	//记录起始时间
	double time0 = static_cast<double>(getTickCount());

	//可以使用 Mat mtx(atomImage)	转换IplImage 为 Mat
	IplImage *atomImage = cvCreateImage( sz, IPL_DEPTH_8U,3 );

	//矩形同时可以使用Rect( x, y, width, height );
	cvEllipse(atomImage, centerpoint, ellsize, 0, 0, 365, cvScalar(42, 68, 212), 2, 8, 0);

	//计算运行时间并输出
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "此方法运行时间为： " << time0 << "秒" << endl;		//输出运行时间 若有错误提示加上using namespace std
	
	cvShowImage("显示图像", atomImage);

	waitKey(0);

}
