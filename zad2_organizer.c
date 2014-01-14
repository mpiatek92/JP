#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<time.h>
#define ENV_CLS "clear" /* komenda do czyszczenia ekranu dla odpowiedniego srodowiska */
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
typedef struct DayTime DayTime;
int IsLessOrEqual(DayTime d1, DayTime d2)
{
	int id1 = d1.year*372+d1.month*31+d1.day;
	int id2 = d2.year*372+d2.month*31+d2.day;
	return id1 <= id2 ? 1 : 0;	
}
int IsEqual(DayTime d1, DayTime d2)
{
	if(d1.day != d2.day)
	{
		return 0;
	}
	if(d1.month != d2.month)
	{
		return 0;
	}
	if(d1.year != d2.year)
	{
		return 0;
	}
	return 1;
}
Entry* LoadEntries(char* fileName, int *countPtr)
{
	*countPtr = 0;
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
		int i;
		for(i = 0; i < count; i++)
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
	system(ENV_CLS);
}
DayTime Now()
{
			time_t tim= time(NULL);
			struct tm *ts = localtime (&tim);
			DayTime time;
			time.day = ts->tm_mday;
			time.month = 1+ts->tm_mon;
			time.year = 1900 + ts->tm_year;
			time.hour = ts->tm_hour;
			time.min = ts->tm_min;
			time.sec = ts->tm_sec;
			return	time;
}
int main(int argc, char** argv)
{
	char yn;
	int day, month, year,pri;
	int count;
	int id;
	printf("Organizer\n==============\n\n");
	char buff[256];
	menu_start:
	printf("Podaj plik do wczytania danych:\n");
	char line[256];
	gets(line);
	char fileName[50];
	strcpy(fileName,line);
	Entry *e = LoadEntries(fileName, &count);
	int actualCount = count;
	if(e == NULL)
	{
		printf("Nie ma takiego pliku (%s).\nChcesz go utworzyc? (y/n): ", fileName);
		gets(line);
		yn = line[0];
		if(yn != 'y')
		{
			goto menu_start;
		}
	}
		
		int i;
		int shown;
		int priFil = -1;
		DayTime timeFil;
		timeFil.day = -1;
	while(1)
	{
		cls();
		printf("Id\tPri\tData\t\tCzas\t\tSkrot\n");
		shown =0;
		for(i = 0; i < count; i++)
		{
			if((e[i].pri != -1) && (priFil == -1 || e[i].pri == priFil) && (timeFil.day == -1 || IsEqual(timeFil, e[i].time)))
			{
				shown++;
				printf("%d\t%d\t%02d/%02d/%d\t%02d:%02d:%02d\t%.20s",i+1, e[i].pri, e[i].time.day, e[i].time.month, e[i].time.year, e[i].time.hour, e[i].time.min, e[i].time.sec,e[i].text);
				if(strlen(e[i].text) > 20)
				{
					printf("...");	
				}
				printf("\n");
			}
		}
		
		printf("Wyswietlono %d z %d wpisow\nFiltry:\nPriorytet ", shown, actualCount);
		
		if(priFil == -1)
		{
			printf("-");	
		}
		else
		{
			printf("%d", priFil);	
		}
		printf("\nData ");
		if(timeFil.day == -1)
		{
			printf("-");	
		}
		else
		{
			printf("%02d/%02d/%d", timeFil.day, timeFil.month, timeFil.year);
		}
		printf("\nWpisz \"help\" aby zobaczyc dostepne komendy\n");
		strcpy(buff, "");
		gets(line);
		sscanf(line, "%s", &buff);
		if(strcmp(buff, "open")==0)
		{
			printf("Zapisac zmiany? y/n:  ");
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
			id = -1;
			sscanf(line, "%*s %d", &id);
			if(id == -1)
			{
			printf("Podaj Id: ");
			gets(line);
			sscanf(line, "%d", &id);
		}
			if(id > 0 && id <= count)
			{
				id--;
				cls();
				printf("Notatka [%d] z dnia %02d/%02d/%d, godziny %02d:%02d:%02d o priorytecie %d\n-------------------------\n%s\n-------------------------\n", id+1, e[id].time.day, e[id].time.month, e[id].time.year, e[id].time.hour, e[id].time.min, e[id].time.sec,e[id].pri,e[id].text);
			    
			}
			else
			{
					printf("Niepoprawny ID\n\n");
			}
			printf("Wcisnij ENTER aby kontynuowac...");
			gets(line);
		}
		else if(strcmp(buff, "add")==0)
		{
			
			Entry newE;
			cls();
			printf("Podaj priorytet:\n");
			gets(line);
			pri = 1;
			sscanf(line,"%d", &pri);
			newE.pri = pri;
			
			printf("Podaj trest wiadomosci:\n");
			fgets(line, 254, stdin);
			sscanf(line, "%[^\t\n]", buff);
			strcpy(newE.text, buff);
			
			newE.time = Now();
			
			count++;
			actualCount++;
			e = realloc(e, count*sizeof(Entry));
			e[count-1] = newE;
			
		}
		else if(strcmp(buff, "del")==0)
		{
			id = -1;
			sscanf(line, "%*s %d", &id);
			if(id == -1)
			{
				printf("Podaj Id: ");
				gets(line);
				sscanf(line, "%d", &id);
			}
			if(id > 0 && id <= count)
			{
				e[id-1].pri = -1;
				actualCount--;
			}
			else
			{
					printf("Niepoprawny ID\n\n");
					gets(line);
					printf("Wcisnij ENTER aby kontynuowac...");
			}
			
			
		}
		else if(strcmp(buff, "clr")==0)
		{
			DayTime desired;
			
			day = -1;
			month = -1;
			year = -1;
			sscanf(line, "%*s %d/%d/%d", &day, &month, &year);
			if(day == -1 || month == -1 || year == -1)
			{
				printf("Podaj date, przed ktora maja zostac usuniete wpisy: ");
				gets(line);
				sscanf(line, "%d/%d/%d", &day,&month,&year);
			}
			desired.day = day;
			desired.month = month;
			desired.year = year;
			if(!(day == -1 || month == -1 || year == -1))
			{
				int i;
				for(i = 0; i < count; i++)
				{
					if(e[i].pri != -1 && (IsLessOrEqual(e[i].time, desired)==1))
					{
						e[i].pri = -1;
					}
				}
			}
		}
		else if(strcmp(buff, "edit") == 0)
		{
			id = -1;
			sscanf(line, "%*s %d", &id);
			if(id == -1)
			{
				printf("Podaj Id: ");
				gets(line);
				sscanf(line, "%d", &id);
			}
			if(id > 0 && id <= count)
			{
				cls();
				id--;
				printf("Notatka [%d] z dnia %02d/%02d/%d, godziny %02d:%02d:%02d o priorytecie %d\nOryginalny tekst:\n%s\n----------------------------\n", id+1, e[id].time.day, e[id].time.month, e[id].time.year, e[id].time.hour, e[id].time.min, e[id].time.sec,e[id].pri, e[id].text); 
				printf("Podaj priorytet:\n");
				gets(line);
				pri = e[id].pri;
				sscanf(line,"%d", &pri);
				e[id].pri = pri;
			
				printf("Podaj tresc wiadomosci:\n");
				fgets(line, 254, stdin);
				sscanf(line, "%[^\t\n]", buff);
				strcpy(e[id].text, buff);
			}
			else
			{
					printf("Niepoprawny ID\n\n");
					gets(line);
					printf("Wcisnij ENTER aby kontynuowac...");
			}
		}
		else if(strcmp(buff, "fltr")==0)
		{
			priFil = -1;
			timeFil.day = -1;
			day = -1;
			sscanf(line, "%*s %d %d/%d/%d", &priFil, &day, &month, &year);
			if(day != -1)
			{
				timeFil.day = day;
				timeFil.month = month;
				timeFil.year = year;
			}
		}
		else if(strcmp(buff, "save")==0)
		{
			cls();
			strcpy(buff, "");
			sscanf(line, "%*s %s", &buff);
			if(strlen(buff) == 0)
			{
				SaveEntries(fileName, e, count, actualCount);	
				printf("Pomyslnie zapisano organizer do pliku %s.", fileName);
			}
			else
			{
				SaveEntries(buff, e, count, actualCount);	
				printf("Pomyslnie zapisano organizer do pliku %s.", buff);
			}
			gets(line);
			
		}
		else if(strcmp(buff, "help") == 0)
		{
			cls();
			printf("Menu:\nget X - wyswietla notatke o ID = X\nadd - dodaje nowy rekord\nedit X - edytuje wpis o ID = X\ndel X - usuwa wpis o ID = X\nfltr X Y - naklada okreslony filtr X Y\n\t*X to priotytet, Y to data w formacie DD/MM/YYYY.\
			Mozna pominac argument Y. Aby ustawic filtr na okreslona date ale o dowolnym priorytecie nalezy w miejsce X wstawic -1. Uzyc bez argumentow, aby wyczysic filtr\nclr X - usuwanie starszych rekordow niz X (DD/MM/YYYY)\nsave X - zapisuje organizer do pliku (mozna podac argument X, wtedy organizer zostanie zapisany do oddzielnego pliku)\nexit - wychodzi z programu\nopen - otwiera inny organizer");
			gets(line);
		}
	}
}
