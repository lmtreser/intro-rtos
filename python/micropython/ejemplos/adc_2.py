from machine import Pin, ADC
from time import sleep_ms

# Con divisor resistivo (0-1V)
# adc = ADC(Pin(35), atten=ADC.ATTN_0DB)

# Sin divisor resistivo (0-3V)
adc = ADC(Pin(35), atten=ADC.ATTN_11DB)

while True:
    lectura = adc.read()
    print(f"Valor en 12 bits: {lectura}")
    
    # lee en µV pero en múltiplos de 1000
    lectura = adc.read_uv()
    print(f"Valor en mV: {lectura/1000} mV")
    sleep_ms(500)
    