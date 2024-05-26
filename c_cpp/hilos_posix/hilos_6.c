// EJEMPLO NRO. 6
// Compilar con -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUMERO_DE_HILOS 3
#define TAM 15

// Esta función imprime el identificador del hilo y después termina
void *imprimir(void *tid)
{
	printf("¡Hola mundo!, saludos del hilo #%d con ID: %d\n", tid, pthread_self());
	pthread_exit(NULL);
}

// Esta funcion permite capturar datos desde el teclado
void *leer(void *datos)
{
	printf("Soy el hilo %d, y te pido que ingreses tu nombre: \n", pthread_self());
	scanf("%s", datos);
	pthread_exit(datos);
}

// El programa principal crea varios hilos y después termina
int main(int argc, char *argv[])
{
	pthread_t hilos[NUMERO_DE_HILOS];
	pthread_t hilo_teclado;
	
	int estado, i;
	char datos[TAM];
	
	pthread_create(&hilo_teclado, NULL, leer, (void *)datos);
		
	for(i=0; i < NUMERO_DE_HILOS; i++) 
	{
		sleep(1);
		printf("Aqui MAIN, creando el hilo #%d \n", i);
		estado = pthread_create(&hilos[i], NULL, imprimir, (void *)i);
		if (estado != 0) 
		{
			printf("Ups!!! pthread_create devolvió el codigo de error %d", estado);
			exit(-1);
		}
	}
	
	// Esperar a que el hilo de lectura de teclado termine
	pthread_join(hilo_teclado, NULL);
	printf("El texto ingresado es: «%s». FIN", datos);
	return 0;
}
