 #include <arpa/inet.h> 
 #include <netinet/in.h> 
 #include <stdio.h> 
 #include <sys/types.h> 
 #include <sys/socket.h> 
 #include <unistd.h> 
 #include <string.h> 
#include <sys/stat.h>
#include <fcntl.h>

#define OPENR  1  // Otwarcie pliku do odczytu 
#define OPENW  2  // Otwarcie pliku do zapisu 
#define READ   3  // Odczyt fragmentu pliku 
#define CLOSE  4  // Zamkniecie pliku 
#define WRITE  5  // Zapis fragmentu pliku 
#define STOP  10  // Zatrzymanie serwera 
#define PORT 9952
#define SIZE 512
 #define BUFLEN 80 
typedef struct  { 
    int  typ;       // typ zlecenia 
    int  ile;       // liczba bajtow 
    int  fh;        // uchwyt pliku 
    char buf[SIZE]; // bufor 
} mms_t; 

  void blad(char *s) {
     perror(s);
     _exit(1);
   }

/* read_file(mms_t * msg, char * filename)
{
	msg->typ = OPENR;
	sprintf(msg->buf, "%s", filename);
	int send;
	send=sendto(s, msg, blen, 0,(struct sockaddr *)&adr_serw,(socklen_t) slen);
	if(send < 0) blad("sendto()");
	rec = recvfrom(s, msg, blen, 0,(struct sockaddr *) &adr_x,(socklen_t *) &slen);
        if(rec < 0) blad("recvfrom()");

	do{

		msg->typ=READ;
		send=sendto(s, msg, blen, 0,(struct sockaddr *)&adr_serw,(socklen_t) slen);
		if(send<0)blad("sendto");
		
		send=recvfrom(s, msg, blen, 0,(struct sockaddr *) &adr_x,(socklen_t *) &slen);	
		if(send<0)blad("recvfrom");
		else
			printf("%s\n", msg->buf);
	}while(msg->ile>0)
}*/

int main(int argc, char * argv[]) {
   struct sockaddr_in adr_moj, adr_serw, adr_x;    
   mms_t msg;
   int s, i, slen=sizeof(adr_serw), snd, blen=sizeof(mms_t),rec, wybor;
   char buf[BUFLEN];
   char name[100], name_sv[100];	
   s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
   if(s < 0) blad("socket");
   printf("Gniazdko %d utworzone\n",s);
   
   memset((char *) &adr_serw, 0, sizeof(adr_serw));
   adr_serw.sin_family = AF_INET;
   adr_serw.sin_port = htons(PORT);
   if (inet_aton(argv[1], &adr_serw.sin_addr)==0) {
        fprintf(stderr, "inet_aton() failed\n");
        _exit(1);
   }
	
   printf("Dokonaj wyboru:\n1. Czytaj z pliku\n2. Pisz do pliku\n3. Czytaj plik\n");
   scanf("%d", &wybor);

   switch(wybor)
   {
		case 1:{
			printf("Podaj nazwę pliku\n");
			scanf("%s", name);
			msg.typ = OPENR;
			sprintf(msg.buf, "%s", name);
			int send;
			send=sendto(s, &msg, blen, 0,(struct sockaddr *)&adr_serw,(socklen_t) slen);
			if(send < 0) blad("sendto()");
			rec = recvfrom(s, &msg, blen, 0,(struct sockaddr *) &adr_x,(socklen_t *) &slen);
        		if(rec < 0) blad("recvfrom()");

			do{

				msg.typ=READ;
				send=sendto(s, &msg, blen, 0,(struct sockaddr *)&adr_serw,(socklen_t) slen);
				if(send<0)blad("sendto");
		
				send=recvfrom(s, &msg, blen, 0,(struct sockaddr *) &adr_x,(socklen_t *) &slen);	
				if(send<0)blad("recvfrom");
				else
					printf("%s\n", msg.buf);

			}while(msg.ile>0);
			break;}
		case 2:
			{
				printf("Podaj nazwę pliku\n");
				scanf("%s", name);
				printf("Podaj nazwę pliku na serwerze\n");
				scanf("%s", name_sv);
				int fh, send;
				fh = open(name, O_RDONLY);
				if(fh<0)blad("open");
				sprintf(msg.buf, "%s", name_sv);
				msg.typ = OPENW;
				send = sendto(s, &msg, blen, 0,(struct sockaddr *)&adr_serw,(socklen_t) slen);
				if(send<0)blad("sendto");		
				send=recvfrom(s, &msg, blen, 0,(struct sockaddr *) &adr_x,(socklen_t *) &slen);	
				if(send<0)blad("recvfrom");

				do{
					msg.typ=WRITE;
					msg.ile=read(fh, msg.buf, SIZE);
					if(msg.ile<0)blad("read");

					send = sendto(s, &msg, blen, 0,(struct sockaddr *)&adr_serw,(socklen_t) slen);
					if(send<0)blad("sendto");		
					send=recvfrom(s, &msg, blen, 0,(struct sockaddr *) &adr_x,(socklen_t *) &slen);	
					if(send<0)blad("recvfrom");
					
				}while(msg.ile>0);
			}
			break;
		case 3:
			break;
		default:
			printf("default");
			break;
   }	
}
