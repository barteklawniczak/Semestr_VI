#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <mqueue.h>
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

struct ms_type{ 
    int nr;        // numer przedzialu i 
    int pocz;      // poczatek zakresu obliczen Zd(i) 
    int kon;       // koniec zakresu obliczen Zg(i)
    int liczb;     // ile liczb pierwszych w przedziale 
}ms_type; 

int main(int argc, char *argv[])
{
	struct wynik w;
	unsigned int prior;
	int pid, status, i, pocz, kon, N, last, fdwej,fd_read,fd,res, 	suma=0,przedzial,pocz2,kon2,licznik=0;
	pocz2 = atoi(argv[1]);
	kon2 = atoi(argv[2]);
	N = atoi(argv[3]);
		mqd_t mq, mqq;
	przedzial = atoi(argv[4]);
	char buffer1[10], buffer2[10], buffer3[10];

	int ilosc = kon2/przedzial;
	mq=mq_open("/Kolejkaa", O_RDWR, 0660, NULL);	
	mqq=mq_open("/Wyjsciowa", O_RDWR, 0660, NULL);
	if(mq<0 || mqq<0)
	{
		perror("mq_open");
		exit(0);
	}	

	printf("Zrobione %d ilosc\n", ilosc);
	for(i=0;i<ilosc;i++)
	{
			pocz=(i*przedzial)+pocz2;
			kon = ((i+1)*przedzial)+pocz2-1;
			if(kon>kon2){kon=kon2;}
			struct ms_type o;
			o.pocz = pocz;
			o.kon = kon;
			o.nr = licznik++;
			mq_send(mq, (const char *)&o, sizeof(o), 10);
	}
	time_t tstart, tstop;

	time(&tstart);
	for(i=0; i<N; i++)
	{
		if(fork() == 0)
		{
			execl("./licz3", "licz3", NULL);
			exit(i+1);
		}
	}

    suma =0;
	for(i=0; i<5; i++)	//5 przyjete z gory
	{
		res = mq_receive(mqq, (char *)&ms_type, sizeof(ms_type), &prior);
        if(res < 0) {
            perror("rec");
        }
		suma += ms_type.liczb;
	}

	for(i=0; i<N; i++)
	{
		pid = wait(&status);
//		printf("Proces %d zakończony status: %d\n", pid, status);
	}
	time(&tstop);
	
/*    suma = 0;
	for(i=0; i<N; i++)
	{
        printf("Poczatek: %d Koniec: %d Ilosc: %d\n",w.pocz,w.kon,w.ile);
		if(res<0)
		{
			perror("Blad odczytu");
			exit(0);
		}
		suma = suma + w.ile;
	}*/

	printf("Znaleziono %d liczb pierwszych\n", suma);
	int time = tstop - tstart;
	printf("Czas obliczen: %d sekund\n", time);
	return 0;
}
