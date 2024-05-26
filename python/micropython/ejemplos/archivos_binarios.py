# Usando archivos binarios

# Un archivo de texto utiliza un byte por cada dato a guardar. 
# Por ejemplo almacenar el número "000" emplea 3 bytes, mientras 
# que en formato binario con sólo un byte alcanza.

# Abrir un archivo binario para lectura utilizando el modificador b
# archivo = open("Nombre", "rb")
archivo = open(datos.bin, "rb")

# Abrir un archivo binario para escritura
# archivo = open("Nombre", "wb")
archivo = open(datos.bin, "wb")

# Para escribir hay que usar un buffer (variable), de tipo bytearray, 
# array o string
archivo.write(bytearray([255]))

# Para escribir un valor constante se puede utilizar un string que 
# represente un número hexadecimal si anteponemos la letra "b"
# indicando que se trata de una secuencia de bytes
archivo.write(b"\x9c\x9b\x9a")

# Para leer se utiliza el método read, si no se especifica la cantidad 
# de bytes, leerá el archivo entero
archivo = open(datos.bin, "rb")
archivo.read(1)

