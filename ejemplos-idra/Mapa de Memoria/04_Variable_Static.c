/*	Ejemplo #4
	Uso de una variable estática.

	size archivo.bin

	Debería incrementarse el tamaño del bss: en este caso a 16 bytes.

*/
	
#include <stdio.h>
double numero = 123;
 
int main(){
	static double otra_var;
    return 0;
}
