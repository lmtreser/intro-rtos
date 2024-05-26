# CREAR Y LEER ARCHIVOS
#
# open – Abre un archivo para leer (r) o escribir (w)
# write – Escribe un texto en el archivo
# read – Lee el archivo completo
# readline – Lee una línea del archivo

import os

objeto_archivo = open("archivo.dat", "w")

# Escribir información en un archivo, este método devuelve la
# cantidad de bytes que se almacenaron cada vez que se invoca
objeto_archivo.write("Texto")
objeto_archivo.write("3")

# Al terminar de guardar datos en el archivo debemos cerrarlo
objeto_archivo.close()

# El modo "a" (append) abre el archivo para agregar datos al final
# sin borrar el contenido anterior. Si el archivo no existe, lo crea 
# y agrega los datos
objeto_archivo = open("datos.dat","a")
objeto_archivo.write("Texto")

# Leer el contenido de un archivo con el método read
objeto_archivo = open("archivo.dat", "r")
objeto_archivo.read()

# El método read() permite especificar la cantidad de caracteres a leer
objeto_archivo = open("archivo.dat", "r")
objeto_archivo.read(3)

# readline() permite leer una línea de un archivo, hasta el caracter "\n"
objeto_archivo = open("archivo.dat", "r")
objeto_archivo.readline()
