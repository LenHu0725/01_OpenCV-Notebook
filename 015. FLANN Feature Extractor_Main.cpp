//----------------------------------【程序说明】----------------------------------------
//		程序说明：参考《OpenCV编程入门》配套程序SURF特征点检测
//		程序描述：FLANN特征点检测
//		开发测试所用操作系统：	Windows 10 64bit
//		开发测试所用IDE版本：	Visual Stuido 2015
//		开发测试所用Opencv版本：2.4.9
//--------------------------------------------------------------------------------------

//--------------------------【头文件、命名空间包含部分】--------------------------------
//				描述：包含程序的头文件定义和命名空间
//--------------------------------------------------------------------------------------
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <iostream>
using namespace cv;
using namespace std;

//--------------------------------【main()函数】----------------------------------------
//				描述：控制台应用程序的入口函数，程序从这里开始
//--------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//【1】读取所需图片文件
	Mat img_1 = imread("srcImage_1.jpg", 1);
	Mat img_2 = imread("srcImage_2.jpg", 1);
	if (!img_1.data || !img_2.data)
	{
		printf("图片读取错误，请验证根目录下是否有图片文件！~	/n"); return 233;
	}

	//【2】利用SURF检测器检测的关键点
	int minHessian = 300;
	SURF detector(minHessian);
	std::vector<KeyPoint> keypoints_1, keypoints_2;
	detector.detect(img_1, keypoints_1);
	detector.detect(img_2, keypoints_2);

	//【3】计算描述符(特征向量)
	SURF extractor;
	Mat descriptors_1, descriptors_2;
	extractor.compute(img_1, keypoints_1, descriptors_1);
	extractor.compute(img_2, keypoints_2, descriptors_2);

	//【4】采用FLANN算法匹配描述符向量
	FlannBasedMatcher matcher;
	std::vector<DMatch> matches;
	matcher.match(descriptors_1, descriptors_2, matches);
	double max_dist = 0; double min_dist = 100;

	//【5】快速计算关键点之间的最大和最小的距离
	for (int i = 0; i < descriptors_1.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist)	min_dist = dist;
		if (dist > max_dist)	max_dist = dist;
	}
	//输出距离信息
	printf(">最大距离（Max dist）：%f \n", max_dist);
	printf(">最小距离（Min dist）：%f \n", max_dist);

	//【6】存下符合条件的匹配结果（即其距离小于2*min_dist的），使用radiusMatch同样可行
	std::vector<DMatch> good_matches;
	for (int i = 0; i < descriptors_1.rows; i++)
	{
		if (matches[i].distance < 2 * min_dist)
			good_matches.push_back(matches[i]);
	}

	//【7】会指出符合条件的匹配点
	Mat img_matches;
	drawMatches(img_1, keypoints_1, img_2, keypoints_2,
		good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
		vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	//【8】输出相关匹配点信息
	for (int i = 0; i < (int)good_matches.size(); i++)
		printf(">负荷条件的匹配点[%d]特征点1：%d -- 特征点2：%d \n", i, good_matches[i].queryIdx, good_matches[i].trainIdx);

	//【9】显示效果图
	namedWindow("匹配效果图", WINDOW_NORMAL);
	imshow("匹配效果图", img_matches);

	//按任意键退出程序
	waitKey(0);
	return 0;

}

