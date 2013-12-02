#include<stdio.h>
#include<stdlib.h>
struct czas
{
	int godzina;
	int minuta;
	int sekunda;
};
void print_czas(struct czas c1)
{
	printf("%02d:%02d:%02d",c1.godzina,c1.minuta,c1.sekunda);
}
struct czas get_czas_from_s(int s)
{
	struct czas wynik;
	div_t d = div(s,60*60);
	wynik.godzina = d.quot;
	d = div(d.rem,60);
	wynik.minuta = d.quot;
	wynik.sekunda = d.rem;
	return wynik;
}
int get_s_from_czas(struct czas c)
{
	return c.godzina*60*60 + c.minuta*60+c.sekunda;
}
struct czas diff(struct czas c1,struct czas c2)
{
	return get_czas_from_s(abs(get_s_from_czas(c1)-get_s_from_czas(c2)));
}
int main(int argc, char** argv)
{
	int h,m,s;
	struct czas c1,c2;
	printf("Podaj -1 zeby wyjsc\n");
	while(1)
	{
		printf("Podaj 1. czas w formacie HH:MM:SS\n");
		scanf("%d:%d:%d", &h,&m,&s);
		c1.godzina = h;
		c1.minuta = m;
		c1.sekunda = s;
		if(c1.godzina == -1)
		{
			break;
		}
		printf("\nPodaj 2. czas w formacie HH:MM:SS\n");
		scanf("%d:%d:%d", &h,&m,&s);
		c2.godzina = h;
		c2.minuta = m;
		c2.sekunda = s;
		if(c2.godzina == -1)
		{
			break;
		}
		printf("\nWynik to: ");
		print_czas(diff(c1,c2));
		printf("\n----\n");
	}
}

