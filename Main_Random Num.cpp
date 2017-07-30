/****************************************************************
* Copyright        : BUPT
* Author           : hx
* Date             : 2017.07.25
* Description      : Random txt
*****************************************************************/

//------------------��ͷ�ļ��������ռ�������֡�------------------
//            ����������������ʹ�õ�ͷ�ļ��������ռ�  
//----------------------------------------------------------------
#include "stdafx.h"
#include "stdafx.h"
#include <Windows.h>
#include <iostream>  
#include <vector>  
#include <algorithm>  
#include <string>  
#include <stdlib.h>  
#include <time.h>  

using namespace std;


//--------------------------------��ȫ�ֱ����������֡�-----------------------------------
//								   ������ȫ�ֱ�������
//-------------------------------------------------------------------------------------
vector<string> lines;
char *inFile = "numTXT.txt";			//�����ȡ�ļ���
char *outFile = "RandNumTXT.txt";		//��������ļ���


//--------------------------------��ȫ�ֺ����������֡�-----------------------------------
//								   ������ȫ�ֺ�������
//---------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
	FILE *p_infile = fopen(inFile, "r");
	if (NULL == p_infile) {
		fprintf(stderr, "open file[%s] failed! ", inFile);
		return -1;
	}

	FILE *p_outfile = fopen(outFile, "w");
	if (NULL == p_outfile) {
		fprintf(stderr, "open file[%s] failed! ", outFile);
		return -1;
	}

	srand(time(0));
	int max_id = 0;
	int temp_id = 0;

	char temp_buf[10000];

	while (fgets(temp_buf, sizeof(temp_buf), p_infile)) {
		sscanf(temp_buf, "%d/t", &temp_id);
		if (temp_id > max_id) {
			max_id = temp_id;
		}

		lines.push_back(temp_buf);

	}

	random_shuffle(lines.begin(), lines.end());

	vector<string>::iterator iter;
	int i = 0;
	for (iter = lines.begin(); iter != lines.end(); iter++) {
		fputs((*iter).c_str(), p_outfile);
	}

	fclose(p_infile);
	fclose(p_outfile);

	return 0;
}