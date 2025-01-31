/* Uso de arreglos
*/

#include <stdlib.h>
#include <stdio.h>

int main(){

    // Variables
    float temp[24];
    float tot, prom, mayor = -20, menor = 50;
    int x, horamayor, horamenor;

    printf("\nIngrese la temperatura hora a hora\n");

    for(x = 0; x < 24; x++){
		printf("Hora %d: ", x); scanf("%f", &temp[x]); tot = tot + 
		temp[x];
    }

    prom = tot / 24;
    printf("\nPromedio de temperaturas: %.2f \n", prom);

    for(x = 0; x < 24; x++){
        if (temp[x] > mayor){
            mayor = temp[x];
            horamayor = x;
        }
    }

    printf("\nA las %d horas se produjo la temperatura más alta de %.2f grados \n", horamayor, mayor);
    printf("\n");
    system("pause"); // Sólo para M$ Windows

}
