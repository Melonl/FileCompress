int bytes_count = 0;							   //����������Ҷ�ӽ������
long long file_length = 0;						   //�����ļ����ֽ�������ʼΪ��
const int FILENAMEMAX = 128;					   //�ļ���������·���������Ȳ��ܳ���127
const int SUFFIXNAMEMAX = 10;					   //�ļ���׺�����Ȳ�����9���ַ�
char source_filename[FILENAMEMAX] = "house.bmp";   //Դ�ļ�����
char compress_filename[FILENAMEMAX] = "house.buf"; //ѹ���ļ�����
char decompress_filename[FILENAMEMAX] = "dehouse"; //��ѹ�ļ�����

char prefix_filename[128]; //�ļ�ǰ׺��
char suffix_filename[128]; // �ļ���׺��

const int BUFF_MAXSIZE = 1024;			 //�ļ����������뻺�����Ĵ�С
char buff[BUFF_MAXSIZE] = "";			 //�ļ����������뻺���� (����ѹ���ļ�ʱ�����ֽڵı����ȴ���buff�У�Ȼ��8����ѹ����һ���ֽڴ浽buff_string�л�����
char buff_string[BUFF_MAXSIZE / 8] = ""; //ѹ���ļ�д�뻺����

const int BLOCK_MAXSIZE = 512;  //д���ѹ�ļ��Ļ������Ĵ�С
char block[BLOCK_MAXSIZE] = ""; //д���ѹ�ļ��Ļ�����
int block_current = 0;			//д��ѹ�ļ��������ĵ�ǰ��дλ��

struct HaffNode
{						//���������Ľ��ṹ
	unsigned char byte; //�������
	long long weight;   //Ȩֵ
	int parent;			//˫�׽���±�
	int leftChild;		//�����±�
	int rightChild;		//�Һ����±�
	char code[256];		//����������
	int code_len;		//���볤��
};

HaffNode HaffTree[511]; //��������
