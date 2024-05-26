/*	Ejemplo #5
	Uso de una variable estática inicializada.

	size archivo.bin

	Si la inicializamos, ahora el espacio vuelve a ser consumido en el 
	segmento de datos inicializados: 8 bytes en bss y 560 bytes en data.

*/
	
#include <stdio.h>
double numero = 123;
 
int main(){
	static double otra_var = 321;
    return 0;
}
