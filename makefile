all: p1 p2 p3 p4 p5 p6
p1: zad1_czasy.c
	gcc -o zad1_czasy zad1_czasy.c
p2: zad2_organizer.c
	gcc -o zad2_organizer zad2_organizer.c
p3: zad3_szyfr_cezara.c
	gcc -o zad3_szyfr_cezara zad3_szyfr_cezara.c
p4: zad4_warsztat.c
	gcc zad4_warsztat zad4_warsztat.c
p5: zad5_szachownica.c
	gcc -o zad5_szachownica zad5_szachownica.c
p6: zad6_funkcjaliniowa.c
	gcc -o zad6_funkcjaliniowa zad6_funkcjaliniowa.c
