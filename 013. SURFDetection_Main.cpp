//----------------------------------【程序说明】----------------------------------------
//	程序说明：参考《OpenCV编程入门》配套程序SURF检测
//	程序描述：SURF特征点检测
//	开发测试所用操作系统：	Windows 10 64bit
//	开发测试所用IDE版本：	Visual Stuido 2015
//	开发测试所用Opencv版本：3.2.0
//--------------------------------------------------------------------------------------

//----------------------------【头文件、命名空间包含部分】------------------------------
//			描述：包含程序所依赖的头文件和命名空间
//--------------------------------------------------------------------------------------
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

//--------------------------------【main()函数】----------------------------------------
//		描述：控制台应用程序的入口函数，程序从这里开始
//--------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//【0】改变console的颜色与帮助字体
	system("color 27");
	//ShowHelpText();
	
	//【1】载入源图像并显示
	Mat srcImage1 = imread("MatchTemplate_Img.jpg", 1);
	Mat srcImage2 = imread("MatchTemplate_Temple2.jpg", 2);
	if (!srcImage1.data || !srcImage2.data)	//检测是否读取成功
	{
		printf("原图片读取错误，请确定根目录下是否存在之名图片~！"); return false;
	}

	imshow("原始图1", srcImage1);
	imshow("原始图2", srcImage2);

	//【2】定义需要用到的变量和类
	int minHessian = 400;//定义SURF中的hessian阈值特征点检测算子
	//在库中：typedef SURF SurfFeatureDetector;   typedef SURF SurfDescriptorExtractor;所以三者是等价的（别名） 
	SURF detector(minHessian);//定义一个SurfFeatureDetector(SURF)特征检测类对象
	std::vector<KeyPoint> keypoints_1, keypoints_2;
		//vector模板类是能够存放任意类型的动态数组，能够存放任意类型的动态数组，能够增加和压缩数据

	//【3】调用detect函数检测出SURF特征关键点，保存在vector容器中
	detector.detect(srcImage1, keypoints_1);
	detector.detect(srcImage2, keypoints_2);

	//【4】绘制特征关键点
	Mat img_keypoints_1; Mat img_keypoints_2;
	drawKeypoints(srcImage1, keypoints_1, img_keypoints_1,
		Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(srcImage2, keypoints_2, img_keypoints_2,
		Scalar::all(-1), DrawMatchesFlags::DEFAULT);

	//【5】显示效果图
	imshow("特征点检测效果图1", img_keypoints_1);
	imshow("特征点检测效果图2", img_keypoints_2);

	waitKey(0);
	return 0;
}
