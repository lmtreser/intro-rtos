# Mide valores de temperatura y humedad usando el módulo Grove DHT11
# Muestra en OLED de base de expansion usando lib ssd1306 oficial
# Usa la placa XIAO RP2040

# Pines
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

#I2C
SDA_PIN = D4
SCL_PIN = D5

#Buzzer
BUZZER_PIN = D3

from machine import Pin, SoftI2C, PWM
from time import sleep
from dht import DHT11
from ssd1306 import SSD1306_I2C #Libreria oficial

#Crea objeto Buzzer como PWM. DC inicial = 0
Buzzer = PWM(Pin(BUZZER_PIN), freq=1000, duty_u16=0)

#Crea objeto I2C
i2c = SoftI2C(scl=Pin(SCL_PIN), sda=Pin(SDA_PIN), freq=100000)  #Inicializa i2c

#Crea objeto oled
Display = SSD1306_I2C (128, 64, i2c)

#El modulo Grove DHT11 está conectado a D7
sensorTH = DHT11 (Pin(D7))

# Hace un bip usando el zumbador pasivo de la placa de expansión
def Beep ():
    Buzzer.duty_u16(32768)     # Fija DC a 50%
    sleep (0.1)
    Buzzer.duty_u16(0)         # Fija DC a 0%

    
# Loop

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
    
    Beep ()
    
    sleep (5)



