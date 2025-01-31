/*
  Primeros pasos con C++ (2)
*/

#include <iostream>

using namespace std;

int main()
{
    string datos;

    for (int i = 0; i < 10; i++)
    {
        cout << "** SISTEMA DE INGRESOS \n";
        cout << "Escribe YES para salir \n";
        cout << "El valor de i es: " << i << "\n";
        cout << ">";
        cin >> datos;
        if (datos == "YES")
        {
            cout << "-- SALIÓ DEL SISTEMA -- " << endl;
            break;
        }
    }
}