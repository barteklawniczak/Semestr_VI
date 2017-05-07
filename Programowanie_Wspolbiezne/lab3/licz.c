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

	int fd = open("wynik", O_APPEND | O_WRONLY);
	if(fd < 0)
	{
		perror("Blad otwarcia");
		exit(0);
	}
	printf("Teraz proces %d chce zablokowac plik, aby zapisac swoj wynik\n", proc);
	lockf(fd, F_LOCK, sizeof(w));
	printf("Teraz proces %d zablokowal plik\n", proc);
	
	w.pocz=pocz;
	w.kon=kon;
	w.ile=licznik;

	int status = write(fd, &w, sizeof(w));
	if(status < 0)
	{
		perror("Blad zapisu");
		exit(0);
	}
	printf("Teraz proces %d odblokowywuje plik\n", proc);
	lockf(fd, F_ULOCK, 1);
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
