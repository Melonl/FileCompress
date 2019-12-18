/**
解压文件 
*/
#ifndef GLOBALVARIABLE_HEAD
#define GLOBALVARIABLE_HEAD
#include "globalvariable.h"
#endif

#ifndef COUNT_HEAD
#define COUNT_HEAD
using namespace std;
#endif

#ifndef HAFFMANTREE_HEAD
#define HAFFMANTREE_HEAD
#include "haffmantree.cpp"
using namespace std;
#endif

#ifndef IOSTREAM_HEAD
#define IOSTREAM_HEAD
#include <iostream>
#include <cstring>
using namespace std;
#endif
void deCompressFile()
{   //解压文件件
	// cout<<"输入压缩文件名（建议后缀名为.buf"<<endl;
	// cin>> compress_filename;
	//打开压缩文件
	FILE *ifp = fopen(compress_filename, "rb");
	if (ifp == NULL) //判断文件是否存在
	{
		cout << compress_filename << "压缩文件不存在或被占用!\r\n";
		exit(4);
	}

	// 开始读文件头部
	//文件类型长度（char），文件类型(char [SUFFIXNAMEMAX] )，文件长度(long long)，被编码的结点数(int)，字节b1，权重w1，字节b2，权重b2，。。。。字节bn,权重wn
	int suffix_filename_len;
	fscanf(ifp, "%d,", &suffix_filename_len);			 //读源文件的后缀名
	fread(suffix_filename, 1, suffix_filename_len, ifp); //把源文件的后缀名写入压缩文件（解压时还原源文件的类型）
	fscanf(ifp, ",%ld,", &file_length);					 //写入源文件的总字节数
	fscanf(ifp, "%d,", &bytes_count);					 //写入源文件中被编码的字节总数 （小于256）

	initHaffTree(); //初始化哈夫曼树存储结构

	//读出字节频度，再还原哈夫曼树
	for (int i = 0; i < bytes_count; i++)
	{
		fscanf(ifp, "%c,", &HaffTree[i].byte);
		fscanf(ifp, "%lld,", &HaffTree[i].weight);
	}
	char tempc;

	creatHaffTree(); //构造哈夫曼树
	printtree(511);

	//  开始读出正文，并进行解码
	//初始化所有全局变量
	int buff_current = 0;			// 缓冲区游标0~BUFF_MAXSIZE
	int byte_current = 0;			// 字节游标 0~7;
	int root = bytes_count * 2 - 2; //根结点
	int tree_current = root;		//树结点游标
	int block_current = 0;
	strcpy(buff, "");  //清空读缓冲区
	strcpy(block, ""); //清空写缓冲区
	char c;
	int test;

	//打开解压文件，准备写入
	strcat(decompress_filename, ".");
	strcat(decompress_filename, suffix_filename);
	FILE *ofp = fopen(decompress_filename, "wb");
	if (ofp == NULL)
	{ //判断文件是否存在
		cout << decompress_filename << "解压文件不存在或被占用!\r\n";
		exit(4);
	}

	fread(buff, 1, BUFF_MAXSIZE - 1, ifp); //装满缓冲区
	cout << buff;

	int refile_length = 0; //已被解压出来的字节总数

	while (refile_length < file_length) //文件没结束
	{
		if (block_current > BLOCK_MAXSIZE - 1)
		{										  //缓冲区已满，先写入文件
			fwrite(block, 1, block_current, ofp); //  此处有问题
			block_current = 0;
		}

		if (HaffTree[tree_current].leftChild == -1)
		{ //叶子节点，则查出该节点，并把该字节写入解压文件中
			c = HaffTree[tree_current].byte;
			block[block_current] = c;
			block_current++;
			block[block_current] = '\0';

			//strcat(block,);
			tree_current = root; //游标回到根结点
			refile_length++;	 //被解压字节数加1
		}
		else
		{ //度缓冲区内的下一位，若是0，则转向左孩子，若是1，则转向右孩子

			if ((buff[buff_current] >> (7 - byte_current)) & 1 == 1)
				tree_current = HaffTree[tree_current].rightChild;
			else
				tree_current = HaffTree[tree_current].leftChild;
			
			if (byte_current < 7)
			{ //在一个字节之内，buff_current不变，byte_current加1
				byte_current++;
			}
			else
			{ //一个字节刚结束，需要知道下一个字节
				byte_current = 0;
				buff_current++;
				if (buff_current >= BUFF_MAXSIZE - 1)
				{ //缓冲区的结点已经读完了，读入下一批

					fread(buff, 1, BUFF_MAXSIZE - 1, ifp); //装满缓冲区
					buff_current = 0;
				}
			}
		}
	}
	fwrite(block, 1, block_current, ofp); //缓冲区中剩余的字符
	fclose(ifp);
	fclose(ofp);
}

/*
int  main(){	
  deCompressFile();    
  return 0; 
}
*/
