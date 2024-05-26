# Simulador de dados
# Cada vez que ejecutamos el programa, este elegirá dos números aleatorios
# entre el 1 y el 6. El programa deberá imprimirlos en pantalla, imprimir 
# su suma y preguntarle al usuario si quiere tirar los dados otra vez.

import random

def dados():
    dado1 = random.choice([1,2,3,4,5,6])
    dado2 = random.choice([1,2,3,4,5,6])
    print("Dado Nro. 1: ", dado1)
    print("Dado Nro. 2: ", dado2)
    return dado1 + dado2

print("Juego de datos - Lucas Martín Treser")
opcion = "SI"

while opcion == "SI":
    puntos = dados()
    print("Puntos obtenidos: ", puntos)
    print("-----")
    opcion = input("Escriba SI para tirar nuevamente o NO para salir: ")