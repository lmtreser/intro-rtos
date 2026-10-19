""" 
    PROCESOS - HILOS
    Instituto Superior IDRA 
    Lucas Martín Treser - 19 de octubre de 2026
    
    Alternativa al Ejemplo 01 
    Cuando un hilo ejecuta time.sleep() (simulando una tarea I/O), le avisa
    al sistema operativo que va a "pausar" su ejecución y libera el GIL (Global
    Interpreter Lock de Python). Mientras el Hilo 1 está durmiendo, el sistema
    operativo le pasa el turno al Hilo 2, luego al 3 y al 4. En este caso, es 
    conveniente usar hilos porque el consumo de memoria RAM es menor que si
    usáramos procesos, y el tiempo de ejecución es similar.

    Si es CPU (cálculo matemático puro, procesamiento de video), con hilos
    tardaría 8 segundos (porque el GIL de Python obligará a los hilos a turnarse
    en un solo núcleo), mientras que con procesos tardaría 2 segundos (porque 
    cada proceso corre en un núcleo distinto de tu CPU).
"""

import threading
import time

def tarea_pesada(n):
  print(f"Iniciando tarea en hilo: {n}")
  time.sleep(2)  # Simula I/O
  print(f"Hilo {n} finalizado.")

if __name__ == "__main__":
  inicio = time.time()
  hilos = []

  # Creamos y lanzamos los hilos
  for i in range(1, 5):
    h = threading.Thread(target=tarea_pesada, args=(i,))
    hilos.append(h)
    h.start()

  # Esperamos a que todos los hilos terminen
  for h in hilos:
    h.join()

  fin = time.time()
  print(f"\nTiempo total con hilos: {fin - inicio:.2f} segundos")