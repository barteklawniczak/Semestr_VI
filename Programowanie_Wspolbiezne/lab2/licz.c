#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int badanie;
	int i, j, pocz, kon, licznik=0;
	pocz = atoi(argv[2]);
	kon = atoi(argv[3]);
	for(i=pocz; i<=kon; i++)
	{
		badanie = pierwsza(i);

		if(badanie == 1)
		{
			licznik++;
		}
	}

	printf("Proces %d - %d liczb pierwszych\n", atoi(argv[1]), licznik);
	return licznik;
}

int pierwsza(int n)
{
	int i,j=0;
  	for(i=2;i*i<=n;i++)
	{
    		if(n%i == 0) return(0) ;
 	}
 	return(1);
}
