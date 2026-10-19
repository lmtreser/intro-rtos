""" 
    PROCESOS - HILOS
    Instituto Superior IDRA 
    Lucas Martín Treser - 19 de octubre de 2026
    
    Comunicación entre procesos (IPC)
    Como los procesos tienen espacio de memoria independientes, si se modifica
    una variable global dentro de un proceso hijo, esa modificación no se
    refleja en el proceso padre. Además, si dos procesos intentan escribir al
    mismo recurso al mismo tiempo, ocurren condiciones de carrera.

    Para pasar datos de forma segura entre procesos independientes en GNU/Linux,
    el sistema operativo provee mecanismos de IPC (Inter-Process Communication)
    como Colas (Queue) o Tuberías (Pipe).
"""

import time
from multiprocessing import Process, Queue

def productor(cola):
  for i in range(1, 4):
    dato = f"Mensaje_{i}"
    cola.put(dato)  # Enviamos datos a la cola del S.O.
    print(f"[Productor] Enviado: {dato}")
    time.sleep(0.5)

def consumidor(cola):
  while True:
    dato = cola.get()  # Extrae el dato
    if dato is None:
      break
    print(f"[Consumidor] Recibido y procesado: {dato}")

if __name__ == "__main__":
  cola = Queue()

  p_prod = Process(target=productor, args=(cola,))
  p_cons = Process(target=consumidor, args=(cola,))

  p_prod.start()
  p_cons.start()

  p_prod.join()  # Esperamos a que el productor termine

  # Señal de parada para el consumidor
  cola.put(None)
  p_cons.join()

  print("Comunicación finalizada con éxito.")