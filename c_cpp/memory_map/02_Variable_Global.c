/*	Ejemplo #2
	Uso de una variable global, de tipo double

	size archivo.bin

	El bss aumenta 8 bytes. Esto es correcto puesto que la variable global no 
	está inicializada, y una variable de tipo double en C ocupa 8 bytes en 
	memoria.

*/
	
#include <stdio.h>
double numero;
 
int main(){
    return 0;
}
