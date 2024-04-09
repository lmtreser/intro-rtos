# Moverse dentro de un archivo
#
# Al leer un archivo (de texto o binario) se realiza desde un determinado 
# valor índice, que se pone a cero cuando se abre el archivo, indicando 
# el inicio y se va incrementando según la cantidad de caracteres o bytes
# que se lean.
#
# Si fuera necesario ubicar un punto específico dentro de un archivo, ya 
# sea hacia atrás o hacia adelante de la última lectura, es posible
# modificar este índice.
#
# tell(): Devuelve el valor del índice
# seek(offset, origen): Establece un nuevo valor para el índice
#
# Si origen = 0, se cuenta desde el inicio del archivo (offset debe ser 
# un valor positivo). Si origen = 1, se cuenta desde la posición actual 
# (offset puede ser positivo o negativo). Si origen = 2, se cuenta desde
# el final del archivo (offset debe ser negativo).

import os
archivo = open("datos.bin", "rb")
archivo.tell() # Devuelve 0 porque el índice está al comienzo del archivo
archivo.read(3)
archivo.tell() # Luego de leer 3 bytes, tell() devuelve 3 como índice
archivo.seek(1, 0) # Vuelve el índice a la posición 1
archivo.read(1)
archivo.seek(-3, 2) # Mover el índice 3 posiciones a partir del final 
