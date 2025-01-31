/*
    Ejemplo uso de arreglo de datos
*/

#include "iostream"
#include "string"
#include "stdio.h"

using namespace std;

int main()
{
    int edades[] = {1, 2, 9, 8, 16, 32, 9, 50, 36, 20, 1, 87};
    int limite = (sizeof(edades) / sizeof(edades[0]));
    for (int i = 0; i < limite; i++)
    {
        cout<< "edad:" << edades[i]<<endl;
    }
}