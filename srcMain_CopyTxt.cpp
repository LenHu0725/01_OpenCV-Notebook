/*************************************************************************************
 * Name		: TxT Data Pack Patch
 * Date		: 2017.7.7  
 * Describe	: ��ifstream�ж�ȡ�������ݣ�����StartNumλΪ��ʼλ��������ݰ��ض���ʽ���
 *			  ��Ǹ�ʽΪ   ......./ Patch .bmp Patch
 *
**************************************************************************************/

/**************������ͷ�ļ���***************/
#include "stdafx.h"
#include <fstream>  
#include <string>  
#include <iostream>  

/**************���궨�塿****************/
#define StartNum 53			// �����ַ���ʼλ��

/************�����������ռ䡿************/
using namespace std;

/**************����������****************/
int main()
{
	ifstream in("RandNumTXT.txt");
	ofstream out("Result Num.txt");
	string filename;
	string line;

	if (in) // �и��ļ�  
	{
		while (getline(in, line)) // line�в�����ÿ�еĻ��з�  
		{

			// ���Ʋ����Txt�ļ�
			cout << line << " " << line[StartNum] << endl;
			out << line << endl;
			out << line[StartNum] << endl; // ���뵽Result Num.txt��  
		}
	}
	else // û�и��ļ�  
	{
		cout << "no such file" << endl;
	}

	return 0;
}