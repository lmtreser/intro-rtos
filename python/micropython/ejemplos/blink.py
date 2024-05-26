# Blink con Raspberry Pico

from machine import Pin
import time

led_1 = Pin(25, Pin.OUT)

while True:
    print("Ejecutando...");
    led_1.value(1)
    time.sleep(3)
    led_1.value(0)
    time.sleep(3)