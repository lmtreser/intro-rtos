/* Procesos con fork()

Todo programa en ejecucion es un proceso, es decir que una vez que compilado y 
ejecutado se volvera un proceso. Dicho proceso sera creado en la memoria 
principal con los datos necesarios para su ejecucion como un apuntador a la 
instruccion a ejecutar, memoria para sus variables, etc. Usando esos datos en 
memoria, el proceso finalmente sera capaz de ejecutar las instrucciones que 
componen al programa.
	
Todos los procesos son manejados por el sistema operativo, el cual los 
diferencia entre si­ con un identificador unico de proceso, o process id (pid). 
El pid lo podemos consultar mediante la funcion getpid() de la cabecera unistd. 
Con dicha funcion podri­amos hacer que nuestro programa imprima su propio 
identificador de proceso cuando se ejecute.

Normalmente los procesos se inician al ejecutar los programas. Sin embargo, a 
veces surge la necesidad de que un proceso cree a su vez otro proceso 
independiente. Ahi­ es cuando entra la funcion fork(), que en el momento en que 
es llamada crea un clon identico del proceso que la ejecuto.

Al usar la funcion (llamada al sistema) fork() dicho proceso crea un hijo 
identico a el, por lo que ahora tanto el proceso original como el nuevo 
podran ejecutar el mismo codigo. La unica diferencia entre los dos es el 
identificador de proceso, porque, a pesar de que ambos procesos sean clones, 
el sistema operativo aun debe poder diferenciar entre ellos y por ende usa un 
pid distinto para cada uno.

Sin embargo, generalmente no tiene sentido crear un proceso que haga lo mismo 
que el padre. La gran mayoria de las veces lo que querremos es que el nuevo 
proceso realice una tarea distinta a su creador. Entonces, ¿es posible hacer 
que dos procesos no sean clones identicos para que cada uno realice una 
tarea distinta? No.

Y justamente ese es el mayor problema al que nos vamos a enfrentar al hacer uso 
de la funcion fork(). Tenemos que arreglarnoslas para que mediante un mismo 
codigo, dos procesos hagan cosas distintas. La forma de afrontar dicho problema 
es justamente la que se usa en el codigo de ejemplo: por medio de "if" ambos 
procesos comprobaran si son el proceso hijo o son el proceso padre. ¿Como se 
realiza dicha comprobacion? Pues por medio de la unica cosa diferenciable entre 
los dos procesos: su pid.

Para entender dicho "if" hay que saber un par de cosas sobre la funcion fork(): 

- Dicha funcion va a regresar un valor tanto al proceso original (padre) como 
al nuevo proceso (hijo).

- Al proceso padre le va a regresar el pid de su hijo. Al proceso hijo le va a 
regresar 0.

Sabiendo esto, nos podemos plantear que la estructura general para manejar 
procesos es la siguiente. De esta forma, aunque ambos procesos tengan el mismo 
codigo, cada uno seguira una serie de instrucciones distintas.
*/

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
			printf("Proceso padre, pid: %d\n", getpid());
		}
		else
		{
			// instrucciones que solo el proceso hijo hara
			printf("Proceso hijo, pid: %d\n", getpid());
		
		}
		sleep(2);
	}
}
