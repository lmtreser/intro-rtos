/* Programacion con Hilos

 Para poder utilizar la interfaz de los hilos es necesario incluir el 
 archivo de cabecera "pthread.h" y compilar con la opcion "-lpthread".
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Funcion que ejecutara el hilo
void* thread_run(void* data)
{ 
	sleep(2); 
	printf("[TH_1: %ld PID:%d]: Soy el hilo \n", pthread_self(), getpid());
	sleep(1);
	(*(int*)data)++;
	printf("[TH_1: %ld PID:%d]: Finalizando...............\n", pthread_self(),
		   getpid());
	pthread_exit(data);
}

int main()
{
	
	int data=0;
	int thread_rc;
	
	pthread_t thread;
	printf("[MAIN: %ld PID:%d]: Iniciando...............\n", pthread_self(), getpid());
	
	/* La creación de un hilo se hace mediante pthread_create. A partir de este 
	punto, si la función no produce error, hay dos hilos de ejecución: el del 
	programa invocante y otro cuyo nombre de función se pasa por parámetro y en 
	nuestro caso se corresponde con thread_run. Dicha función recibe un puntero 
	a datos y devuelve otro. Típicamente, el hilo invocante usa el último 
	parametro de hilo para enviar datos de entrada al nuevo hilo. 
	*/
	if ((thread_rc = pthread_create(&thread, NULL, thread_run, &data)) != 0)
	{
		printf("Error al crear el hilo. Codigo %i", thread_rc);
		return -1;
	}
	
	sleep(1);
	printf("[MAIN: %ld PID:%d]: Hilo asignado \n",pthread_self(), getpid());
	int *ptr_output_data;
	/* El resultado del hilo se devuelve cuando la función con la que se crea 
	el hilo finaliza. El hilo devuelve un puntero cuyos resultados se pueden 
	recoger, más tarde, con pthread_join desde el hilo padre que lo ha creado. 
	*/
	
	pthread_join(thread,(void **)&ptr_output_data);
	printf("[MAIN: %ld PID:%d]: El hilo retorno: %d \n", pthread_self(), 
		   getpid(), *ptr_output_data);
	return 0;
} 

