/**
构造已知文件字节的频度，构造哈夫曼树 
*/

#ifndef IOSTREAM_HEAD
#define IOSTREAM_HEAD
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
#endif

#ifndef GLOBALVARIABLE_HEAD
#define GLOBALVARIABLE_HEAD
#include "globalvariable.h"
#endif

void initHaffTree();								//初始化哈夫曼树哈夫曼编码存储结构
void Statistics(char fileName[]);						//统计文件各字节的频度
void sortweights(HaffNode HaffTree[], int bytes_count); //按字节出现的频度进行降序排序

void initHaffTree()
{
	for (int i = 0; i < 511; i++)
	{
		HaffTree[i].weight = 0;
		HaffTree[i].byte = i;
		HaffTree[i].parent = -1;
		HaffTree[i].leftChild = -1;
		HaffTree[i].rightChild = -1;
		strcpy(HaffTree[i].code, "");
	}
	return;
}
void Statistics(char fileName[])
{
	//初始化权值记录函数
	//打开文件
	FILE *ifp = fopen(fileName, "rb");
	if (ifp == NULL) //判断文件是否存在
	{
		cout << fileName << "文件不存在或被占用!\r\n";
		exit(4);
	}
	unsigned char c;	  //接收读取的每个字节
	file_length = 0;	  //保存文件的字节数，初始为０
	fread(&c, 1, 1, ifp); //从文件中读取一个字节到 c
	while (!feof(ifp))	//文件没结束
	{
		HaffTree[c].weight++;
		file_length++;		  //字符出现原文件长度+1
		fread(&c, 1, 1, ifp); //从文件中读取一个字节到 c
	}
	//	cout<< "完成以字节为单位的权值统计\r\n" ;

	fclose(ifp);

	// 统计一下权值大于0的结点个数
	bytes_count = 0;
	for (int i = 0; i < 256; i++)
	{
		if (HaffTree[i].weight > 0)
			bytes_count++;
	}

	return;
}

bool compare(HaffNode a, HaffNode b)
{
	return a.weight > b.weight; //降序
}

void sortweights(HaffNode HaffTree[], int bytescount = 256)
{
	sort(HaffTree, HaffTree + bytescount - 1, compare);
}

void creatHaffTree()
{
	///	initHaffTree( );
	//	cout<<"哈夫曼中叶子结点的个数为"<<bytes_count<<endl;
	int min1 = 0, min2 = 1;	//weight值最小的两个子树的根结点位置
	int current = bytes_count; //合并树的根结点存储位置

	for (int i = 1; i < bytes_count; i++)
	{ //经过bytes_count -1 次树的合并。
		//找出 min1 和min2
		min1 = current - 1;
		for (int j = current - 1; j >= 0; j--)
		{
			if (HaffTree[j].parent == -1 && HaffTree[j].weight <= HaffTree[min1].weight)
				min1 = j;
		}
		min2 = -1;
		for (int j = current - 1; j >= 0; j--)
		{
			if (min2 == -1)
			{											   //min2 未初始化
				if (HaffTree[j].parent == -1 && j != min1) //初始化min2 ，避开min1
					min2 = j;
			}
			else
			{ //min2已经被始化
				if (j != min1 && HaffTree[j].parent == -1 && HaffTree[j].weight <= HaffTree[min2].weight)
					min2 = j;
			}
		}
		// 把min1 和min2 两个位置上的子树进行合并；
		HaffTree[current].weight = HaffTree[min1].weight + HaffTree[min2].weight;
		HaffTree[current].leftChild = min1;
		HaffTree[current].rightChild = min2;
		HaffTree[min1].parent = current;
		HaffTree[min2].parent = current;
		current++;
	}
}
void creatHaffCode()
{
	int root = bytes_count * 2 - 2; //正确
	HaffTree[root].code[0] = '\0';
	//	cout<<"根结点的编码"<<HaffTree[root].code <<endl;
	for (int i = root - 1; i >= 0; i--)
	{
		//cout<<"第"<<i<<"个结点的编码原编码是"<<HaffTree[HaffTree[i].parent].code <<endl;

		strcpy(HaffTree[i].code, HaffTree[HaffTree[i].parent].code);

		if (HaffTree[HaffTree[i].parent].rightChild == i)
		{ //若第i个结点，是其双亲的右孩子结点，则在双亲的编码后再接上‘1’
			strcat(HaffTree[i].code, "1");
		}
		else
		{ //若第i个结点，是其双亲的左孩子结点，则在双亲的编码后再接上‘0’
			strcat(HaffTree[i].code, "0");
		}
		//cout<<"第"<<i<<"个结点的编码是"<<HaffTree[i].code <<endl;

		HaffTree[i].code_len = strlen(HaffTree[i].code);
	}
}
void printtree(int n = 256)
{
	/*
	cout << "哈夫曼树的存储结构如下所示：" << endl;
	cout << "  i        byte     weight   lchild    rchild   parrent    code" << endl;
	int i = 0;
	for (i = 0; i < n; i++)
	{
		printf(" %d \t    %x\t    %d    \t %d    \t %d\t   %d \t   %c\n", i, (int)HaffTree[i].byte, HaffTree[i].weight, HaffTree[i].leftChild, HaffTree[i].rightChild, HaffTree[i].parent, HaffTree[i].code);
	}
	*/
	cout << "index\tbyte\tweight\tlchild\trchild\tparent\tcodelength\tcode" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i << "\t"
             << (int)HaffTree[i].byte << "\t"
             << HaffTree[i].weight << "\t"
             << HaffTree[i].leftChild << "\t"
             << HaffTree[i].rightChild << "\t"
             << HaffTree[i].parent << "\t"
             << HaffTree[i].code_len << "\t"
             << HaffTree[i].code << "\t"
             << endl;
    }
}

//int  main(){
//    initHaffTree( );
//	Statistics(source_filename);//统计个字节出现的次数
//    printtree(10)	;//
//	sortweights(HaffTree,256);
//    printtree(10)	;
//	creatHaffTree();
//    creatHaffCode();
//    printtree(10);
//    return 0;
//}
