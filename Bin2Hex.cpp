#include"stdio.h"
#include"string.h"

int file_size(const char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (!fp) return -1;
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	fclose(fp);
	return size;
}

int mode1(char* src, char* dst)
{
	FILE* fp1 = fopen(src, "rb");
	if (fp1 == NULL)
	{
		printf("No Such File or Directory ! LOL");
		return 0;
	}
	FILE* fp2 = fopen(dst, "w+");
	int tmp = 0;
	for (int i = 0; i < file_size(src); i++)
	{
		tmp = (int)fgetc(fp1);
		printf("\\x%02x", tmp);
		fprintf(fp2, "\\x%02x,", tmp);
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}

int mode2(char *src ,char *dst)
{
	FILE* fp1 = fopen(src, "rb");
	FILE* fp2 = fopen(dst, "w+");
	int tmp = 0;
	for (int i = 0; i < file_size(src); i++)
	{
		if (i % 16 == 0)
		{
			fprintf(fp2, "\"\n\"");
		}
		tmp = (int)fgetc(fp1);
		printf("\\x%02x", tmp);
		fprintf(fp2, "\\x%02x", tmp);
	}
	fprintf(fp2, "\"");
	fclose(fp1);
	fclose(fp2);
	return 0;
}

int mode3(char* src, char* dst)
{
	FILE* fp1 = fopen(src, "rb");
	FILE* fp2 = fopen(dst, "w+");
	int tmp = 0;
	for (int i = 0; i < file_size(src); i++)
	{
		tmp = (int)fgetc(fp1);
		printf("%02x", tmp);
		fprintf(fp2, "%02x", tmp);
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}

int main(int argc,char*argv[],char* envp[])
{
	char usage[256]=
		"\n[-] Usage: Bin2Hex SrcFile -m 1,2... DstFile \n"
		"[-] mode 1: Convert to C-ArrayLike Formation \n"
		"[-] mode 2: Convert to C-Srting Formation \n"
		"[-] mode 3: Convert to Hex Formation \n";
	if (argc < 5)
	{
		printf(usage);
		return 0;
	}
	switch (argv[2][1])
	{
	case 'm':
		switch (argv[3][0])
		{
		case '1':
			mode1(argv[1],argv[4]);
			break;
		case '2':
			mode2(argv[1], argv[4]);
			break;
		case '3':
			mode3(argv[1], argv[4]);
			break;
		default:
			printf(usage);
			break;
		}
		break;
	default:
		printf(usage);
		break;
	}
	return 0;
}