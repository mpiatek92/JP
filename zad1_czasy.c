#include<stdio.h>
#include<stdlib.h>
#define DOBA 86399 /* sekund */
struct czas
{
	int godzina;
	int minuta;
	int sekunda;
};
typedef struct czas czas;

void print_czas(czas c)
{
	printf("%02d:%02d:%02d",c.godzina,c.minuta,c.sekunda);
}
czas get_czas_from_s(int s)
{
	czas wynik;
	div_t d = div(s,60*60);
	wynik.godzina = d.quot;
	d = div(d.rem,60);
	wynik.minuta = d.quot;
	wynik.sekunda = d.rem;
	return wynik;
}
int get_s_from_czas(czas c)
{
	return c.godzina*60*60 + c.minuta*60+c.sekunda;
}
czas diff(czas c1, czas c2)
{
	return get_czas_from_s(abs(get_s_from_czas(c1)-get_s_from_czas(c2)));
}
void test(void)
{
		int vals[] = {0,0,0,0,0,0,0,0,0,0};
		czas test;
		int i;
		for(i = 0; i <= DOBA; i++)
		{
			test = get_czas_from_s(i);
			vals[(test.godzina % 10)]++;
			vals[(test.godzina / 10)]++;

			vals[(test.minuta % 10)]++;
			vals[(test.minuta / 10)]++;

			vals[(test.sekunda % 10)]++;
			vals[(test.sekunda / 10)]++;
		}
		int max, maxpos;
		max = vals[0];
		maxpos = 0;
		printf("Wystapienia poszczegolnych cyfr na wyswietlaczu od 00:00:00 do 23:59:59:\n");
		for(i = 0; i < 10; i++)
		{
			printf("%d: %d\n", i, vals[i]);
			if(vals[i] > max)
			{
				max = vals[i];
				maxpos = i;
			}
		}
		printf("\nCyfra/y najczesciej wystepujaca/e to %d", (maxpos));
		for(i = 0; i < 10; i++)
		{
			if(i!= maxpos && vals[i] == max)
			{
				printf(" i %d", i);
			}
		}
		printf("\n");
}
int main(int argc, char** argv)
{
	test();
	int h,m,s;
	czas c1,c2;
	printf("Wpisz -1 aby zakonczyc\n");
	while(1)
	{
		printf("Podaj 1. czas w formacie HH:MM:SS\n");
		scanf("%d:%d:%d", &h,&m,&s);
		if(h == -1)
		{
			break;
		}
		c1.godzina = h;
		c1.minuta = m;
		c1.sekunda = s;
		printf("\nPodaj 2. czas w formacie HH:MM:SS\n");
		scanf("%d:%d:%d", &h,&m,&s);
		if(h == -1)
		{
			break;
		}
		c2.godzina = h;
		c2.minuta = m;
		c2.sekunda = s;
		printf("\nWynik to: ");
		print_czas(diff(c1,c2));
		printf("\n----\n");
	}
}
