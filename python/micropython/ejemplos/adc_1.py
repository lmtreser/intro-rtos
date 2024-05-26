# Uso del convertidor ADC

from machine import ADC
import time

# Pin donde conectamos el potenciómetro
sensor = ADC(26)

# Factor de conversión lectura/V
factor = 3.3 / 65535

while True:
    # conversion a 16 bits
    lectura = sensor.read_u16()
    volts = lectura * factor
    print("Valor:", lectura ,"| Tensión:", volts,"V") 
    time.sleep(1)