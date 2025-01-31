/*
  Primeros pasos con C++ (1)
*/

#include <iostream>
using namespace std; // nombre de espacio std, para evitar std::cout por ejemplo

int main()
{
  int num = 0;

  while (num < 10)
  {
    cout << "Ingrese un número: ";
    cin >> num; // ingresa un número entero
    cout << "Usted ingresó: " << num << endl;
  }
  printf("** Fin de programa ** \n");
  return 0;
}