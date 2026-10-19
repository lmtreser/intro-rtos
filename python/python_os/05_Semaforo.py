""" 
    PROCESOS - HILOS
    Instituto Superior IDRA 
    Lucas Martín Treser - 19 de octubre de 2026
    
    Semáforo (Control de acceso concurrente)
    Un Semáforo es una evolución del Lock. Mientras que el Mutex solo
    permite el paso a un proceso a la vez, el semáforo mantiene un contador
    interno que permite el acceso a un número máximo de N procesos de
    forma simultánea.
"""

import time
from multiprocessing import Process, Semaphore

def usar_recurso(semaforo, id_proceso):
  print(f"Proceso {id_proceso} esperando acceso...")

  with semaforo:  # Si el cupo está lleno, el proceso se bloquea aquí
    print(f"¡Proceso {id_proceso} entró a la zona protegida!")
    time.sleep(1)  # Simula uso del recurso limitado
    print(f"Proceso {id_proceso} liberó el recurso.")

if __name__ == "__main__":
  # Creamos un semáforo que permite máximo 2 procesos concurrentes
  semaforo = Semaphore(2)

  procesos = []
  for i in range(4):  # Lanzamos 4 procesos
    p = Process(target=usar_recurso, args=(semaforo, i))
    procesos.append(p)
    p.start()

  for p in procesos:
    p.join()

  print("Todas las tareas terminaron.")