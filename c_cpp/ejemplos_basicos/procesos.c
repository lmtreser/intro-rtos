/*	Ejemplo #8
	Creaci�n de Procesos en C - Uso de fork()
*/
		
#include <unistd.h>			// Access to the POSIX operating system API
#include <stdio.h>			// Standard Input Output Header
#include <sys/types.h>

// Funci�n principal
int main(void)
{
	pid_t idHijo;
	pid_t idPropio;
	
	idPropio = getpid(); // Se obtiene el ID del proceso actual
	idHijo = fork(); // Se crea un proceso hijo
	
	if (idHijo == -1) { // Si hay un c�digo menor que cero, hubo un error
		printf("Error al realizar la llamada a fork()");
		return 1; // Se interrumpe la ejecuci�n del proceso con una salida distinta a cero
	} 
	
	if (idHijo == 0) // La ejecuci�n de la llamada al sistema fork devuelve un cero al proceso hijo
	{	
		printf("Soy el hijo con id: %ld - id proceso original: %ld\n", (long)getpid(), (long)idPropio); 
		printf("Voy a ejecutar la herramienta date:\n");
		char *args[] = {"-d now", (char *) 0 };
		execv("/bin/date", args);
	}
	else // La ejecuci�n de la llamada al sistema fork devuelve el identificador al proceso padre
	{	
		printf("Soy el padre con id: %ld - id proceso original: %ld\n", (long)getpid(), (long)idPropio); 
	}

	return 0; 

}
