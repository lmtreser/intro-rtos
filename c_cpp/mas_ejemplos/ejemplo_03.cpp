/*
  Primeros pasos con C++ (3)
*/

#include <iostream>

using namespace std;

int main()
{
    string datos;
    cout << "Ingrese su nombre: ";
    getline(cin, datos);
    
    cout << "Su nombre es: " << datos << endl;
    cout << "END \n";
}