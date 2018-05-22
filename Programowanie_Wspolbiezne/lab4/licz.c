#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

struct wynik{ 
   int pocz;// początek przedzialu 
   int kon; // koniec przedzialu 
   int ile; // Ile liczb w przedziale 
}; 

int main(int argc, char *argv[])
{
	struct wynik w;
	int badanie;
	int i, j, pocz, kon, licznik=0;
	int proc = atoi(argv[1]);
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

	int fd = open("MyFifo", O_RDWR);
	if(fd < 0)
	{
		perror("Blad otwarcia");
		exit(0);
	}
	
	w.pocz=pocz;
	w.kon=kon;
	w.ile=licznik;

	int status = write(fd, &w, sizeof(w));
	if(status < 0)
	{
		perror("Blad zapisu");
		exit(0);
	}
	close(fd);
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
