from machine import Pin, PWM
from time import sleep_ms

servo = PWM(Pin(14), freq=50)

while True:
    for i in range(51, 102, 5):
        servo.duty(i)
        sleep_ms(100)