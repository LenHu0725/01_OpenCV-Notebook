/***************************************************************************************
* Copyright        : BUPT
* Author           : hx
* Date             : 2017.07.30
* Description      : Image to Video
***************************************************************************************/

//------------------------【头文件与命名空间包含部分】----------------------------------
//				描述：包含程序所依赖的头文件和命名空间
//--------------------------------------------------------------------------------------
#include <iostream>  
#include "cv.h"  
#include "highgui.h"  
#include "windows.h"

/*生成不同视频需要修改的变量*/
CvSize size = cvSize(720, 400);  //视频帧格式的大小  
double fps = 3;			//<span style = "white-space:pre">      < / span>//每秒钟的帧率  


//------------------------------【Main()函数】------------------------------------------
//		描述：控制台应用程序的入口函数，我们的程序从这里开始执行
//--------------------------------------------------------------------------------------
void main()
{
	int frameCount = 1;
	
	CvVideoWriter* writer = cvCreateVideoWriter("srcVideo.avi", CV_FOURCC('X', 'V', 'I', 'D'), fps, size); //创建视频文件  
	char cname[20];
	sprintf(cname, "PIC\\%.4d.jpg", frameCount); //加载图片的文件夹，图片的名称编号是1开始1，2,3,4,5.。。。  
	IplImage *src = cvLoadImage(cname);
	if (!src)
	{ return -1; }
	IplImage *src_resize = cvCreateImage(size, 8, 3); //创建视频文件格式大小的图片  
	cvNamedWindow("srcImage");
	while (src)
	{
		cvShowImage("srcImage", src_resize);
		cvWaitKey(1);
		cvResize(src, src_resize);		//<span style = "white-space:pre">    < / span>//将读取的图片设置为视频格式大小相同  
			cvWriteFrame(writer, src_resize); //保存图片为视频流格式  
		cvReleaseImage(&src);			//<span style = "white-space:pre">        < / span> //释放空间  
			frameCount++;
		sprintf(cname, "PIC\\%.4d.jpg", frameCount);
		src = cvLoadImage(cname);       //循环读取数据  
	}
	cvReleaseVideoWriter(&writer);
	cvReleaseImage(&src_resize);

}
