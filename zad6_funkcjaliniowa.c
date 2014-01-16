#include<stdio.h>
#include<stdlib.h>
void cls(void)
{
     system("clear");     
}
int main(int argc, char** argv)
{
    int args[10];
    cls();
    puts("Podawaj kolejne wspolczynniki funkcji:\n");
    int i=0;
    int j;
    int arg;
    char buff[BUFSIZ];
    while(i<10)
    {
            arg = -1;
            printf("Podaj %d. wspolczynnik: ", (i+1));
            gets(buff);
            sscanf(buff, "%d", &arg);
            if(arg >= 0 && arg <= 10)
            {
                   args[i] = arg;
                   i++;
            }
            puts("\n");
    }
    cls();
    puts("  ^");
    for(i = 0; i <= 10; i++)
    {
          printf(i!=10 ? "%2d|" : "  |",10-i);
          for(j = 0; j < 10; j++)
          {
                if(args[j] == 10-i)
                {
                      printf(i == 10? "_*" : " *");     
                }
                else
                {
                    printf(i == 10? "__" : "  ");
                }
          }
          if(i == 10)
          {
               printf(">\n");    
          }    
          else
          {
              printf("\n");
          }
    }
    puts("    1 2 3 4 5 6 7 8 9 10");
    gets(buff);
}
