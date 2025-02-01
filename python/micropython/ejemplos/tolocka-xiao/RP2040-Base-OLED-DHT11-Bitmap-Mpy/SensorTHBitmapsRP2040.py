# Autor: Ernesto Tolocka (profe Tolocka)
# Fecha: 15-12-2024
# Descripción: Sensor de temperatura y humedad con RP2040 y módulo Grove DHT11
#   Muestra valores en OLED de la placa de expansión
#   Usa fuentes grandes y bitmaps
# Licencia: MIT

# Equivalencias entre nombres de pines y GPIOs
D0 = 26
D1 = 27
D2 = 28
D3 = 29
D4 = 6
D5 = 7
D6 = 0
D7 = 1
D8 = 2
D9 = 4
D10 = 3

# Pines I2C del RP2040
PIN_SDA = D4
PIN_SCL = D5

# Pin de conexión del DHT11
PIN_DHT11 = D7

from time import sleep
from machine import Pin, SoftI2C 
from ssd1306 import Display
from xglcd_font import XglcdFont
from dht import DHT11

# Crear objeto I2C
i2c = SoftI2C(freq=400000, scl=Pin(PIN_SCL), sda=Pin(PIN_SDA)) 

# Crear objeto display
display = Display(i2c=i2c, width=128, height=64)

# Crear objeto sensor
sensorTH = DHT11(Pin(PIN_DHT11))

# Cargar fuente grande
perfect = XglcdFont('fonts/PerfectPixel_23x32.c', 23, 32)

# Bucle
while (True):
    
    sensorTH.measure()  # Medir temperatura y humedad del DHT11
    
    temp = sensorTH.temperature()
    hum  = sensorTH.humidity()
    
    print(temp, "grados")
    print(hum, "%")
    
    tempStr = f"{temp:.1f}"
    humStr  = f"{hum:.0f}"

    # Borrar buffer
    display.clear_buffers()
    
    # Mostrar valores de temperatura y humedad en OLED
    display.draw_text(5, 31, tempStr, perfect, False)
    display.draw_text(85, 31, humStr, perfect, False)
    
    # Mostrar bitmaps
    display.draw_bitmap("images/TempIcon.mono", 25, 0, 32, 32, True)
    display.draw_bitmap("images/HumIcon.mono",  85, 0, 32, 32, True)

    # Actualizar pantalla
    display.present()

    sleep(10)