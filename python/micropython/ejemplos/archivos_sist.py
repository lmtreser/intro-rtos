# Sistema de archivos en MicroPython

import os

# listdir – Lista el contenido del sistema de archivos
os.listdir()

# mkdir – Crea un directorio
os.mkdir("libs")

# chdir – Cambia a un directorio
os.chdir("libs")

# chdir - Volver al directorio raíz
os.chdir("/")

# rmdir – Borra un directorio
os.rmdir("libs")

# getcwd – Indica el directorio actual
os.getcwd()

# rename – Renombra un directorio o archivo
os.rename("libs", "lib")
