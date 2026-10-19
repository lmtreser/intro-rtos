""" 
    PROCESOS - HILOS
    Instituto Superior IDRA 
    Lucas Martín Treser - 19 de octubre de 2026
    
    Tuberías (Pipe)
    Mientras que una Queue permite repartir tareas a muchos trabajadores, un 
    Pipe es un canal de comunicación bidireccional y directo de punto a punto
    exclusivamente entre dos procesos (un extremo emisor y un extremo receptor). 
    En GNU/Linux, esto emula a las tuberías clásicas `|` de la terminal.
"""

from multiprocessing import Pipe, Process

def worker_hijo(conexion_hijo):
  print("[Hijo] Esperando mensaje del padre...")

  # Recibimos el mensaje a través del Pipe
  mensaje_recibido = conexion_hijo.recv()
  print(f"[Hijo] ¡Mensaje recibido! - {mensaje_recibido}")

  # Respondemos al padre por la misma tubería
  respuesta = "Hola padre, recibido fuerte y claro."
  conexion_hijo.send(respuesta)

if __name__ == "__main__":
  # Creamos el Pipe. Devuelve dos extremos: (conn_padre, conn_hijo)
  conn_padre, conn_hijo = Pipe()

  # Lanzamos el proceso hijo pasándole su extremo del Pipe
  p = Process(target=worker_hijo, args=(conn_hijo,))
  p.start()

  # El padre envía un mensaje
  mensaje_a_enviar = "Hola hijo, este es un mensaje secreto."
  print(f"[Padre] Enviando: {mensaje_a_enviar}")
  conn_padre.send(mensaje_a_enviar)

  # El padre espera la respuesta del hijo por su extremo
  respuesta_recibida = conn_padre.recv()
  print(f"[Padre] Respuesta del hijo - {respuesta_recibida}")

  p.join()