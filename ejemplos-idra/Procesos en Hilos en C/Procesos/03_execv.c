/* Procesos con fork() y execv() */

#include <stdio.h>
#include <unistd.h>

int main(void)
{
	
	int pid = fork();
	
	// instrucciones que tanto el padre como el hijo haran
	while(1) 
	{
		if (pid != 0)
		{
			// instrucciones que solo el proceso padre hara
			printf("Proceso --Padre-- con pid: %d\n", getpid());
		}
		else
		{
			// instrucciones que solo el proceso hijo hara
			printf("Proceso --Hijo-- con pid: %d\n", getpid());
			printf("Cambiando la imagen de proceso...\n");
						
			char *args[]={"./proceso.bin",NULL};
			execv(args[0],args);
			
			/* Instrucciones ignoradas después de la llamada a execv() */
			printf("Finalizando...\n");
		}
		sleep(2);
	}
}
