// ejemplo que toma dos numeros, los suma y muestra el resultado
Algoritmo  Suma
    Definir A,B,C como Real;
    // para cargar un dato, se le muestra un mensaje al usuario
    // con la instrucción Escribir, y luego se lee el dato en 
    // una variable (A para el primero, B para el segundo) con 
    // la instrucción Leer
    Escribir "Ingrese el primer numero:"; //presionar la tecla ENTER para cargar
    Leer A;
    Escribir "Ingrese el segundo numero:"; //presionar la tecla ENTER para cargar
    Leer B;
    // ahora se calcula la suma y se guarda el resultado en la
    // variable C mediante la asignación (<-)
    C <- A+B;
    // finalmente, se muestra el resultado, precedido de un 
    // mensaje para avisar al usuario, todo en una sola
    // instrucción Escribir
    Escribir "El resultado es: ",C;
FinAlgoritmo