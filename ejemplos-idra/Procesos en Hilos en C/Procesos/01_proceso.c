// Un simple proceso que muestra un mensaje en pantalla

#include <stdio.h>
#include <unistd.h>

int main(void)
{
	while(1)
	{
		int pid = getpid();
		printf("Soy el proceso --Hola Mundo-- con pid: %d\n", pid);
		sleep(3);
	}
}
