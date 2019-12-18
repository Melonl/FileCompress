/**
����ѹ���ļ� 
*/
#ifndef GLOBALVARIABLE_HEAD
#define GLOBALVARIABLE_HEAD
#include "globalvariable.h"
#include <cstring>
#include <string>
#endif

#include <cmath>

#ifndef HAFFMANTREE_HEAD
#define HAFFMANTREE_HEAD
#include "haffmantree.cpp"
#endif

#ifndef IOSTREAM_HEAD
#define IOSTREAM_HEAD
#include <iostream>
#include <cstring>
using namespace std;
#endif

void getFileNameFromPath(char *prefix_filename, char *suffix_filename, const char *filepath_name)
{ //���������ļ�·���£�������ļ����ļ�ǰ׺���ͺ�����
	int lastSplit = -1;
	// lastSplitָ������һ�� '/'��'\'����
	char file_name[128]; //ǰ׺��.��׺��
	for (int i = 0; i < strlen(filepath_name); i++)
	{
		if (filepath_name[i] == '/' || filepath_name[i] == '\\')
		{
			lastSplit = i;
		}
	}
	strcpy(file_name, filepath_name + lastSplit + 1); // ȥ��·����ֻʣ���ļ���
	lastSplit = -1;
	//lastSplitָ�����һ��'.'����
	for (int i = 0; i < strlen(file_name); i++)
	{
		if (file_name[i] == '.')
		{
			lastSplit = i;
		}
	}
	strcpy(suffix_filename, file_name + lastSplit + 1);									  // ȡ��׺��
	strncpy(prefix_filename, file_name, strlen(file_name) - strlen(suffix_filename) - 1); //ȡǰ׺��
}

char *getByteEncode(unsigned char c)
{ //�����ַ�c�Ĺ���������
	for (int j = 0; j < bytes_count; j++)
	{
		if (HaffTree[j].byte == c)
		{
			return HaffTree[j].code;
		}
	}
	return NULL;
}

// �ѻ������У������ܶ���ֽڣ�д���ļ���
void flushBuffer(FILE *fp)
{
	strcpy(buff_string, "");

	unsigned char tempchar = 0;
	int byte_num = strlen(buff) / 8; //����д��byte_num���ֽ�
	int i;

	for (i = 0; i < byte_num; i++)
	{ //������8λ�������i���ֽ�
		tempchar = 0;
		for (int j = 0; j < 8; j++)
		{

			if (buff[i * 8 + j] == '1')
				tempchar += pow(2, 7 - j);
		}
		// cout<<"tempchar= "<<(int)tempchar<<endl;

		buff_string[i] = tempchar;
	}
	buff_string[i] = '\0';
	fwrite(buff_string, 1, byte_num, fp); //����д���ļ���
	strcpy(buff, buff + byte_num * 8);	//��buff����д���ļ��Ĳ��ּ�����
}

void writeCompressFile()
{ //����ѹ���ļ�
	//  cout<<"����ѹ���ļ����������׺��Ϊ.buf"<<endl;
	//	cin>> compress_filename;
	//��ѹ���ļ�
	//  strcat(compress_filename,".buf");//ѹ���ļ��� ��׺��Ϊbuf


	FILE *ofp = fopen(compress_filename, "wb");
	if (ofp == NULL)
	{ //�ж��ļ��Ƿ����
		cout << compress_filename << "�ļ������ڻ�ռ��!\r\n";
		exit(4);
	}

	//���ļ�ͷ����Ϣд���ļ� :�ļ����ͳ��ȣ�char�����ļ�����(char [SUFFIXNAMEMAX] )���ļ�����(long long)��������Ľ����(int)���ֽ�b1��Ȩ��w1���ֽ�b2��Ȩ��b2�����������ֽ�bn,Ȩ��wn
	fprintf(ofp, "%d,", strlen(suffix_filename));
	fprintf(ofp, "%s,", suffix_filename);
	fprintf(ofp, "%lld,", file_length);
	fprintf(ofp, "%d,", bytes_count);
	//д����ֽڵ�Ƶ�ȣ���ѹʱ���ɸ��ݸ�Ƶ��ֵ����ԭ����������
	for (int i = 0; i < bytes_count; i++)
	{
		fprintf(ofp, "%c,", HaffTree[i].byte);
		fprintf(ofp, "%lld,", HaffTree[i].weight);
	}

	//����buff����������Դ�ļ��ĸ����ֽڣ�����ת�롣
	FILE *ifp = fopen(source_filename, "rb");
	unsigned char c;
	if (ifp == NULL)
	{ //�ж��ļ��Ƿ����
		cout << source_filename << "�ļ������ڻ�ռ��!\r\n";
		exit(4);
	}

	strcpy(buff, "");  //��չ��������뻺����
	c = fgetc(ifp);	//���ļ��ж�ȡһ���ֽڵ� c
	while (!feof(ifp)) //�ļ�û����
	{
		if (BUFF_MAXSIZE - strlen(buff) > 256)
		{ //�����������ʣ���λ�ó���256������������ٷ���һ���ַ�
			strcat(buff, getByteEncode(c));
			c = fgetc(ifp); //���ļ��ж�ȡһ���ֽڵ� c
		}
		else
		{ //��������Ҫ���ˣ��Ȱѻ������н����ܶ������д���ļ��С�
			flushBuffer(ofp);
			//  cout<<"��һ��"<<endl;
		}
		//	       c=fgetc(ifp); //������д��һ���ֽ�
	}
	// �ѻ�������ʣ����ַ�д���ļ�

	flushBuffer(ofp);
	//    cout<<"�ڶ���"<<endl;

	//���һ���ַ�δ����
	if (strlen(buff) > 0)
	{

		strcat(buff, "0000000");
		// cout<<"��0֮�� buff="<<buff<<endl;
		flushBuffer(ofp);
		strcpy(buff, "");
	}
	fclose(ofp);
	fclose(ifp);
}

void compressFile()
{
	getFileNameFromPath(prefix_filename, suffix_filename, source_filename);
	initHaffTree();
	Statistics(source_filename); //ͳ�Ƹ��ֽڳ��ֵĴ���
	sortweights(HaffTree, 256);
	creatHaffTree();
	creatHaffCode();
	printtree(511);
	writeCompressFile();
}
/*
int  main(){	

   compressFile()  ; 
   return 0; 
}
*/
