# Mide valores de temperatura y humedad usando el módulo Grove DHT11
# Muestra en OLED de base de expansion usando lib ssd1306 oficial

# Pines y equivalencias con GPIO
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

from machine import Pin, SoftI2C
from time import sleep
from dht import DHT11
from ssd1306 import SSD1306_I2C #Libreria oficial


#Crea objeto I2C
i2c = SoftI2C(scl=Pin(D5), sda=Pin(D4), freq=100000)  #Inicializa i2c

#Crea objeto oled
Display = SSD1306_I2C (128, 64, i2c)


sensorTH = DHT11 (Pin(D7))

while (1):
    sensorTH.measure ()  #Mide
    
    print (sensorTH.temperature(),"grados")
    print (sensorTH.humidity (),"%")
    
    Display.fill (0)

    Display.text ("Temp=",10,10,1)
    Display.text (str(sensorTH.temperature()),50,10,1)
    Display.text ("Hum=",10,20,1)
    Display.text (str(sensorTH.humidity ()),50,20,1)
    Display.show()
    
    sleep (5)



