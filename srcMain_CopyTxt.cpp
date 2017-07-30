/*************************************************************************************
 * Name		: TxT Data Pack Patch
 * Date		: 2017.7.7  
 * Describe	: 从ifstream中读取各行数据，再由StartNum位为起始位将标记数据按特定格式标记
 *			  标记格式为   ......./ Patch .bmp Patch
 *
**************************************************************************************/

/**************【包含头文件】***************/
#include "stdafx.h"
#include <fstream>  
#include <string>  
#include <iostream>  

/**************【宏定义】****************/
#define StartNum 53			// 定义字符开始位数

/************【引用命名空间】************/
using namespace std;

/**************【主函数】****************/
int main()
{
	ifstream in("RandNumTXT.txt");
	ofstream out("Result Num.txt");
	string filename;
	string line;

	if (in) // 有该文件  
	{
		while (getline(in, line)) // line中不包括每行的换行符  
		{

			// 复制并输出Txt文件
			cout << line << " " << line[StartNum] << endl;
			out << line << endl;
			out << line[StartNum] << endl; // 输入到Result Num.txt中  
		}
	}
	else // 没有该文件  
	{
		cout << "no such file" << endl;
	}

	return 0;
}