/**
生成压缩文件 
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
{ //在完整的文件路径下，剥离出文件的文件前缀名和后罪名
	int lastSplit = -1;
	// lastSplit指向最右一个 '/'或'\'符号
	char file_name[128]; //前缀名.后缀名
	for (int i = 0; i < strlen(filepath_name); i++)
	{
		if (filepath_name[i] == '/' || filepath_name[i] == '\\')
		{
			lastSplit = i;
		}
	}
	strcpy(file_name, filepath_name + lastSplit + 1); // 去除路径，只剩下文件名
	lastSplit = -1;
	//lastSplit指向最后一个'.'符号
	for (int i = 0; i < strlen(file_name); i++)
	{
		if (file_name[i] == '.')
		{
			lastSplit = i;
		}
	}
	strcpy(suffix_filename, file_name + lastSplit + 1);									  // 取后缀名
	strncpy(prefix_filename, file_name, strlen(file_name) - strlen(suffix_filename) - 1); //取前缀名
}

char *getByteEncode(unsigned char c)
{ //查找字符c的哈夫曼编码
	for (int j = 0; j < bytes_count; j++)
	{
		if (HaffTree[j].byte == c)
		{
			return HaffTree[j].code;
		}
	}
	return NULL;
}

// 把缓冲区中，尽可能多的字节，写入文件中
void flushBuffer(FILE *fp)
{
	strcpy(buff_string, "");

	unsigned char tempchar = 0;
	int byte_num = strlen(buff) / 8; //可以写入byte_num个字节
	int i;

	for (i = 0; i < byte_num; i++)
	{ //连续读8位，构造第i个字节
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
	fwrite(buff_string, 1, byte_num, fp); //批量写入文件；
	strcpy(buff, buff + byte_num * 8);	//把buff中已写入文件的部分剪掉；
}

void writeCompressFile()
{ //生成压缩文件
	//  cout<<"输入压缩文件名（建议后缀名为.buf"<<endl;
	//	cin>> compress_filename;
	//打开压缩文件
	//  strcat(compress_filename,".buf");//压缩文件的 后缀名为buf


	FILE *ofp = fopen(compress_filename, "wb");
	if (ofp == NULL)
	{ //判断文件是否存在
		cout << compress_filename << "文件不存在或被占用!\r\n";
		exit(4);
	}

	//把文件头部信息写入文件 :文件类型长度（char），文件类型(char [SUFFIXNAMEMAX] )，文件长度(long long)，被编码的结点数(int)，字节b1，权重w1，字节b2，权重b2，。。。。字节bn,权重wn
	fprintf(ofp, "%d,", strlen(suffix_filename));
	fprintf(ofp, "%s,", suffix_filename);
	fprintf(ofp, "%lld,", file_length);
	fprintf(ofp, "%d,", bytes_count);
	//写入个字节的频度，解压时，可根据该频度值，还原哈夫曼编码
	for (int i = 0; i < bytes_count; i++)
	{
		fprintf(ofp, "%c,", HaffTree[i].byte);
		fprintf(ofp, "%lld,", HaffTree[i].weight);
	}

	//利用buff缓冲区，把源文件的各个字节，进行转码。
	FILE *ifp = fopen(source_filename, "rb");
	unsigned char c;
	if (ifp == NULL)
	{ //判断文件是否存在
		cout << source_filename << "文件不存在或被占用!\r\n";
		exit(4);
	}

	strcpy(buff, "");  //清空哈夫曼编码缓冲区
	c = fgetc(ifp);	//从文件中读取一个字节到 c
	while (!feof(ifp)) //文件没结束
	{
		if (BUFF_MAXSIZE - strlen(buff) > 256)
		{ //如果缓冲区中剩余的位置超过256，则可以至少再放入一个字符
			strcat(buff, getByteEncode(c));
			c = fgetc(ifp); //从文件中读取一个字节到 c
		}
		else
		{ //缓冲区快要满了，先把缓冲区中仅可能多的内容写入文件中。
			flushBuffer(ofp);
			//  cout<<"第一处"<<endl;
		}
		//	       c=fgetc(ifp); //错误，少写入一个字节
	}
	// 把缓冲区中剩余的字符写入文件

	flushBuffer(ofp);
	//    cout<<"第二处"<<endl;

	//最后一个字符未处理
	if (strlen(buff) > 0)
	{

		strcat(buff, "0000000");
		// cout<<"补0之后 buff="<<buff<<endl;
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
	Statistics(source_filename); //统计个字节出现的次数
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
