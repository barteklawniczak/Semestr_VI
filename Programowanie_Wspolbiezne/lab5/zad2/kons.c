#include <stdio.h>
#include <mqueue.h>
#include <stdlib.h>
#define PROD 1
#define KONS 2

struct
{
	int type;
	int pnr;
	char text[100];
}ms_type;
 
void main(int argc, char *argv[])
{
	int i, kroki,res;
	mqd_t mq;
	unsigned int prior;
    kroki = atoi(argv[1]);
	mq=mq_open("/Kolejka", O_RDWR, 0660, NULL);
	if(mq<0)
	{
		perror("mq_open");
		exit(0);
	}
 
	for(i=0; i<kroki; i++)
	{
		res = mq_receive(mq, (char *)&ms_type, sizeof(ms_type), &prior);
        if(res < 0) {
            perror("rec");
        }
		printf("%s Odbior krok: %d\n", ms_type.text, i+1);
	}
	mq_close(mq);
}
