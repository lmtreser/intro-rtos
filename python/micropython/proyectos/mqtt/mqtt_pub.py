# Trabajo Publicaciones - Lucas Martín Treser
#
# /alumno/entradas/nivel enviar el estado del potenciometro al pulsar un boton
# /alumno/entradas/alarma al pulsar un boton enviar un mensaje de alarma
# /alumno/entradas/temperatura enviar la temperatura periodicamente
# /alumno/entradas/humedad enviar la humedad periodicamente
#

import network
from dht import DHT11
from time import sleep_ms
from machine import Pin, ADC, Timer
from umqtt.robust import MQTTClient

# ----- Variables
contador = 0

# ----- Definicion de dispositivos
boton1 = Pin(18, Pin.IN, Pin.PULL_UP)
boton2 = Pin(19, Pin.IN, Pin.PULL_UP)
adc = ADC(Pin(35), atten=ADC.ATTN_11DB)
dht = DHT11(Pin(32))

# ----- Lectura de humedad y temperatura
def temperatura(timer):
    dht.measure()
    temp = dht.temperature()
    hum = dht.humidity()
    cliente.publish("/lmtreser/entradas/temperatura", str(temp))
    cliente.publish("/lmtreser/entradas/humedad", str(hum))

# ----- Funcion potenciometro
def potenciometro():
    lectura = adc.read_uv()
    milivolts = lectura / 1000
    cliente.publish("/lmtreser/entradas/nivel", str(milivolts))
  
# ----- Conexión a Internet 
wlan = network.WLAN(network.STA_IF)
if not wlan.active():
    wlan.active(True)

if not wlan.isconnected():
    wlan.connect("Fibertel WiFi973 2.4GHz","0043062806")
    print("Conectando...")
    while not wlan.isconnected():
        sleep_ms(1000)

config = wlan.ifconfig()
print(f"Conectado con ip {config[0]}")

# ----- Conexión al broker MQTT
cliente = MQTTClient("esp32-a99", "livra-mqtt.fi.mdp.edu.ar", port=1884)
print("Conectando a servidor MQTT...")
cliente.connect()
print("Conectado")

# ----- Inicia el Timer0
tim = Timer(0)
tim.init(period=5000, mode=Timer.PERIODIC, callback=temperatura)

while True:

    if (boton1.value() == False):
        sleep_ms(10)
        if (boton1.value() == True):
            potenciometro()

    if (boton2.value() == False):
        sleep_ms(10)
        if (boton2.value() == True):
            contador += 1
            payload = "Intruso #" + str(contador)
            cliente.publish("/lmtreser/entradas/alarma", payload) 

cliente.disconnect()
