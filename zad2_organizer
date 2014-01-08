#include<stdio.h>
#include<stdlib.h>
#include <string.h>
struct DayTime
{
	int day;
	int month;
	int year;
	int hour;
	int min;
	int sec;
};
struct Entry
{
		struct DayTime time;
		char text[256];
		int pri;
};
typedef struct Entry Entry;
Entry* LoadEntries(char* fileName, int *countPtr)
{
	FILE *in_handle;
  	char bufor[BUFSIZ];
	int day, month, year, hour,min,sec,pri,count;
	char text[256];
  	in_handle = fopen(fileName, "r");
	if(in_handle == NULL)
	{
		return NULL;
	}
	fgets(bufor, BUFSIZ, in_handle);
	sscanf(bufor, "%d", &count);
	struct Entry *entries = calloc(count, sizeof(struct Entry));
	int i = 0;
  	while (fgets(bufor, BUFSIZ, in_handle) != NULL) {
    sscanf(bufor, "%d %d/%d/%d %d:%d:%d %[^\t\n]",&pri, &day, &month, &year, &hour, &min, &sec, &text);
	strcpy(entries[i].text, text);
	entries[i].pri = pri;
	entries[i].time.day = day;
	entries[i].time.month = month;
	entries[i].time.year = year;
	entries[i].time.hour = hour;
	entries[i].time.min = min;
	entries[i].time.sec = sec;

	i++;
  }
  fclose(in_handle);
  *countPtr = count;
  return entries;
}
void SaveEntries(char* fileName, Entry* entries , int count, int actualCount)
{

		FILE *in_handle;
		in_handle = fopen(fileName, "w");
		char buff[276];
		sprintf(buff, "%d\n", actualCount);
		fputs(buff, in_handle);
		for(int i = 0; i < count; i++)
		{
			if(entries[i].pri != -1)
			{
			sprintf(buff, "%d %d/%d/%d %d:%d:%d %s\n", entries[i].pri, entries[i].time.day, entries[i].time.month, entries[i].time.year, entries[i].time.hour, entries[i].time.min, entries[i].time.sec,entries[i].text);
			fputs(buff, in_handle);
			}
		}
		fclose(in_handle);
}
void cls(void)
{
	system("cls");
}
int main(int argc, char** argv)
{
	int count;
	int id;
	printf("Organizer\n==============\n\n");
	char buff[50];
	menu_start:
	printf("Podaj plik do wczytania danych:\n");
	char line[50];
	gets(line);
	char fileName[50];
	strcpy(fileName, line);
	Entry *e = LoadEntries(fileName, &count);
	int actualCount = count;
	if(e == NULL)
	{
		printf("Nie ma takiego pliku (%s).\n", fileName);
		goto menu_start;
	}
		char yn;
	while(1)
	{
		cls();
		printf("Ilosc notatek: %d\n", count);
	printf("Id\tPri\tData\tCzas\n");
	for(int i = 0; i < count; i++)
	{
		if(e[i].pri != -1)
			printf("%d\t%d\t%d/%d/%d %d:%d:%d\n",i+1, e[i].pri, e[i].time.day, e[i].time.month, e[i].time.year, e[i].time.hour, e[i].time.min, e[i].time.sec);
	}
	printf("\nM:\nget - wyswietla notatke\nadd - dodaje nowy rekord\nfil - naklada okreslony filtr\nclr - usuwanie starszych rekordow\nexit - wychodzi z programu\nopen - otwiera inny organizer\n");
	gets(line);
	sscanf(line, "%s", &buff);
	if(strcmp(buff, "open")==0)
	{
		printf("Zapisac zmiany? y/n:  ");
		//yn = getchar();
		gets(line);
		yn = line[0];
		if(yn == 'y')
			SaveEntries(fileName, e, count, actualCount);
		cls();
		goto menu_start;
	}
	else if(strcmp(buff, "exit")==0)
	{
		printf("Zapisac zmiany? y/n:  ");
		gets(line);
		yn = line[0];
		if(yn == 'y')
			SaveEntries(fileName, e, count, actualCount);
		break;
	}
	else if(strcmp(buff, "get")==0)
	{
		printf("Podaj Id: ");
		gets(line);
		sscanf(line, "%d", &id);
		if(id > 0 && id <= count)
		{
			id--;
			cls();
			printf("Notatka [%d] z dnia %d/%d/%d, godziny %d:%d:%d o priorytecie %d\n-------------------------\n%s\n-------------------------\nMenu:\nok - wraca do trybu przegladania\ndel - usuwa notatke\nedit - edytuje notatke\n", id+1, e[id].time.day, e[id].time.month, e[id].time.year, e[id].time.hour, e[id].time.min, e[id].time.sec,e[id].pri,e[id].text);
		    gets(line);
			sscanf(line, "%s", buff);
			if(strcmp(buff, "del")==0)
			{
					e[id].pri = -1;
					actualCount--;
			}
			else if(strstr(buff, "edit")==0)
			{

			}
		}
	}
	}
}
