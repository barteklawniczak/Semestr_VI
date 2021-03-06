#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/mman.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <string.h> 
#include <semaphore.h> 

#define SIZE 4 //rozmiar bufora


typedef struct { 
    int pocz; 
    int kon ; 
    int suma; 
 } dane_t;

typedef struct{ 
    int typ; 
    dane_t dane[SIZE];
    int head; 
    int tail; 
    int cnt; 
    sem_t mutex; 
    sem_t empty; 
    sem_t full;  
 } buf_t; 

int pierwsza(int n) 
// Funkcja zwraca 1 gdy n jest liczbą pierwsza 0 gdy nie                               
	{ int i,j=0; 
  		for(i=2;i*i<=n;i++) { 
    		if(n%i == 0) return(0) ; 
 	} 
 return(1); 
} 

int main(int argc, char *argv[]){
	int i,j, status,k, pid, size, fd,res, nr, licznik; 
    int pocz = atoi(argv[1]);
    int kon = atoi(argv[2]);
	int przedzial = atoi(argv[3]);
	dane_t tablica[20];

	buf_t *buf; // zmienna wsaznikowa
	int  fdd; // deskryptor segmentu  

 	shm_unlink("bufor");

	fd = shm_open("bufor", O_RDWR | O_CREAT , 0774); 
 	if(fd == -1){ 
   		perror("open"); _exit(-1); 
 	} 
	printf("fd: %d\n", fd);

	size = ftruncate(fd, sizeof(buf_t));
	if(size < 0) {
		perror("trunc"); _exit(-1); 
	}

	//Odwzorowanie segmentu fd w obszar pamieci procesow
	buf = (buf_t*)mmap(0,sizeof(buf_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if(buf == NULL) {
		perror("map"); _exit(-1); 
	}

//Inicjalizacja obszaru
 	buf-> cnt = 0; 
 	buf->head = 0; 
 	buf->tail = 0; 
 	if(sem_init(&(buf->mutex),1,1)){ 
   		perror("mutex"); _exit(0);  
 	} 
 	if(sem_init(&(buf->empty),1,SIZE)) {  
   		perror("empty"); _exit(0);  
 	} 
 	if(sem_init(&(buf->full),1,0)) {  
   		perror("full"); _exit(0);  
 	}
//

	int pocz2=0, kon2=0;
	int ilosc = kon/przedzial;
	for(i=0; i<ilosc; i++)
	{
		pocz2=(i*przedzial)+pocz;
		kon2 = ((i+1)*przedzial)+pocz-1;
		if(kon>kon2){kon=kon2;}
		tablica[i].pocz = pocz2;
		tablica[i].kon = kon2;
		tablica[i].suma=i;
	}

	licznik = 0; int suma=0; int ilosc2 = ilosc;
	for(i=0;i<ilosc;i++)
	{
		nr = j; suma=0;
		if(fork()==0){
			
			int poczatek = tablica[i].pocz;
			int koniec = tablica[i].kon;
			int pom = tablica[i].suma;
			for(j=poczatek; j<koniec;j++)
				if (pierwsza(j)==1) suma++;
			sem_wait(&(buf->empty));
			sem_wait(&(buf->mutex));
			buf->dane[buf->head].pocz = poczatek;
			buf->dane[buf->head].kon = koniec;
			buf->dane[buf->head].suma = suma;
			buf->cnt++;
			buf->head = (buf->head+1) % SIZE;
			sem_post(&(buf->mutex));
			sem_post(&(buf->full));

			printf("Poczatek: %d koniec: %d suma: %d \n", poczatek, koniec, suma); 	
			exit(1);
		}
	}


	int suma_ogolna=0;
	for(i=0; i<ilosc; i++) 
	{
		sem_wait(&(buf->full));
		sem_wait(&(buf->mutex));
		suma_ogolna = suma_ogolna + buf->dane[buf->tail].suma;
		printf("w procesie numer: %d bylo %d \n", i,buf->dane[buf->tail].suma);
		buf->cnt--;
		buf->tail = (buf->tail+1) % SIZE;
		sem_post(&(buf->mutex));
		sem_post(&(buf->empty));	

	}
    	printf ("suma calkowita: %d \n",suma_ogolna);
}
