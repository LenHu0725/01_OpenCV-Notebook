/***************************************************************************************
* Copyright        : BUPT
* Author           : hx
* Date             : 2017.07.30
* Description      : Image to Video
***************************************************************************************/

//------------------------��ͷ�ļ��������ռ�������֡�----------------------------------
//				����������������������ͷ�ļ��������ռ�
//--------------------------------------------------------------------------------------
#include <iostream>  
#include "cv.h"  
#include "highgui.h"  
#include "windows.h"

/*���ɲ�ͬ��Ƶ��Ҫ�޸ĵı���*/
CvSize size = cvSize(720, 400);  //��Ƶ֡��ʽ�Ĵ�С  
double fps = 3;			//<span style = "white-space:pre">      < / span>//ÿ���ӵ�֡��  


//------------------------------��Main()������------------------------------------------
//		����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼִ��
//--------------------------------------------------------------------------------------
void main()
{
	int frameCount = 1;
	
	CvVideoWriter* writer = cvCreateVideoWriter("srcVideo.avi", CV_FOURCC('X', 'V', 'I', 'D'), fps, size); //������Ƶ�ļ�  
	char cname[20];
	sprintf(cname, "PIC\\%.4d.jpg", frameCount); //����ͼƬ���ļ��У�ͼƬ�����Ʊ����1��ʼ1��2,3,4,5.������  
	IplImage *src = cvLoadImage(cname);
	if (!src)
	{
		return;
	}
	IplImage *src_resize = cvCreateImage(size, 8, 3); //������Ƶ�ļ���ʽ��С��ͼƬ  
	cvNamedWindow("srcImage");
	while (src)
	{
		cvShowImage("srcImage", src_resize);
		cvWaitKey(1);
		cvResize(src, src_resize);		//<span style = "white-space:pre">    < / span>//����ȡ��ͼƬ����Ϊ��Ƶ��ʽ��С��ͬ  
			cvWriteFrame(writer, src_resize); //����ͼƬΪ��Ƶ����ʽ  
		cvReleaseImage(&src);			//<span style = "white-space:pre">        < / span> //�ͷſռ�  
			frameCount++;
		sprintf(cname, "PIC\\%.4d.jpg", frameCount);
		src = cvLoadImage(cname);       //ѭ����ȡ����  
	}
	cvReleaseVideoWriter(&writer);
	cvReleaseImage(&src_resize);

}