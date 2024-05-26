# threading — Paralelismo basado en hilos
# https://docs.python.org/es/3/library/threading.html

import threading
import time

# Función contador


def cuenta(inicio, nombre):
    count = inicio
    while count < 10:
        print("Thread ID: ", threading.get_native_id(),
              "Hilo: ", nombre, "Cuenta: ", count)
        time.sleep(.5)  # delay
        count += 1

# Función tiempo


def tiempo():
    name = threading.currentThread().getName()
    print("Inicio Hilo: ", name)
    datos = input()
    print("Ingresaste: ", datos, "correspondiente al Hilo", name)


# Creación de procesos a ejecutarse en paralelo
hilo0 = threading.Thread(name="0", target=tiempo)
hilo1 = threading.Thread(name="1", target=tiempo)
hilo2 = threading.Thread(target=cuenta, args=(1, "2"))
hilo3 = threading.Thread(target=cuenta, args=(5, "3"))

# Inicio de procesos
hilo0.start()
hilo1.start()
hilo2.start()
hilo3.start()

print("---> EOF")
