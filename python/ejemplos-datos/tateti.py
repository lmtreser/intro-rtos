#  JUEGO TA-TE-TI // LUCAS MARTÍN TRESER
print("Bienvenida/o a TA-TE-PY 1.0")
print("El layout del tablero es el siguiente:")
print("|1|2|3|")
print("|4|5|6|")
print("|7|8|9|")

jugador1 = input ("Ingrese el nombre del primer jugador: ")
jugador2 = input ("Ingrese el nombre del segundo jugador: ")
print("A", jugador1, "le tocan las X")

# variables necesarias
tabNum = [[0,0,0],[0,0,0],[0,0,0]]
tabXO = [[" "," ", " "],[" "," ", " "],[" "," ", " "]]
juego, turno = 1, 1
ganador = False
fila1, fila2, fila3 = 0, 0 , 0
columna1, columna2, columna3 = 0, 0, 0
diagonal1, diagonal2 = 0, 0
validar = [1, 2, 3, 4, 5, 6, 7, 8, 9]

def convPosicion(posicion):
   # función para convertir la posición ingresada por el usuario
   # al formato de filas y columnas.
    if posicion == 1:
        fila = 0
        columna = 0
    if posicion == 2:
        fila = 0
        columna = 1
    if posicion == 3:
        fila = 0
        columna = 2
    if posicion == 4:
        fila = 1
        columna = 0
    if posicion == 5:
        fila = 1
        columna = 1
    if posicion == 6:
        fila = 1
        columna = 2
    if posicion == 7:
        fila = 2
        columna = 0
    if posicion == 8:
        fila = 2
        columna = 1
    if posicion == 9:
        fila = 2
        columna = 2
    return fila, columna

# comienza el juego
while juego < 10:
    if turno == 1:     
        print (jugador1, "ingrese la posición: ")      
        while True:
            try:
                posicion = int(input ())
                validar.remove(posicion)
                break
            except ValueError:
                print("Posición ocupada. Intente nuevamente...")
        fila, columna = convPosicion(posicion)
        tabNum[fila][columna] = 1
        tabXO[fila][columna] = "X"
        print(tabXO[0][:]) 
        print(tabXO[1][:])
        print(tabXO[2][:])
        turno = 2
    else :    
        print (jugador2, "ingrese la posición: ")
        while True:
            try:
                posicion = int(input ())
                validar.remove(posicion)
                break
            except ValueError:
                print("Posición ocupada. Intente nuevamente...")
        fila, columna = convPosicion(posicion)
        tabNum[fila][columna] = 2
        tabXO[fila][columna] = "O"
        print(tabXO[0][:]) 
        print(tabXO[1][:])
        print(tabXO[2][:])
        turno = 1

    # calculo el resultado de la partida
    # si resultado = 1 ganan las Xs, si resultado = 8 ganan las Os  
    fila1 = tabNum[0][0] * tabNum[0][1] * tabNum[0][2]
    fila2 = tabNum[1][0] * tabNum[1][1] * tabNum[1][2]
    fila3 = tabNum[2][0] * tabNum[2][1] * tabNum[2][2]
    columna1 = tabNum[0][0] * tabNum[1][0] * tabNum[2][0]
    columna2 = tabNum[0][1] * tabNum[1][1] * tabNum[2][1]
    columna3 = tabNum[0][2] * tabNum[1][2] * tabNum[2][2]
    diagonal1 = tabNum[0][0] * tabNum[1][1] * tabNum[2][2]
    diagonal2 = tabNum[0][2] * tabNum[1][1] * tabNum[2][0]

    if (fila1 or fila2 or fila3 or columna1 or columna2 or columna3 or diagonal1 or diagonal2) == 1:
        print("Tenemos un GANADOR:", jugador1)
        ganador = True
        break

    if (fila1 or fila2 or fila3 or columna1 or columna2 or columna3 or diagonal1 or diagonal2) == 8:
        print("Tenemos un GANADOR:", jugador2)
        ganador = True
        break

    juego = juego + 1

if (ganador == False):
    print("EMPATE. Juego terminado")