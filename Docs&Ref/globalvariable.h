int bytes_count = 0;							   //哈夫曼树的叶子结点数量
long long file_length = 0;						   //保存文件的字节数，初始为０
const int FILENAMEMAX = 128;					   //文件名（包括路径），长度不能超过127
const int SUFFIXNAMEMAX = 10;					   //文件后缀名长度不超过9个字符
char source_filename[FILENAMEMAX] = "house.bmp";   //源文件名字
char compress_filename[FILENAMEMAX] = "house.buf"; //压缩文件名字
char decompress_filename[FILENAMEMAX] = "dehouse"; //解压文件名字

char prefix_filename[128]; //文件前缀名
char suffix_filename[128]; // 文件后缀名

const int BUFF_MAXSIZE = 1024;			 //文件哈夫曼编码缓冲区的大小
char buff[BUFF_MAXSIZE] = "";			 //文件哈夫曼编码缓冲区 (生成压缩文件时，各字节的编码先存在buff中，然后8个码压缩成一个字节存到buff_string中缓冲区
char buff_string[BUFF_MAXSIZE / 8] = ""; //压缩文件写入缓冲区

const int BLOCK_MAXSIZE = 512;  //写入解压文件的缓冲区的大小
char block[BLOCK_MAXSIZE] = ""; //写入解压文件的缓冲区
int block_current = 0;			//写解压文件缓冲区的当前读写位置

struct HaffNode
{						//哈夫曼树的结点结构
	unsigned char byte; //结点数据
	long long weight;   //权值
	int parent;			//双亲结点下标
	int leftChild;		//左孩子下标
	int rightChild;		//右孩子下标
	char code[256];		//哈夫曼编码
	int code_len;		//编码长度
};

HaffNode HaffTree[511]; //哈夫曼树
