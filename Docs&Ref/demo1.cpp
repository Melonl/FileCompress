/*������ʵ�ֲ˵���ѡ��*/

#include <ctime>

#ifndef GLOBALVARIABLE_HEAD
#define GLOBALVARIABLE_HEAD
#include "globalvariable.h"
#endif

/*
#ifndef COUNT_HEAD
#define  COUNT_HEAD
#include "count.cpp"
#endif
*/

#ifndef COMPRESSFILE_HEAD
#define COMPRESSFILE_HEAD
#include "compressfile.cpp"
#endif

#ifndef DECOMPRESSFILE_HEAD
#define DECOMPRESSFILE_HEAD
#include "decompressfile.cpp"
#endif

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

int main()
{
	while (1)
	{

		time_t beforeTime, afterTime;
		cout << "========== Huffman �ļ�ѹ�����ѹ ==========" << endl;
		cout << "========== 1��ѹ���ļ� =============" << endl;
		cout << "========== 2����ѹ�ļ� =============" << endl;
		cout << "========== 3���˳����� =============" << endl;
		cout << "��ѡ����Ҫ���еĲ���:";
		int choose;
		cin >> choose;
		switch (choose)
		{
		case 1:
		{
			cout << "========== Huffman �ļ�ѹ�� ==========" << endl;
			cout << "������Դ�ļ���:";
			cin >> source_filename;
			cout << "������ѹ�����ļ�����������׺����:";
			cin >> compress_filename;
			compressFile();
			printf("Դ�ļ�����=%d", file_length);
			break;
		}
		case 2:
		{
			cout << "========== Huffman �ļ�ѹ�� ==========" << endl;
			cout << "������ѹ���ļ�����������׺����:";
			cin >> compress_filename;
			cout << "�������ѹ����ļ�����������׺����";
			cin >> decompress_filename;
			////��ȡ��ǰʱ��

			time(&beforeTime);
			deCompressFile();
			time(&afterTime);
			cout << "��ѹʱ��Ϊ��" << (int)(afterTime - beforeTime) << endl;
			break;
		}
		case 3:
		{
			cout << "�������" << endl;
			return 0;
		}

		default:
		{
			cout << "����ȷ��������ѡ��";
			break;
		}
		}
	}
	return 0;
}
