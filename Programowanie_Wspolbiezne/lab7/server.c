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

int main(){
	struct sockaddr_in adr_moj, adr_cli;
	int rec, s, i, slen=sizeof(adr_cli),snd, blen=sizeof(mms_t);
	s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	mms_t msg;
	if(s < 0) blad("socket");
   	printf("Gniazdko %d utworzone\n",s);

	memset((char *) &adr_moj, 0, sizeof(adr_moj));
	adr_moj.sin_family = AF_INET;
	adr_moj.sin_port = htons(PORT);
	adr_moj.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(s,(struct sockaddr *) &adr_moj, sizeof(adr_moj))==-1)
       		blad("bind");

	do{
		rec=recvfrom(s, &msg, blen, 0,(struct sockaddr *) &adr_cli, &slen);
		if(rec < 0) blad("recvfrom()");
		switch(msg.typ)
		{
			case OPENR:
				msg.fh=open(msg.buf, O_RDONLY);
				if(msg.fh==-1) blad("open");
				printf("Otworzono plik %s do odczytu\n", msg.buf);
				break;
			case OPENW:
				msg.fh=open(msg.buf, O_WRONLY|O_CREAT, S_IRWXU|S_IRWXG|S_IRWXO);
				if(msg.fh==-1) blad("write");
				printf("Otworzono plik %s do zapisu\n", msg.buf);
				break;
			case READ:
				msg.ile=read(msg.fh, msg.buf, SIZE);
				if(msg.ile==-1) blad("read");
				printf("Czytanie pliku\n");
				break;
			case WRITE:
				msg.ile=write(msg.fh,msg.buf, msg.ile);
				if(msg.ile==-1) blad("write");
				printf("Zapis do pliku\n");
				break;
			default:
				printf("DEFAULT");
				break;
		}
					
	rec=sendto(s, &msg,  blen, 0,(struct sockaddr *) &adr_cli, slen);
	if(rec==-1) blad("sendto");
	}while(1);

	close(s);
}


