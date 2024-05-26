# Uso del sensor de temperatura interno

from machine import ADC
import time

sensor = ADC(4)
factor = 3.3 /65535

while True:
    reading = sensor.read_u16() * factor
    
    # The temperature sensor measures the Vbe voltage of a biased
    # bipolar diode, connected to the fifth ADC channel
    # Typically, Vbe = 0.706V at 27 degrees C, with a slope
    # of -1.721mV (0.001721) per degree. 
    temperatura = 27 - (reading - 0.706) / 0.001721
    print("Temperatura interna:", temperatura, "°C")
    time.sleep(1)