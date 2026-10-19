# PROCESOS - HILOS
# Instituto Superior IDRA 
# Lucas Martín Treser - 19 de octubre de 2026
#
# Ejemplo 00 Ejecución secuencial de tareas pesadas
#

import time

def tarea_pesada(n):
  print(f"Iniciando tarea: {n}")
  time.sleep(2)  # Simula un cálculo pesado o I/O
  print(f"Tarea {n} finalizada.")

if __name__ == "__main__":
  inicio = time.time()

  # Ejecución secuencial
  for i in range(1, 5):
    tarea_pesada(i)

  fin = time.time()
  print(f"\nTiempo total de ejecución: {fin - inicio:.2f} segundos")