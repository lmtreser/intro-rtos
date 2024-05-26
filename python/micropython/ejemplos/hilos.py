# Ejecución en hilos

from machine import Pin
import time
import _thread

# Configurar el LED interno
LED = Pin(25, Pin.OUT)

# Función que bloqueará el hilo con un loop while
def second_thread():
    while True:
        print("Hola, soy", _thread.get_ident(), "el hilo nro. 2")
        time.sleep(1)
        
# Función que inicializa la ejecución en el segundo núcleo
# El segundo argumento es una lista o diccionario con los argumentos
# que se pasarán a la función.
_thread.start_new_thread(second_thread, ())

# Segundo loop que bloqueará el hilo principal
while True:
    # print("Hola, soy", _thread.get_ident(), "el hilo nro. 1")
    LED.toggle()
    time.sleep(0.25)
