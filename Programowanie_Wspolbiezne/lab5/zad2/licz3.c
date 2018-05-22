#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>

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

struct ms_type{ 
    int nr;        // numer przedzialu i 
    int pocz;      // poczatek zakresu obliczen Zd(i) 
    int kon;       // koniec zakresu obliczen Zg(i)
    int liczb;     // ile liczb pierwszych w przedziale 
}ms_type; 

int main(int argc, char *argv[])
{
	struct wynik w;
	int badanie;
	mqd_t mq, mqq;
	unsigned int prior;
	int i, j, pocz, kon, res, licznik=0;
	mq=mq_open("/Kolejkaa", O_RDWR, 0660, NULL);
	mqq=mq_open("/Wyjsciowa", O_RDWR, 0660, NULL);
	if(mq<0 || mqq < 0)
	{
		perror("mq_open");
		exit(0);
	}
	struct ms_type o;
	for(i=0; i<5; i++)	//100 przyjete z gory
	{
		res = mq_receive(mq, (char *)&ms_type, sizeof(ms_type), &prior);
        if(res < 0) {
            perror("rec");
        }
		for(i=ms_type.pocz; i<=ms_type.kon; i++)
		{
			badanie = pierwsza(i);
	
			if(badanie == 1)
			{
				licznik++;
			}
		}
        printf("pocz %d kon %d wynik %d\n",ms_type.pocz,ms_type.kon,licznik);
		o.nr = ms_type.nr;
		o.pocz = ms_type.pocz;
		o.kon = ms_type.kon;
		o.liczb = licznik;
		mq_send(mqq, (const char *)&o, sizeof(o), 10);
	}
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
