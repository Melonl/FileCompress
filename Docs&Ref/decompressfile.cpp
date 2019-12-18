/**
��ѹ�ļ� 
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
{   //��ѹ�ļ���
	// cout<<"����ѹ���ļ����������׺��Ϊ.buf"<<endl;
	// cin>> compress_filename;
	//��ѹ���ļ�
	FILE *ifp = fopen(compress_filename, "rb");
	if (ifp == NULL) //�ж��ļ��Ƿ����
	{
		cout << compress_filename << "ѹ���ļ������ڻ�ռ��!\r\n";
		exit(4);
	}

	// ��ʼ���ļ�ͷ��
	//�ļ����ͳ��ȣ�char�����ļ�����(char [SUFFIXNAMEMAX] )���ļ�����(long long)��������Ľ����(int)���ֽ�b1��Ȩ��w1���ֽ�b2��Ȩ��b2�����������ֽ�bn,Ȩ��wn
	int suffix_filename_len;
	fscanf(ifp, "%d,", &suffix_filename_len);			 //��Դ�ļ��ĺ�׺��
	fread(suffix_filename, 1, suffix_filename_len, ifp); //��Դ�ļ��ĺ�׺��д��ѹ���ļ�����ѹʱ��ԭԴ�ļ������ͣ�
	fscanf(ifp, ",%ld,", &file_length);					 //д��Դ�ļ������ֽ���
	fscanf(ifp, "%d,", &bytes_count);					 //д��Դ�ļ��б�������ֽ����� ��С��256��

	initHaffTree(); //��ʼ�����������洢�ṹ

	//�����ֽ�Ƶ�ȣ��ٻ�ԭ��������
	for (int i = 0; i < bytes_count; i++)
	{
		fscanf(ifp, "%c,", &HaffTree[i].byte);
		fscanf(ifp, "%lld,", &HaffTree[i].weight);
	}
	char tempc;

	creatHaffTree(); //�����������
	printtree(511);

	//  ��ʼ�������ģ������н���
	//��ʼ������ȫ�ֱ���
	int buff_current = 0;			// �������α�0~BUFF_MAXSIZE
	int byte_current = 0;			// �ֽ��α� 0~7;
	int root = bytes_count * 2 - 2; //�����
	int tree_current = root;		//������α�
	int block_current = 0;
	strcpy(buff, "");  //��ն�������
	strcpy(block, ""); //���д������
	char c;
	int test;

	//�򿪽�ѹ�ļ���׼��д��
	strcat(decompress_filename, ".");
	strcat(decompress_filename, suffix_filename);
	FILE *ofp = fopen(decompress_filename, "wb");
	if (ofp == NULL)
	{ //�ж��ļ��Ƿ����
		cout << decompress_filename << "��ѹ�ļ������ڻ�ռ��!\r\n";
		exit(4);
	}

	fread(buff, 1, BUFF_MAXSIZE - 1, ifp); //װ��������
	cout << buff;

	int refile_length = 0; //�ѱ���ѹ�������ֽ�����

	while (refile_length < file_length) //�ļ�û����
	{
		if (block_current > BLOCK_MAXSIZE - 1)
		{										  //��������������д���ļ�
			fwrite(block, 1, block_current, ofp); //  �˴�������
			block_current = 0;
		}

		if (HaffTree[tree_current].leftChild == -1)
		{ //Ҷ�ӽڵ㣬�����ýڵ㣬���Ѹ��ֽ�д���ѹ�ļ���
			c = HaffTree[tree_current].byte;
			block[block_current] = c;
			block_current++;
			block[block_current] = '\0';

			//strcat(block,);
			tree_current = root; //�α�ص������
			refile_length++;	 //����ѹ�ֽ�����1
		}
		else
		{ //�Ȼ������ڵ���һλ������0����ת�����ӣ�����1����ת���Һ���

			if ((buff[buff_current] >> (7 - byte_current)) & 1 == 1)
				tree_current = HaffTree[tree_current].rightChild;
			else
				tree_current = HaffTree[tree_current].leftChild;
			
			if (byte_current < 7)
			{ //��һ���ֽ�֮�ڣ�buff_current���䣬byte_current��1
				byte_current++;
			}
			else
			{ //һ���ֽڸս�������Ҫ֪����һ���ֽ�
				byte_current = 0;
				buff_current++;
				if (buff_current >= BUFF_MAXSIZE - 1)
				{ //�������Ľ���Ѿ������ˣ�������һ��

					fread(buff, 1, BUFF_MAXSIZE - 1, ifp); //װ��������
					buff_current = 0;
				}
			}
		}
	}
	fwrite(block, 1, block_current, ofp); //��������ʣ����ַ�
	fclose(ifp);
	fclose(ofp);
}

/*
int  main(){	
  deCompressFile();    
  return 0; 
}
*/
