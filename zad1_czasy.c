#include<stdio.h>
#include<stdlib.h>
int abs(int n)
{
	if(n >= 0)
	{
		return n;
	}
	else
	{
		return 0 - n;
	}
}
struct czas
{
	int godzina;
	int minuta;
	int sekunda;
};
void print_czas(czas c)
{
	printf("%02d:%02d:%02d",c.godzina,c.minuta,c.sekunda);
}
czas get_czas_from_s(int s)
{
	czas wynik;
	div_t d = div(s,3600);
	wynik.godzina = d.quot;
	d = div(d.rem,60);
	wynik.minuta = d.quot;
	wynik.sekunda = d.rem;
	return wynik;
}
int get_s_from_czas(czas c)
{
	return c.godzina*3600 + c.minuta*60+c.sekunda;
}
czas diff(czas c1, czas c2)
{
	return get_czas_from_s(abs(get_s_from_czas(c1)-get_s_from_czas(c2)));
}
int main(int argc, char** argv)
{
	int h,m,s;
	czas c1,c2;
	while(1)
	{
		printf("Podaj 1. czas w formacie HH:MM:SS\n");
		scanf("%d:%d:%d", &h,&m,&s);
		c1.godzina = h;
		c1.minuta = m;
		c1.sekunda = s;
		
		printf("\nPodaj 2. czas w formacie HH:MM:SS\n");
		scanf("%d:%d:%d", &h,&m,&s);
		c2.godzina = h;
		c2.minuta = m;
		c2.sekunda = s;
		printf("\nWynik to: ");
		print_czas(diff(c1,c2));
		printf("\n----\n");
	}
}
