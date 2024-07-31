# Crear procesos
# Mayo de 2024

import os
import time
import multiprocessing

def nuevo_proceso(mensaje):
    print("Iniciando el proceso: ", os.getppid())
    time.sleep(3)
    print(mensaje)
    print("Fin del proceso")

# Crear un proceso
process = multiprocessing.Process(target=nuevo_proceso, name='proceso-hijo',
                                  kwargs={'mensaje': 'Mensaje desde un argumento!'})

print("Proceso padre: ", os.getppid())
process.start()
process.join()

print("Mensaje desde el proceso padre")
