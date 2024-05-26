// EJEMPLO NRO. 5
// Compilar con -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUMERO_DE_HILOS 10

// Esta función imprime el identificador del hilo y después termina
void *imprimir_hola_mundo(void *tid)
{
	printf("¡Hola mundo!, saludos del hilo: %d\n", tid);
	pthread_exit(NULL);
}

// El programa principal crea 10 hilos y después termina
int main(int argc, char *argv[])
{
	pthread_t hilos[NUMERO_DE_HILOS];
	int estado, i;
	for(i=0; i < NUMERO_DE_HILOS; i++) 
	{
		printf("Aqui MAIN, creando el hilo nro.: %d\n", i);
		estado = pthread_create(&hilos[i], NULL, imprimir_hola_mundo, (void *)i);
		if (estado != 0) 
		{
			printf("Ups!!! pthread_create devolvió el codigo de error %d", estado);
			exit(-1);
		}
	}
	return 0;
}
