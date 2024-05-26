/*	Ejemplo #7
	
	Al compilar y analizar la salida del comando size veremos lo siguiente:

	text 	data	bss		
	1355	82536	8
	
	El comando size nos muestra que los 80 KiB que antes estaban en el 
	segmento bss ahora han pasado al segmento de datos inicializados.
	
	La salida de pmap muestra que ahora el segmento ya no es anónimo, ha 
	pasado a datos inicializados, y se sumó a los 4 KiB que ya teníamos ahí.

*/
	
#include <stdio.h>

char cadena[8192*10] = "hola";

int main(){
	getchar();
	return 0;
}
