#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int i, j, pid, status, K = argc-2;
	//K - ile procesow potomnych mamy utworzyc
	for(i=0; i<K; i++)
	{
		if(fork()==0)
		{
			for(j=0; j<atoi(argv[i+2]); j++)
			{
				printf("Potomny %d krok %d\n", i+1, j+1);
				sleep(1);
			}
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
