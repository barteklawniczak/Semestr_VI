#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

struct wynik{ 
   int pocz;// początek przedzialu 
   int kon; // koniec przedzialu 
   int ile; // Ile liczb w przedziale 
}; 

struct odcinek{
   int pocz;  // Początek przedziału 
   int kon;   // Koniec przedziału 
   int numer; // Kolejny numer odcinka 
};


int main(int argc, char *argv[])
{
	struct wynik w;
	int badanie;
	int i, j, pocz, kon, res, licznik=0;

	int fd = open("MyFifo", O_RDWR);
	int fdwej = open("wejscie", O_RDWR);
	if(fd < 0 || fdwej <0)
	{
		perror("Blad otwarcia");
		exit(0);
	}
	struct odcinek o;
	printf("jestem w funkcji licz\n");
	do
	{
		res = read(fdwej,&o,sizeof(o));
		if(res<0)
		{
			exit(0);
		}
		if(o.numer == -1)
		{	exit(0);}
		licznik=0;
		for(i=o.pocz; i<=o.kon; i++)
		{
			badanie = pierwsza(i);
	
			if(badanie == 1)
			{
				licznik++;
			}
		}
	
		w.pocz=o.pocz;
		w.kon=o.kon;
		w.ile=licznik;

		int status = write(fd, &w, sizeof(w));
		if(status < 0)
		{
			perror("Blad zapisu");
			exit(0);
		}
        printf("pocz %d kon %d wynik %d %d\n",w.pocz,w.kon,w.ile,status);
	}while(o.numer!=-1);
	close(fd);
	close(fdwej);
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
