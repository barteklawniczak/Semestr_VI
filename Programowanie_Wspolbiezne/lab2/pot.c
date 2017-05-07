#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int i;
	for(i=0; i<atoi(argv[2]); i++)
	{
		printf("Potomny %d krok %d\n", atoi(argv[1]), i+1);
		sleep(1);
	}
	return atoi(argv[1]);
}
