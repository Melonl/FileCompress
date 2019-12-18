/*本程序实现菜单的选择*/

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
		cout << "========== Huffman 文件压缩与解压 ==========" << endl;
		cout << "========== 1、压缩文件 =============" << endl;
		cout << "========== 2、解压文件 =============" << endl;
		cout << "========== 3、退出程序 =============" << endl;
		cout << "请选择您要进行的操作:";
		int choose;
		cin >> choose;
		switch (choose)
		{
		case 1:
		{
			cout << "========== Huffman 文件压缩 ==========" << endl;
			cout << "请输入源文件名:";
			cin >> source_filename;
			cout << "请输入压缩后文件名（不含后缀名）:";
			cin >> compress_filename;
			compressFile();
			printf("源文件长度=%d", file_length);
			break;
		}
		case 2:
		{
			cout << "========== Huffman 文件压缩 ==========" << endl;
			cout << "请输入压缩文件名（包括后缀名）:";
			cin >> compress_filename;
			cout << "请输入解压后的文件名（不含后缀名）";
			cin >> decompress_filename;
			////获取当前时间

			time(&beforeTime);
			deCompressFile();
			time(&afterTime);
			cout << "解压时间为：" << (int)(afterTime - beforeTime) << endl;
			break;
		}
		case 3:
		{
			cout << "程序结束" << endl;
			return 0;
		}

		default:
		{
			cout << "请正确输入您的选择！";
			break;
		}
		}
	}
	return 0;
}
