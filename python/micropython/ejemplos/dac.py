from machine import Pin, DAC
from random import randint
from time import sleep_ms

dac = DAC(Pin(25))

while True:
    dac.write(randint(0, 255))
    sleep_ms(1)
        