/*	Ejemplo #6
	Pmap es una buena forma de leer el mapa de memoria completo. Tiene varios 
	modificadores y niveles de verbosidad en la salida, veremos algo simple 
	para orientarnos.

	Al compilar y analizar la salida del comando size veremos lo siguiente:

	text 	data	bss		
	1355	600		81952

	El segmento de datos no inicializados (bss) contiene 80 KiB de datos, 
	el arreglo del 80 KiB definido de manera global.

	Si ejecutamos el c�digo �ste se detendr� en la pen�ltima l�nea, getchar(), 
	esperando que presionemos una tecla. Si lo dejamos corriendo y en otra 
	terminal ejecutamos el comando pmap pasando por argumento el PID de nuestro 
	ejecutable, veremos lo siguiente:
	
	pmap -x pid

	La l�nea marcada como [anon] indica una regi�n definida como an�nima 
	(mapeo an�nimo). Se llama an�nima a la memoria mapeada no asociada a 
	archivos en el disco. En este caso indica que tenemos un mapeo an�nimo de 
	80 KiB.

	Las columnas representan lo siguiente:

	Address: la direcci�n de inicio de la posici�n de memoria en cuesti�n.
	Kbytes: tama�o de esa regi�n en KiB.
	RSS: Resident set size, parte de la memoria realmente en RAM.
	Dirty: estado de las p�ginas de memoria.
	Mode: permisos de acceso a esa regi�n de memoria por parte del proceso.
	Mapping: el nombre de la app o librer�a asociada a esa regi�n de memoria.

*/
	
#include <stdio.h>

char cadena[8192*10];

int main(){
	getchar();
	return 0;
}
