# Finalizar un proceso
# Mayo de 2024

import os
import time
import multiprocessing

def proceso_hijo():
    print("Mensaje desde el proceso hijo")
    time.sleep(2)
    print("Fin del proceso hijo")

# Crear el proceso hijo
process = multiprocessing.Process(target=proceso_hijo)
process.start()
time.sleep(3)

if process.is_alive():
    process.terminate()
    print("Proceso hijo finalizado antes de tiempo")

print("Fin del programa")
