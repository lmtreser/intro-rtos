// EJEMPLO NRO. 1
// Para poder utilizar la interfaz de los hilos es necesario incluir la 
// cabecera pthread.h y compilar con -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* thread_run(void* data)
{ 
	sleep(2); 
	printf("[TH_1:%ld]: Hello from the thread \n", pthread_self());
	sleep(1);
	(*(int*)data)++;
	printf("[TH_1: %ld]: To exit...............\n",pthread_self());
	pthread_exit(data);
}

int main()
{
	pthread_t thread;
	int data=0;
	int thread_rc;
	printf("[MAIN:%ld]: Starting............ \n",pthread_self());
	
	/* La creación de un hilo se hace mediante pthread_create. A partir de este 
	punto, si la función no produce error, hay dos hilos de ejecución: el del 
	programa invocante y otro cuyo nombre de función se pasa por parámetro y en 
	nuestro caso se corresponde con thread_run. Dicha función recibe un puntero 
	a datos y devuelve otro. Típicamente, el hilo invocante usa el último 
	parametro de hilo para enviar datos de entrada al nuevo hilo. 
	*/
	if ((thread_rc=pthread_create(&thread,NULL,thread_run,&data))!=0)
	{
		printf("Error creating the thread. Code %i",thread_rc);
		return -1;
	}
	sleep(1);
	printf("[MAIN:%ld]: Thread allocated \n",pthread_self());
	int *ptr_output_data;
	/* El resultado del hilo se devuelve cuando la función con la que se crea 
	el hilo finaliza. El hilo devuelve un puntero cuyos resultados se pueden 
	recoger, más tarde, con pthread_join desde el hilo padre que lo ha creado. 
	*/
	pthread_join(thread,(void **)&ptr_output_data);
	printf("[MAIN:%ld]: Thread returns %d \n",pthread_self(), *ptr_output_data);
	return 0;
} 
