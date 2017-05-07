#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int pid, status, i, pocz, kon, N, last;
	pocz = atoi(argv[1]);
	kon = atoi(argv[2]);
	N = atoi(argv[3]);
	double przedzial2 = (double)(kon - pocz)/N;
	int przedzial = (kon - pocz)/N;
	if(przedzial2 > przedzial)	//sprawdzenie czy przedzial dzieli sie calkowicie
	{
		przedzial++;
	}
	char buffer1[10], buffer2[10], buffer3[10];
	for(i=0; i<N; i++)
	{
		if(fork() == 0)
		{
			sprintf(buffer1, "%d", i+1);		//Nr procesu
			sprintf(buffer2, "%d", (i*przedzial)+pocz);
			last = ((i+1)*przedzial)+pocz;
			if(last>kon)
			{
				last=kon;
			}
			sprintf(buffer3, "%d", last);
			execl("./licz", "licz", buffer1, buffer2, buffer3, NULL);
			exit(i+1);
		}
	}

	for(i=0; i<N; i++)
	{
		pid = wait(&status);
		printf("Proces %d zakończony status: %d\n", pid, status);
	}

	return 0;
}
