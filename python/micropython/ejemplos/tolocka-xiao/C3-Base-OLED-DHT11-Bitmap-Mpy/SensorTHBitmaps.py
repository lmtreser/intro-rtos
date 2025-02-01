# Sensor de temperatura y humedad con modulo Grove DHT11
# Muestra valores en OLED de placa de expansión
# Usa fonts grandes y bitmaps

#Equivalencias entre nombres de pines y GPIOs
D0 = 2
D1 = 3
D2 = 4
D3 = 5
D4 = 6
D5 = 7
D6 = 21
D7 = 20
D8 = 8
D9 = 9
D10 = 10


from time import sleep
from machine import Pin, SoftI2C 
from ssd1306 import Display
from xglcd_font import XglcdFont

from dht import DHT11

#Crear objeto I2C
i2c = SoftI2C(freq=400000, scl=Pin(D5), sda=Pin(D4))  

#Crear objeto display
display = Display(i2c=i2c, width=128, height=64)

#Crear objeto sensor
sensorTH = DHT11 (Pin(D7))

# Carga font grande
perfect = XglcdFont('fonts/PerfectPixel_23x32.c', 23, 32)


while (True):
    
    sensorTH.measure ()  #Mide Temperatura y humedad del DHT11
    
    temp = sensorTH.temperature()
    hum  = sensorTH.humidity()
    
    print (temp,"grados")
    print (hum ,"%")
    
    tempStr = f"{temp:.1f}"
    humStr  = f"{hum:.0f}"

    #Borrar buffer
    display.clear_buffers()
    
    #Mostrar valores de temperatura y humedad en OLED
    display.draw_text(5, 31, tempStr, perfect, False)
    display.draw_text(85, 31, humStr, perfect, False)
    
    #Mostrar bitmaps
    display.draw_bitmap("images/TempIcon.mono", 25, 0, 32, 32, True)
    display.draw_bitmap("images/HumIcon.mono",  85, 0, 32, 32, True)

    #Actualizar pantalla
    display.present()

    sleep(10)
