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
	struct wynik w;
	int pid, status, i, pocz, kon, N, last, fd_read,fd,res, suma=0;
	pocz = atoi(argv[1]);
	kon = atoi(argv[2]);
	N = atoi(argv[3]);
	double przedzial2 = (double)(kon - pocz)/N;
	int przedzial = (kon - pocz)/N;
	if(przedzial2 > przedzial)	//sprawdzenie czy przedzial dzieli sie calkowicie
	{
		przedzial++;
	}
	char buffer1[10], buffer2[10], buffer3[10];

	int myFifo = mkfifo("MyFifo", 0666);
	if(myFifo < 0)
	{
		perror("mkfifo");
		exit(0);
	}
	fd = open("MyFifo",O_RDWR);
	time_t tstart, tstop;

	time(&tstart);
	for(i=0; i<N; i++)
	{
		if(fork() == 0)
		{
			sprintf(buffer1, "%d", i+1);		//Nr procesu
			sprintf(buffer2, "%d", (i*przedzial)+pocz);
			last = ((i+1)*przedzial)+pocz;
			if(last>kon)
			{
				last=kon;
			}
			else
			{
				last--;
			}
			sprintf(buffer3, "%d", last);
			execl("./licz", "licz", buffer1, buffer2, buffer3, NULL);
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
	printf("Znaleziono %d liczb pierwszych\n", suma);
	int time = tstop - tstart;
	printf("Czas obliczen: %d sekund\n", time);
	return 0;
}
