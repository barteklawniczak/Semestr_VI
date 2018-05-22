#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>

struct wynik { 
   int pocz;// początek przedzialu 
   int kon; // koniec przedzialu 
   int ile; // Ile liczb w przedziale 
}; 

int main(int argc, char *argv[])
{
	int pocz,kon,N,last,i,badanie,suma=0,res,pocz2,kon2,wr;
	int fd[2];
	pipe(fd);
	pocz = atoi(argv[1]);
	kon = atoi(argv[2]);
	N = atoi(argv[3]);
	double przedzial2 = (double)(kon - pocz)/N;
	int przedzial = (kon - pocz)/N;
	if(przedzial2 > przedzial)	//sprawdzenie czy przedzial dzieli sie calkowicie
	{
		przedzial++;
	}
	time_t tstart, tstop;

	pocz2=pocz;
	kon2=kon;
	time(&tstart); 
	for(i=0;i<N;i++)
	{
			pocz=(i*przedzial)+pocz2;
			kon = ((i+1)*przedzial)+pocz2-1;
			if(kon>kon2){kon=kon2;}
			if(fork()==0)
			{
				close(fd[0]);
				int licznik=0,badanie,j;
				struct wynik w;
				for(j=pocz; j<=kon; j++)
				{
					badanie = pierwsza(j);

					if(badanie == 1)
					{
						licznik++;
					}
				}
				w.pocz=pocz;
				w.kon=kon;
				w.ile=licznik;
				wr=write(fd[1],&w,sizeof(w));
				if(res<0)
				{
					perror("Blad zapisu");
					exit(i);
				}
				close(fd[1]);
				exit(i);
			}
	}
	close(fd[1]);
	struct wynik wyn;
	for(i=0;i<N;i++)
	{
		res=read(fd[0],&wyn,sizeof(wyn));
		if(res<0)
		{
			perror("Blad odczytu");
			exit(1);
		}
		suma=suma+wyn.ile;
		printf("Poczatek: %d Koniec: %d Ilosc: %d\n",wyn.pocz,wyn.kon,wyn.ile);
	}
	time(&tstop);
	printf("Znaleziono %d liczb pierwszych\n", suma);
	int time = tstop - tstart;
	printf("Czas obliczen: %d sekund\n", time);
	close(fd[0]);
	return 0;	
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
