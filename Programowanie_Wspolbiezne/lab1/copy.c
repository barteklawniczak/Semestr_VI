#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#define wlk 512

int main(int argc, char *argv[]) {
  if(argc!=3)
  {
	printf("Zla liczba argumentow");
	exit(0);
  }

  int rd = open(argv[1], O_RDONLY);
  if(rd<0)
  {
	perror("blad otwarcia pliku1");
	exit(0);
  }
  int wr = open(argv[2], O_WRONLY);
  if(wr<0)
  {
	perror("blad otwarcia pliku2");
	exit(0);
  }
  int rd2;
  char buf[wlk];
  do {
        rd2 = read(rd,buf,wlk);
	write(wr,buf,rd2);
        
  } while (rd2 > 0);
  close(rd);
  close(wr);
return 0;
}
