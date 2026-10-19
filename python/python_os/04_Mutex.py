""" 
    PROCESOS - HILOS
    Instituto Superior IDRA 
    Lucas Martín Treser - 19 de octubre de 2026
    
    Mutex / Cerrojo
    Cuando varios procesos intentan modificar un recurso compartido al 
    mismo tiempo (como una variable o un archivo), se produce una condición
    de carrera (race condition), corrompiendo los datos.

    Un Mutex (Lock) actúa como una llave exclusiva: solo un proceso puede
    obtenerla para entrar a la sección crítica, mientras los demás esperan
    su turno.
"""

import time
from multiprocessing import Lock, Process, Value

def incrementar(contador, lock):
  for _ in range(50):
    time.sleep(0.01)
    # El Lock protege la sección crítica
    with lock:
      contador.value += 1

    # Si no utilizamos el lock, el valor final 
    # del contador será impredecible y menor a 
    # 100 porque ambos procesos se pisarán las
    # escrituras en memoria.
    # contador.value += 1

if __name__ == "__main__":
  # Variable entera compartida en memoria y cerrojo del S.O.
  contador = Value("i", 0)
  lock = Lock()

  p1 = Process(target=incrementar, args=(contador, lock))
  p2 = Process(target=incrementar, args=(contador, lock))

  p1.start()
  p2.start()

  p1.join()
  p2.join()

  print(f"Valor final del contador (con Lock): {contador.value}")