""" 
    PROCESOS - HILOS
    Instituto Superior IDRA 
    Lucas Martín Treser - 19 de octubre de 2026
  
    Creación de procesos. 
    En GNU/Linux, cuando se crea un proceso con Python, por debajo se suele usar
    una llamada al sistema llamada `fork()`. A diferencia de los hilos, cada
    proceso tiene su propio espacio de memoria independiente y corre en su propio
    núcleo del procesador, esquivando el GIL (Global Interpreter Lock) de Python.

    El ejemplo muestra cómo repartir una tarea pesada en paralelo. En este enfoque,
    se crea manualmente cada objeto `Process`, se le indica qué función ejecutar y
    luego se llama a `start()`. Con `join()` el hilo principal `main` debe esperar
    a que terminen el resto de los procesos o hilos.
"""

import time
from multiprocessing import Process

def tarea_pesada(n):
  print(f"Iniciando tarea en proceso para: {n}")
  time.sleep(2)  # Simula un cálculo pesado o I/O
  print(f"Tarea {n} finalizada.")

if __name__ == "__main__":
  inicio = time.time()

  procesos = []

  # Creamos y lanzamos los procesos
  for i in range(1, 5):
    p = Process(target=tarea_pesada, args=(i,))
    procesos.append(p)
    p.start()  # El S.O. crea un nuevo proceso

  # Esperamos a que todos los procesos terminen su ejecución
  for p in procesos:
    p.join()

  fin = time.time()

  print(f"\nTiempo total de ejecución: {fin - inicio:.2f} segundos")