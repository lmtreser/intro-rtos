// EJEMPLO NRO. 4
// Compilar con -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_IT 19000000

int a;

void * hilo( void *arg)
{
	int id, i , aux;
	id = (int) arg;
	printf("Soy el hilo %d con identificador %d. \n", id , pthread_self() );
	for (i=0; i < NUM_IT; i++)
	{
		if ( id == 0 ){
			aux = a; 
			aux++; 
			a = aux;
		} 
		else 
		{
			aux = a; 
			aux--; 
			a=aux;
		}
		pthread_exit(0); /* Opcional */
	}
}

int main( void ) 
{
	pthread_t t1, t2 , t3;
	printf("Valor inicial de a: %d. \n", a);
	pthread_create( &t1, NULL, hilo, (void *) 0 );
	pthread_create( &t2, NULL, hilo , (void *) 1);
	pthread_create( &t3, NULL, hilo, (void *) 2);
	printf("Esperando que terminen los hilos. \n");
	pthread_join(t1, NULL);
	pthread_join(t2,NULL);
	pthread_join(t3, NULL);
	printf("Hilos terminados. Valor de a: %d. \n", a);
	return 0;
}
