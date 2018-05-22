#include <sys/mman.h> 
#include <fcntl.h> 
#include <semaphore.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 

#define BSIZE     4   // Rozmiar bufora 
#define LSIZE    80   //  Dlugosc linii 
typedef struct { 
    char buf[BSIZE][LSIZE]; 
    int head; 
    int tail; 
    int cnt; 
    sem_t mutex; 
    sem_t empty; 
    sem_t full; 
} bufor_t; 

int main(int argc,char *argv[]) { 
	int i,stat,k, pid, size, fd,res, nr, kroki; 
 	bufor_t  *wbuf;

	nr=atoi(argv[1]);
	kroki=atoi(argv[2]);
	
	fd = shm_open("bufor", O_RDWR | O_CREAT , 0774); 
 	if(fd == -1){ 
   		perror("open"); _exit(-1); 
 	}

	wbuf = (bufor_t*)mmap(0,sizeof(bufor_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if(wbuf == NULL) {
		perror("map"); _exit(-1); 
	}

	for(i=0; i<kroki; i++)
	{
		printf("Konsument nr %d, odebrano %s\n", nr, wbuf->buf[wbuf->tail]);
		sem_wait(&(wbuf->full));
		sem_wait(&(wbuf->mutex));
//		sprintf(wbuf->buf[wbuf->head], "Konsument nr %d, krok %d", nr, i);
		wbuf->cnt--;
		wbuf->tail = (wbuf->tail+1) % BSIZE;
		sem_post(&(wbuf->mutex));
		sem_post(&(wbuf->empty));
	}
	return(0);
}
