""" 
    ARCHIVOS EN PYTHON
    Instituto Superior IDRA 
    Lucas Martín Treser - 19 de octubre de 2026
    
    Archivo compartido entre dos hilos (Concurrencia)
    Si dos hilos intentan escribir en el mismo archivo al mismo tiempo de
    forma totalmente desordenada, las escrituras pueden cruzarse o corromperse
    a nivel de sistema operativo.

    La solución es usar un Lock para asegurar que cuando un hilo esté escribiendo
    en el archivo, el otro deba esperar su turno.
"""

import threading
import time

nombre_archivo = "./idra/python_os/log_concurrente.txt"
lock = threading.Lock()

def escribir_en_archivo(nombre_hilo):
  for i in range(3):
    time.sleep(0.1)  # Simula un pequeño retraso de trabajo

    # Protegemos la sección crítica de escritura en el archivo
    with lock:
      with open(nombre_archivo, "a") as archivo:
        mensaje = f"[{nombre_hilo}] Mensaje de registro num {i}\n"
        archivo.write(mensaje)
        print(f"{nombre_hilo} escribió en el archivo.")


if __name__ == "__main__":
  # Creamos el archivo limpio antes de empezar
  with open(nombre_archivo, "w") as f:
    f.write("--- INICIO DEL LOG ---\n")

  # Creamos dos hilos que competirán por escribir en el mismo archivo
  hilo1 = threading.Thread(target=escribir_en_archivo, args=("Hilo-A",))
  hilo2 = threading.Thread(target=escribir_en_archivo, args=("Hilo-B",))

  hilo1.start()
  hilo2.start()

  hilo1.join()
  hilo2.join()

  print("\n--- Contenido final del archivo compartido ---")
  with open(nombre_archivo, "r") as f:
    print(f.read())