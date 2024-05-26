# Proyecto: semáforo con botón de bloqueo
# Uso de ejecución en hilos

from machine import Pin
import time
import _thread

LED_ROJO = Pin(22, Pin.OUT)
LED_AMARILLO = Pin(26, Pin.OUT)
LED_VERDE = Pin(27, Pin.OUT)

LED_PLACA = Pin(25, Pin.OUT)

BOTON = Pin(20, Pin.IN)

def second_thread():
    while True:
        print("bandera")
        if (BOTON.value() == 0):
            print("boton pulsado")
    
_thread.start_new_thread(second_thread, ())

while True:
    LED_ROJO.value(1)
    time.sleep(5)
    LED_AMARILLO.value(1)
    time.sleep(1)
    LED_ROJO.value(0)
    LED_AMARILLO.value(0)
    LED_VERDE.value(1)
    time.sleep(5)
    LED_VERDE.value(0)
    LED_AMARILLO.value(1)
    time.sleep(1)
    LED_AMARILLO.value(0)
    
