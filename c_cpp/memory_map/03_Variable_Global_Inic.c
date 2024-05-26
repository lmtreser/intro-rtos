/*	Ejemplo #3
	Uso de una variable global, de tipo double, inicializada.

	size archivo.bin

	Se redujo en 8 bytes el bss, ya no tenemos esa variable no inicializada. 
	Sin embargo, se incrementó en 8 bytes el segmento de datos inicializados.

*/
	
#include <stdio.h>
double numero = 123;
 
int main(){
    return 0;
}
