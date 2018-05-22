#include <stdio.h>
#include <mqueue.h>

struct { 
    int nr;        // numer przedzialu i 
    int pocz;      // poczatek zakresu obliczen Zd(i) 
    int kon;       // koniec zakresu obliczen Zg(i)
    int liczb;     // ile liczb pierwszych w przedziale 
} ms_type; 

void main(int argc, char *argv[])
{
	mqd_t mq, mqq;
	struct mq_attr attr;
	attr.mq_msgsize = sizeof(ms_type);
	attr.mq_maxmsg=6;
	attr.mq_flags=0;
    mq_unlink("/Kolejkaa");
	mq_unlink("/Wyjsciowa");
	mq=mq_open("/Kolejkaa", O_RDWR | O_CREAT, 0660, &attr);
	mqq=mq_open("/Wyjsciowa", O_RDWR | O_CREAT, 0660, &attr);
	if(mq<0 || mqq < 0)
	{
		perror("Kolejka nie zostala utworzona");
	}
	mq_close(mq);
}
