/*****************************************************************************************
 * Copyright        : BUPT
 * Author           : hx
 * Date             : 2017.07.25
 * Description      : Read and write XML
******************************************************************************************/

//-----------------------【头文件、命名空间包含部分】--------------------------------
//		    描述：包含程序所使用的头文件和命名空间
//-----------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <time.h>

using namespace cv;


//--------------------------------【main()函数】--------------------------------------
//				描述：全主函数从这里开始
//------------------------------------------------------------------------------------
int main( int argc, char** argv )
{
	//初始化
	FileStorage Text("test.xml", FileStorage::WRITE);

	//开始文件写入
	Text << "frameCount" << 5;
	time_t rawtime; time(&rawtime);
	Text << "calibrationDate" << asctime(localtime(&rawtime));
	Mat cameraMatrix = (Mat_<double>(3, 3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);
	Mat distCoeffs = (Mat_<double>(5, 1) << 0.1, 0.01, -0.001, 0, 0);
	Text << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;
	Text << "features" << "[";
	for (int i = 0; i < 3; i++)
	{
		int x = rand() % 640;
		int y = rand() % 480;
		uchar lbp = rand() % 256;
		Text << "{:" << "x" << x << "y" << y << "lbp" << "[:";
		for (int j = 0; j < 8; j++)
			Text << ((lbp >> j) & 1);
		Text << "]" << "}";
	}
	Text << "]";
	Text.release();

	//文件遇到No element name has been given的提示需注意以下几点
	//vector元素要注意在第一个元素前加上“[”，在最后一个元素前加上"]"
	//对于map结构的操作使用的符号是"{"和"}"
	//http://blog.csdn.net/yang_xian521/article/details/6897684
	printf("文件读取完毕，请在工程目录下查看生成文件~");
	getchar();

	return 0;
}
