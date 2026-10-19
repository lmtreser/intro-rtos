""" 
    PROCESOS - HILOS
    Instituto Superior IDRA 
    Lucas Martín Treser - 19 de octubre de 2026
    
    Comunicación entre hilos
    Como los hilos comparten el mismo bloque de memoria, no necesitan estructuras
    complejas de IPC (como Queue o Pipe). Pueden leer y escribir directamente en
    las mismas variables.

    Sin embargo, esto requiere usar un Lock (cerrojo) para evitar que dos hilos
    modifiquen la misma variable al mismo tiempo y corrompan los datos.
"""

import threading
import time

# Variable compartida directamente en memoria
saldo_cuenta = 100
lock = threading.Lock()

def retirar_dinero(nombre_hilo, monto):
  global saldo_cuenta
  print(f"[{nombre_hilo}] Intentando retirar {monto}...")

  with lock:  # Sección crítica protegida
    if saldo_cuenta >= monto:
      time.sleep(0.1)  # Simula un pequeño retraso de lectura/escritura
      saldo_cuenta -= monto
      print(f"[{nombre_hilo}] Éxito. Saldo restante: {saldo_cuenta}")
    else:
      print(f"[{nombre_hilo}] Fondos insuficientes.")

if __name__ == "__main__":
  h1 = threading.Thread(target=retirar_dinero, args=("Hilo-1", 70))
  h2 = threading.Thread(target=retirar_dinero, args=("Hilo-2", 50))

  h1.start()
  h2.start()

  h1.join()
  h2.join()