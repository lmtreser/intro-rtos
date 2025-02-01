#Demo de imagen bitmap. Muestra el logo de Seeed Studio

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

#Crear objeto I2C
i2c = SoftI2C(freq=400000, scl=Pin(D5), sda=Pin(D4))  #Pines de la XIAO ESP32-C3

#Crear objeto display
display = Display(i2c=i2c, width=128, height=64)

while (True):

    #Mostrar bitmap
    display.draw_bitmap("images/seeedLogo.mono", 0, 0, 116, 64)
    display.present()
    sleep(10)

    #Borrar buffer
    display.clear_buffers()

    #Mostrar bitmap
    display.draw_bitmap("images/seeedLogo.mono", 0, 0, 116, 64, invert=True)
    display.present()
    sleep(10)
