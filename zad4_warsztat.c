#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define DB "db.txt"
#define LR "lastrun.txt"
#define ENV_CLS "clear"
struct Client
{
	char name[256];
	char vehicle[256];
	char notes[256];
	int del;
};
typedef struct Client Client;
Client* c;
int count;
int actualCount;
char buff[BUFSIZ];
/* Tu gdzies jest blad pamieci; u mnie na laptiopie z windowsem dziala bez zarzutow
a na sigmie raz dziala, raz nie. Funkcja jest zadeklarowana ale nie uzywana*/
void LastRun(void)
{
	FILE* f;
	f = fopen(LR, "r");
	fgets(buff, BUFSIZ, f);
	int day,mon,yr,hr,min,sec;
	day = 1;
	sscanf(buff, "%d/%d/%d %d:%d:%d", &day, &mon, &yr, &hr, &min,&sec);
	if(day == -1)
	{
		return;	
	}
	
	time_t now;
	struct tm lastrun;
	time(&now);	
	lastrun = *localtime(&now);	
	fclose(f);
	f=fopen(LR, "w");
	sprintf(buff, "%d/%d/%d %d:%d:%d", lastrun.tm_mday, lastrun.tm_mon+1, lastrun.tm_year+1900, lastrun.tm_hour, lastrun.tm_min, lastrun.tm_sec);
	fputs(buff, f);
	fclose(f);
	
	lastrun.tm_hour = hr;
	lastrun.tm_min = min;
	lastrun.tm_sec = sec;
	lastrun.tm_mon = mon-1;
	lastrun.tm_mday = day;
	lastrun.tm_year = yr-1900;
double diff = difftime(now,mktime(&lastrun));
	printf("Ostatnio program byl uruchomiony %02d/%02d/%02d o godz. %02d:%02d:%02d. Od tego czasu uplynelo ", day,mon,yr,hr,min,sec);
	div_t d = div(diff, 3600);
	hr = d.quot;
	d = div(d.rem, 60);
	min = d.quot;
	sec = d.rem;
	printf("%d:%02d:%02d (H:MM:SS)\n", hr, min,sec);
	fclose(f);
}
void Load(void)
{
	FILE* f;
	f = fopen(DB, "r");
	fgets(buff, BUFSIZ, f);
	sscanf(buff, "%d", &count);
	actualCount = count;
	c = (Client*)calloc(count, sizeof(Client));
	int i;
	for(i = 0; i < count; i++)
	{
		fgets(buff,BUFSIZ,f);
		sscanf(buff, "%[^\t\n]", &c[i].name);
		fgets(buff,BUFSIZ,f);
		sscanf(buff, "%[^\t\n]", &c[i].vehicle);
		fgets(buff,BUFSIZ,f);
		sscanf(buff, "%[^\t\n]", &c[i].notes);
		c[i].del = 0;
		
	}
	
	fclose(f);	
}
void Save(void)
{
	FILE *f;
	f = fopen(DB,"w");
	sprintf(buff, "%d\n", actualCount);
	fputs(buff, f);
	int i;
	for(i=0; i < count; i++)
	{
		if(c[i].del == 0)
		{
			sprintf(buff, "%s\n", c[i].name);
			fputs(buff, f);
			sprintf(buff, "%s\n", c[i].vehicle);
			fputs(buff, f);
			sprintf(buff, "%s\n", c[i].notes);
			fputs(buff, f);
		}
	}
	fclose(f);
}
void Show(void)
{
	int i;
	printf("id\timie i nazwisko\tpojazd\tuwagi\n");
	for(i = 0; i < count; i++)
	{
		if(c[i].del == 0)
		{
			printf("%d\t%s\t%s\t%s\n", (i+1), c[i].name, c[i].vehicle, c[i].notes);
		}
	}
}
void Add(void)
{
	Client newC;
	printf("Podaj imie i nazwisko klienta:\n");
	gets(buff);
	strcpy(newC.name, buff);
	
	printf("Podaj marke i model pojazdu klienta:\n");
	gets(buff);
	strcpy(newC.vehicle, buff);
	
	printf("Uwagi:\n");
	gets(buff);
	strcpy(newC.notes, buff);
	newC.del = 0;
	actualCount++;
	count++;
	c= realloc(c, count*sizeof(Client));
	c[count-1] = newC;
}
void Delete(void)
{
	printf("Podaj id klienta, ktorego chcesz usunac (0 aby anulowac):\n");
	gets(buff);
	int del = 0;
	sscanf(buff, "%d", &del);
	del--;
	if(del >= 0 && del < count)
	{
		c[del].del = 1;	
		actualCount--;
	}
}
void cls(void)
{
	system(ENV_CLS);
}
int main(int argc, char** argv)
{
	Load();
	int menu = -1;
	cls();
	/*LastRun();*/
	while(menu != 0)
	{
		Show();
		printf("Menu:\n\
0 - wyjdz i zapisz\n\
1 - dodaj rekord\n\
2 - usun rekord\n");
		gets(buff);
		menu = -1;
		sscanf(buff, "%d", &menu);
		cls();
		switch(menu)
		{
			case 1: Add(); break;
			case 2: Delete(); break;
		}
		cls();
	}
	Save();
}
