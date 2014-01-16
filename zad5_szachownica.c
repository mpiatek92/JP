#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char cipher[] = { 'a', 'b', 'c', 'd','e','f','g','h','i','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
int GetCode(char c)
{
	int raw = -1;
	int i;
	for(i = 0; i < 25; i++)
	{
		if(cipher[i] == c)
		{
			raw = i;	
		}
	}
	if(raw == -1)
	{
		return	0;
	}
	return ((raw / 5)+1)*10 + (raw%5)+1;
}
char GetCharFromCode(int code)
{
	if(code == 0)
	{
	return ' ';	
	}
	div_t d = div(code, 10);
	return cipher[(d.quot-1)*5+d.rem-1];	
}
int main(int argc, char** argv)
{
		char buff[BUFSIZ];
		int len,i;
		char tmp;
		int code;
		int codes[256];
		int codesCount;
		while(1)
		{
			puts("Chcesz (o)dszyfrowac wiadomosc czy (z)aszyfrowac? (q zeby wyjsc)\n");
			gets(buff);
			if(buff[0] == 'q')
			{
				break;
			}	
			if(buff[0] == 'z')
			{
				puts("Podaj wiadomosc do zaszyfrowania:\n");
				gets(buff);
				len = strlen(buff);
				int i;
				for(i = 0; i<len; i++)
				{
						tmp = buff[i];
						tmp = tolower(tmp);
						if(tmp == 'j')
							tmp = 'i';
						code = GetCode(tmp);
						if(code != 0)
						{
							printf("%d ", code);	
						}
				}
				puts("\n");
			}
			else
			{
				puts("Podawaj kolejne znaki zaszyfrowanej wiadomosci, podaj	0 aby zakonczyc wpisywanie\n");
				codesCount = 0;
				for(i = 0; i < 256; i++)
				{
					gets(buff);
					code = -1;
					sscanf(buff, "%d", &code);
					if(code == -1)
					{
						codes[codesCount] = 0;
					}
					else if(code == 0)
					{
						break;
					}
					else
					{
						codes[codesCount] = code;
					}
					codesCount++;
				}
				if(codesCount > 0)
				{
					puts("Odszyfrowana wiadomosc to:\n");
					for(i = 0; i < codesCount; i++)
					{
						printf("%c", GetCharFromCode(codes[i]));	
					}
				}
				puts("\n");
			}
		}
		
}
