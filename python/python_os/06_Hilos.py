""" 
    PROCESOS - HILOS
    Instituto Superior IDRA 
    Lucas Martín Treser - 19 de octubre de 2026
    
    Hilos
    A diferencia de los procesos, los hilos comparten el mismo espacio
    de memoria dentro de un mismo proceso. Esto hace que comunicarse entre
    ellos sea extremadamente fácil, pero trae consigo problemas de
    concurrencia y limitaciones propias de Python.

    Para crear hilos usamos el módulo threading. El siguiente ejemplo
    muestra cómo lanzar múltiples hilos que corren concurrentemente. 
"""

import threading
import time

def tarea_hilo(nombre, segundos):
  print(f"[Hilo {nombre}] Iniciando...")
  time.sleep(segundos)
  print(f"[Hilo {nombre}] ¡Terminado!")

if __name__ == "__main__":
  inicio = time.time()

  # Creamos los hilos
  hilo1 = threading.Thread(target=tarea_hilo, args=("A", 2))
  hilo2 = threading.Thread(target=tarea_hilo, args=("B", 2))

  hilo1.start()
  hilo2.start()

  hilo1.join()
  hilo2.join()

  fin = time.time()
  print(f"Tiempo total con hilos: {fin - inicio:.2f} segundos")