import queue
import sqlite3
import threading

cola_datos = queue.Queue()

# Hilo 1: Lee datos desde la terminal (Productor)
def leer_terminal(cola):
  print("--- Hilo Terminal Iniciado ---")
  print("Escribe algo y presiona Enter (escribe 'salir' para terminar):")

  while True:
    texto = input("> ")
    if texto.lower() == "salir":
      cola.put(None)
      break
    if texto.strip():
      cola.put(texto)

# Hilo 2: Guarda en la base de datos SQLite (Consumidor)
def guardar_db(cola):
  conexion = sqlite3.connect("registros.db")
  cursor = conexion.cursor()

  cursor.execute("""
        CREATE TABLE IF NOT EXISTS mensajes (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            contenido TEXT,
            fecha TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        )
    """)
  conexion.commit()

  print("--- Hilo Base de Datos Iniciado --- Esperando datos...")

  while True:
    texto = cola.get()  # Espera a que haya un elemento en la cola

    if texto is None:  # Si recibe la señal de parada, salimos del ciclo
      cola.task_done()
      break

    # Insertamos el texto recibido en la base de datos
    cursor.execute("INSERT INTO mensajes (contenido) VALUES (?)", (texto,))
    conexion.commit()
    print(f"[BD] Guardado exitosamente: '{texto}'")
    cola.task_done()

  conexion.close()
  print("--- Hilo Base de Datos Cerrado ---")

if __name__ == "__main__":
  hilo_terminal = threading.Thread(target=leer_terminal, args=(cola_datos,))
  hilo_db = threading.Thread(target=guardar_db, args=(cola_datos,))

  hilo_db.start()
  hilo_terminal.start()

  hilo_terminal.join()
  hilo_db.join()

  print("Programa finalizado correctamente. Datos guardados en 'registros.db'.")