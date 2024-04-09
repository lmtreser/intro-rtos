# Sistema de archivos en MicroPython
#
# El módulo os (uos) de la librería estándar de MicroPython proporciona un conjunto
# de funciones para  manipular los archivos y estructura de directorios, las funciones
# generales uname –da información del intérprete y/o microcontrolador– y urandom –genera
# bytes aleatorios-, funciones para el redireccionamiento y duplicación del terminal y
# funciones para la integración del sistema de archivos.
#
# https://www.esploradores.com/os/

import os

# listdir – Lista el contenido del sistema de archivos
os.listdir()

# mkdir – Crea un directorio
os.mkdir("dir_ejemplo")

# chdir – Cambia a un directorio
os.chdir("dir_ejemplo")

# chdir - Volver al directorio raíz
os.chdir("/")

# rename – Renombra un directorio o archivo
os.rename("dir_ejemplo", "dir-ejemplo")

# getcwd – Indica el directorio actual
os.getcwd()

# rmdir – Borra un directorio
os.rmdir("dir-ejemplo")