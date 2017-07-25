
/***************************************************************************************
* Copyright        : BUPT
* Author           : hx
* Date             : 2017.07.25
* Description      : �����ƾ��ο�
***************************************************************************************/

//--------------------------------��main()������----------------------------------------
//				������ȫ�����������￪ʼ
//-------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <time.h>

using namespace cv;
using namespace std;


//--------------------------------��main()������----------------------------------------
//				������ȫ�����������￪ʼ
//-------------------------------------------------------------------------------------
int main( int argc, char** argv )
{
	//�ı�console������ɫ
	system("color 2F");

	//��ʼ��
	FileStorage fs2("test.xml", FileStorage::READ);

	//��һ�ַ�������FileNode����
	int frameCount = (int)fs2["frameCount"];

	std::string date;
	//�ڶ��ַ�����ʹ��FileNode�����>>
	fs2["calibrationgDate"] >> date;

	Mat cameraMatrix2, distCoeffs2;
	fs2["cameraMatrix"] >> cameraMatrix2;
	fs2["distCoeffs"] >> distCoeffs2;

	cout << "frameCount:" << frameCount << endl
		<< "calibration date:" << date << endl
		<< "camera matrix:" << cameraMatrix2 << endl
		<< "distortion coeffs:" << distCoeffs2 << endl;

	FileNode features = fs2[ "features" ];
	FileNodeIterator it = features.begin(), it_end = features.end();
	int idx = 0;
	std::vector<uchar> lbpval;

	//ʹ��FileNodeIterator��������
	for (; it != it_end; ++it, idx++)
	{
		cout << "feature #" << idx << ":";
		cout << "x=" << (int)(*it)["x"] << ",y=" << (int)(*it)["y"] << ",lbp:(";
		//����Ҳ����ʹ��filenode>>std::vector�������������׵ض���ֵ����
		(*it)["lbp"] >> lbpval;
		for (int i = 0; i < (int)lbpval.size(); i++)
			cout << "" << (int)lbpval[i];
			cout << ")" << endl;
	}
	fs2.release();

	//������������һЩ��������
	printf("\n�ļ���ȡ��ϣ��������������������~");
	getchar();

	return 0;
}