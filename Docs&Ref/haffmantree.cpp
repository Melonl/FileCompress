/**
������֪�ļ��ֽڵ�Ƶ�ȣ������������ 
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

void initHaffTree();								//��ʼ��������������������洢�ṹ
void Statistics(char fileName[]);						//ͳ���ļ����ֽڵ�Ƶ��
void sortweights(HaffNode HaffTree[], int bytes_count); //���ֽڳ��ֵ�Ƶ�Ƚ��н�������

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
	//��ʼ��Ȩֵ��¼����
	//���ļ�
	FILE *ifp = fopen(fileName, "rb");
	if (ifp == NULL) //�ж��ļ��Ƿ����
	{
		cout << fileName << "�ļ������ڻ�ռ��!\r\n";
		exit(4);
	}
	unsigned char c;	  //���ն�ȡ��ÿ���ֽ�
	file_length = 0;	  //�����ļ����ֽ�������ʼΪ��
	fread(&c, 1, 1, ifp); //���ļ��ж�ȡһ���ֽڵ� c
	while (!feof(ifp))	//�ļ�û����
	{
		HaffTree[c].weight++;
		file_length++;		  //�ַ�����ԭ�ļ�����+1
		fread(&c, 1, 1, ifp); //���ļ��ж�ȡһ���ֽڵ� c
	}
	//	cout<< "������ֽ�Ϊ��λ��Ȩֵͳ��\r\n" ;

	fclose(ifp);

	// ͳ��һ��Ȩֵ����0�Ľ�����
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
	return a.weight > b.weight; //����
}

void sortweights(HaffNode HaffTree[], int bytescount = 256)
{
	sort(HaffTree, HaffTree + bytescount - 1, compare);
}

void creatHaffTree()
{
	///	initHaffTree( );
	//	cout<<"��������Ҷ�ӽ��ĸ���Ϊ"<<bytes_count<<endl;
	int min1 = 0, min2 = 1;	//weightֵ��С�����������ĸ����λ��
	int current = bytes_count; //�ϲ����ĸ����洢λ��

	for (int i = 1; i < bytes_count; i++)
	{ //����bytes_count -1 �����ĺϲ���
		//�ҳ� min1 ��min2
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
			{											   //min2 δ��ʼ��
				if (HaffTree[j].parent == -1 && j != min1) //��ʼ��min2 ���ܿ�min1
					min2 = j;
			}
			else
			{ //min2�Ѿ���ʼ��
				if (j != min1 && HaffTree[j].parent == -1 && HaffTree[j].weight <= HaffTree[min2].weight)
					min2 = j;
			}
		}
		// ��min1 ��min2 ����λ���ϵ��������кϲ���
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
	int root = bytes_count * 2 - 2; //��ȷ
	HaffTree[root].code[0] = '\0';
	//	cout<<"�����ı���"<<HaffTree[root].code <<endl;
	for (int i = root - 1; i >= 0; i--)
	{
		//cout<<"��"<<i<<"�����ı���ԭ������"<<HaffTree[HaffTree[i].parent].code <<endl;

		strcpy(HaffTree[i].code, HaffTree[HaffTree[i].parent].code);

		if (HaffTree[HaffTree[i].parent].rightChild == i)
		{ //����i����㣬����˫�׵��Һ��ӽ�㣬����˫�׵ı�����ٽ��ϡ�1��
			strcat(HaffTree[i].code, "1");
		}
		else
		{ //����i����㣬����˫�׵����ӽ�㣬����˫�׵ı�����ٽ��ϡ�0��
			strcat(HaffTree[i].code, "0");
		}
		//cout<<"��"<<i<<"�����ı�����"<<HaffTree[i].code <<endl;

		HaffTree[i].code_len = strlen(HaffTree[i].code);
	}
}
void printtree(int n = 256)
{
	/*
	cout << "���������Ĵ洢�ṹ������ʾ��" << endl;
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
//	Statistics(source_filename);//ͳ�Ƹ��ֽڳ��ֵĴ���
//    printtree(10)	;//
//	sortweights(HaffTree,256);
//    printtree(10)	;
//	creatHaffTree();
//    creatHaffCode();
//    printtree(10);
//    return 0;
//}
