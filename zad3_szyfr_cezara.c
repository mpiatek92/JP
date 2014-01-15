#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define OFFSET 13
#define ASCII_START 97 //litera a
#define ASCII_END 122 // litera z
#define ASCII_SPACE 32 // spacja
char* code(char* src, int decode) //decode to bool okreslajacy, czy funkcja ma dekodowac czy kodowac
{
	int len = strlen(src);
	unsigned char tmp;
	for(int i = 0; i < len; i++)
	{
		tmp = src[i];

		tmp = tolower(tmp);
		if(tmp == ASCII_SPACE)
		{
			continue;
		}
		else if(tmp < ASCII_START || tmp > ASCII_END)
		{
			tmp = ASCII_SPACE;
			continue;
		}
		if(!decode)
		{
			tmp += OFFSET;
			if(tmp > ASCII_END)
			{
				tmp = ASCII_START + tmp - ASCII_END -1;
			}
		}
		else
		{
			tmp -= OFFSET;
			if(tmp < ASCII_START)
			{
				tmp = ASCII_END - ASCII_START+tmp+1;

			}
		}
		src[i] = tmp;
	}
	return src;
}
int main(int argc, char** argv)
{
	puts("Wpisz tekst do zakodowania:\n");
	char buff[1024];
	gets(buff);
	char* c = code(buff, 0);
	printf("Zakodowany: %s\n", c);
	c = code(c, 1);
	printf("Odkodowany: %s\n", c);
}
