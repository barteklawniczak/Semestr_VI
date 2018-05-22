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

struct odcinek{
   int pocz;  // Początek przedziału 
   int kon;   // Koniec przedziału 
   int numer; // Kolejny numer odcinka 
};

int main(int argc, char *argv[])
{
	struct wynik w;
	int pid, status, i, pocz, kon, N, last, fdwej,fd_read,fd,res, suma=0,przedzial,pocz2,kon2,licznik=0;
	pocz2 = atoi(argv[1]);
	kon2 = atoi(argv[2]);
	N = atoi(argv[3]);
	przedzial = atoi(argv[4]);
	char buffer1[10], buffer2[10], buffer3[10];
	printf("przed otworzeniem\n");
	int myFifo = mkfifo("MyFifo", 0666);
	int wejscie = mkfifo("wejscie", 0666);
	if(myFifo < 0 || wejscie <0)
	{
		perror("mkfifo");
		exit(0);
	}
	printf("po otworzeniu\n");
	fd = open("MyFifo",O_RDWR);
	fdwej = open("wejscie", O_RDWR);
	
	int ilosc = kon2/przedzial;
	printf("Zrobione %d ilosc\n", ilosc);
	for(i=0;i<ilosc;i++)
	{
			pocz=(i*przedzial)+pocz2;
			kon = ((i+1)*przedzial)+pocz2-1;
			if(kon>kon2){kon=kon2;}
			struct odcinek o;
			o.pocz = pocz;
			o.kon = kon;
			o.numer = licznik++;
			status = write(fdwej, &o, sizeof(o));
			if(status < 0)
			{
				perror("Blad zapisu");
				exit(0);
			}
	}
	time_t tstart, tstop;

	for(i=0;i<N;i++)
	{
	o.pocz = 0;
	o.kon = 0;
	o.numer = -1;
	write(fdwej, &o, sizeof(o));
	}
	time(&tstart);
	for(i=0; i<N; i++)
	{
		if(fork() == 0)
		{
			execl("./licz3", "licz3", NULL);
			exit(i+1);
		}
	}

	for(i=0; i<N; i++)
	{
		pid = wait(&status);
//		printf("Proces %d zakończony status: %d\n", pid, status);
	}
	time(&tstop);
	
    suma = 0;
	for(i=0; i<N; i++)
	{
		res = read(fd, &w, sizeof(w));
        printf("Poczatek: %d Koniec: %d Ilosc: %d\n",w.pocz,w.kon,w.ile);
		if(res<0)
		{
			perror("Blad odczytu");
			exit(0);
		}
		suma = suma + w.ile;
	}

	close(fd);
	close(fdwej);
	printf("Znaleziono %d liczb pierwszych\n", suma);
	int time = tstop - tstart;
	printf("Czas obliczen: %d sekund\n", time);
	return 0;
}
