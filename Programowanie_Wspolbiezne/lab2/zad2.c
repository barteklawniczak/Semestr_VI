#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	char buffer[10];	//bufor dla funkcji sprintf
        int i, process, pid, status, K = argc-2;
        //K - ile procesow potomnych mamy utworzyc
        for(i=0; i<K; i++)
        {
                if(fork()==0)
                {
			sprintf(buffer, "%d", i+1);
			execl("./pot", "pot", buffer, argv[i+2], NULL);
			exit(i+1);
                }
        }

        for(i=0; i<atoi(argv[1]); i++)
        {
                printf("Macierzysty krok %d\n", i+1);
                sleep(1);
        }

        for(i=0; i<K; i++)
        {
                pid = wait(&status);
                printf("Proces %d zakończony status: %d\n", pid, status);
        }
        return 0;
}
