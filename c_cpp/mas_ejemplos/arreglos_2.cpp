/* Arreglos en C++
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(){

    // Declaración de variables
    int horas[5][4];
    int c, f;
    int total = 0, ts = 0;

    cout << "\n Ingresar las horas trabajadas dia a dia por un empleado\n\n";

    for(f = 0; f < 4; f++){
        for(c = 0; c < 5; c++){
            cout << "Horas trabajadas el día " << c + 1 << " semana " << f + 1 << ": ";
            cin >> horas[c][f];
            total = total + horas [c][f];
        }
    }

    cout << "\n Horas trabajadas por el empleado\n\n";
    cout << "\n \t Lu \t Ma \t Mi \t Ju \t Vi \n\n";

    for(f = 0; f < 4; f++){
        for(c = 0; c < 5; c++){
            cout << "\t " << horas[c][f];
            ts = ts + horas [c][f];
        }
        cout << "   T: " << ts << endl << endl << endl;
        ts = 0;
    }
    cout << "\n Total de horas trabajadas: " << total << endl << endl;
    system("pause"); // Sólo para M$ Windows
}
