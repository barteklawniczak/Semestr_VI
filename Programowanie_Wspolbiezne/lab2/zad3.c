#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
        char buffer[50];        //bufor dla funkcji sprintf
        int i, process, pid, status, K = argc-2;
        //K - ile procesow potomnych mamy utworzyc
        for(i=0; i<K; i++)
        {
                if(fork()==0)
                {
                        sprintf(buffer, "./pot %d %d", i+1, atoi(argv[i+2]));
                        system(buffer);
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


