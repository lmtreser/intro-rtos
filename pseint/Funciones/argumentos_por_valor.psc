// Pasaje de argumentos por valor 

Funcion Suma (numero1,  numero2)
	numero1 <- numero1 + 1;
	numero2 <- numero2 + 1;
	Escribir "El contenido de numero1 es ", numero1;
	Escribir "El contenido de numero2 es ", numero2;
FinFuncion

Algoritmo Sumando
	
	Definir dato1, dato2 Como Entero;
	dato1 <- 3;
	dato2 <- 5;
	
	Suma(dato1, dato2);
	
	Escribir "El contenido de dato1 es ", dato1;
	Escribir "El contenido de dato2 es ", dato2;
	
FinAlgoritmo