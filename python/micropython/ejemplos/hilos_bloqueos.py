# Uso de hilos con bloqueos

from machine import Pin
import time
import _thread

LED = Pin(25, Pin.OUT)

# Creamos un semáforo (también llamado bloqueo)
bloqueo = _thread.allocate_lock()

# Función que bloqueará el hilo
def second_thread():
    while True:
        # Adquirir el bloqueo del semáforo
        bloqueo.acquire()
        print("Hilo", _thread.get_ident() ,"bloqueando")
        time.sleep(1)
        # Liberar el bloqueo del semáforo
        bloqueo.release()
        
# Función que inicializa la ejecución en el segundo núcleo
_thread.start_new_thread(second_thread, ())

# Hilo principal
while True:
    bloqueo.acquire()
    LED.toggle()
    time.sleep(0.25)
    print("Hilo", _thread.get_ident() ,"bloqueando")
    bloqueo.release()