/*	Ejemplo #6
	Pmap es una buena forma de leer el mapa de memoria completo. Tiene varios 
	modificadores y niveles de verbosidad en la salida, veremos algo simple 
	para orientarnos.

	Al compilar y analizar la salida del comando size veremos lo siguiente:

	text 	data	bss		
	1355	600		81952

	El segmento de datos no inicializados (bss) contiene 80 KiB de datos, 
	el arreglo del 80 KiB definido de manera global.

	Si ejecutamos el código éste se detendrá en la penúltima línea, getchar(), 
	esperando que presionemos una tecla. Si lo dejamos corriendo y en otra 
	terminal ejecutamos el comando pmap pasando por argumento el PID de nuestro 
	ejecutable, veremos lo siguiente:
	
	pmap -x pid

	La línea marcada como [anon] indica una región definida como anónima 
	(mapeo anónimo). Se llama anónima a la memoria mapeada no asociada a 
	archivos en el disco. En este caso indica que tenemos un mapeo anónimo de 
	80 KiB.

	Las columnas representan lo siguiente:

	Address: la dirección de inicio de la posición de memoria en cuestión.
	Kbytes: tamaño de esa región en KiB.
	RSS: Resident set size, parte de la memoria realmente en RAM.
	Dirty: estado de las páginas de memoria.
	Mode: permisos de acceso a esa región de memoria por parte del proceso.
	Mapping: el nombre de la app o librería asociada a esa región de memoria.

*/
	
#include <stdio.h>

char cadena[8192*10];

int main(){
	getchar();
	return 0;
}
