//----------------------------------【程序说明】----------------------------------------
//	程序说明：参考《OpenCV编程入门》配套程序SURF特征点检测
//	程序描述：SURF特征点检测
//	开发测试所用操作系统：	Windows 10 64bit
//	开发测试所用IDE版本：	Visual Stuido 2015
//	开发测试所用Opencv版本：2.4.9
//--------------------------------------------------------------------------------------


//--------------------------【头文件、命名空间包含部分】--------------------------------
//				描述：包含程序的头文件定义和命名空间
//--------------------------------------------------------------------------------------
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <iostream>
using namespace cv;
using namespace std;

//--------------------------------【main()函数】----------------------------------------
//				描述：控制台应用程序的入口函数，程序从这里开始
//--------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//【1】载入素材图
	Mat srcImage1 = imread("srcImage_1.jpg", 1);
	Mat srcImage2 = imread("srcImage_2.jpg", 1);
	if (!srcImage1.data || !srcImage2.data) {
		printf("读取文件错误，请检查是否有原图像！~   /n"); return 233;
	}

	//【2】使用SURF算子检测关键点
	int minHessian = 700;	//SURF算法中的的Hessian阈值
	SurfFeatureDetector detector(minHessian);	//定义一个SurfFeatureDetector(SURF)特征检测类对象
	std::vector<KeyPoint> keyPoint1, keyPoint2;	//vector模板类，存放任意类型的动态数据

	//【3】调用detect函数检测出SURF特征关键点，保存在vector中
	detector.detect(srcImage1, keyPoint1);
	detector.detect(srcImage2, keyPoint2);

	//【4】计算描述符
	SurfDescriptorExtractor extractor;
	Mat descriptors1, descriptors2;
	extractor.compute(srcImage1, keyPoint1, descriptors1);
	extractor.compute(srcImage2, keyPoint2, descriptors2);

	//【5】使用BruteForce进行匹配
	//实例化一个匹配器
	BruteForceMatcher< L2<float> >matcher;
	std::vector <DMatch> matches;
	//匹配两幅图中的描述子（descriptors）
	matcher.match(descriptors1, descriptors2, matches);

	//【6】绘制从两个图像中匹配出的关键点
	Mat imgMatches;
	drawMatches(srcImage1, keyPoint1, srcImage2, keyPoint2, matches, imgMatches);	//进行绘制

	//【7】显示效果图
	namedWindow("匹配图", WINDOW_NORMAL );
	imshow("匹配图", imgMatches);
	waitKey(0);
	return 0;

}



