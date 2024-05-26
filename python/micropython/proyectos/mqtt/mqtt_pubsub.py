# Trabajo Publicaciones/Suscripciones
# Lucas Martín Treser - Octubre de 2022
#
# /<alumno>/salidas/led_<color>: encender el LED del color correspondiente
# si se recibe on, sino apagar.
#
# /<alumno>/salidas/servo: leer el número recibido en el rango 0-180 y ubicar
# el servo en esa posición.
#
# /<alumno>/salidas/neopixel/<num>: se reciben tres valores separados por
# comas (R,G,B) y encender el NeoPixel como corresponda (ayuda: usar método
# .split(“,”) en el mensaje). Deben interpretarse qué píxel iluminar siendo el
# topic <num> el índice.
#
# /alumno/entradas/nivel enviar el estado del potenciometro al pulsar un boton
# 
# /alumno/entradas/alarma al pulsar un boton enviar un mensaje de alarma
# 
# /alumno/entradas/temperatura enviar la temperatura periodicamente
# 
# /alumno/entradas/humedad enviar la humedad periodicamente
#

import network
from dht import DHT11
from time import sleep_ms
from neopixel import NeoPixel
from machine import ADC, Pin, PWM, Timer
from umqtt.robust import MQTTClient

# ----- Variables
contador = 0

# ----- Definicion de dispositivos
np = NeoPixel(Pin(27), 8)
servo = PWM(Pin(14), freq=50)
led_rojo = Pin(0, Pin.OUT)
led_verde = Pin(15, Pin.OUT)
led_amarillo = Pin(2, Pin.OUT)
boton1 = Pin(18, Pin.IN, Pin.PULL_UP)
boton2 = Pin(19, Pin.IN, Pin.PULL_UP)
adc = ADC(Pin(35), atten=ADC.ATTN_11DB)
dht = DHT11(Pin(32))

# Funcion map
def escalar(variable, in_min, in_max, out_min, out_max):
    result = (variable - in_min) * (out_max - out_min) // (in_max - in_min) + out_min 
    return result

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

# Funcion Neopixel
def pixel(nro, r, g, b):
    np[nro] = (int(r), int(g), int(b))
    np.write()

# Funcion servo
def servito(angulo):
    posicion = escalar(int(angulo), 0, 180, 51, 102) 
    servo.duty(posicion)

# ----- Funcion callback MQTT
def callback(topic, msg):
    
    # Recibo y decodifico los datos
    mensaje = msg.decode()
    topico = topic.decode()
    
    # Neopixel
    if (topico == "/lmtreser/salidas/neopixel/1/"):
        color = mensaje.split(",")
        pixel(0, color[0], color[1], color[2])
        
    if (topico == "/lmtreser/salidas/neopixel/2/"):
        color = mensaje.split(",")
        pixel(1, color[0], color[1], color[2])
        
    if (topico == "/lmtreser/salidas/neopixel/3/"):
        color = mensaje.split(",")
        pixel(2, color[0], color[1], color[2])
    
    # Servo
    if (topico == "/lmtreser/salidas/servo/"):
        servito(mensaje)
        
    # LED ROJO
    if (topico == "/lmtreser/salidas/led_rojo/"):
        if (mensaje == "on"):
            led_rojo.value(1)
        elif (mensaje == "off"):
            led_rojo.value(0)

    # LED VERDE
    if (topico == "/lmtreser/salidas/led_verde/"):
        if (mensaje == "on"):
            led_verde.value(1)
        elif (mensaje == "off"):
            led_verde.value(0)
            
    # LED AMARILLO
    if (topico == "/lmtreser/salidas/led_amarillo/"):
        if (mensaje == "on"):
            led_amarillo.value(1)
        elif (mensaje == "off"):
            led_amarillo.value(0)

# ----- Conexión a Internet
wlan = network.WLAN(network.STA_IF)
if not wlan.active():
    wlan.active(True)

if not wlan.isconnected():
    wlan.connect("ssid", "password")
    print("Conectando...")
    while not wlan.isconnected():
        sleep_ms(1000)

config = wlan.ifconfig()
print(f"Conectado con ip {config[0]}")

# ----- Conexión al broker MQTT
cliente = MQTTClient("esp32-a99", "livra-mqtt.fi.mdp.edu.ar", port=1884)
print("Conectando a servidor MQTT...")
cliente.set_callback(callback)
cliente.connect()
cliente.subscribe("/lmtreser/salidas/#")
print("Conectado")

# ----- Inicia el Timer0
tim = Timer(0)
tim.init(period=5000, mode=Timer.PERIODIC, callback=temperatura)

while True:
    
    cliente.check_msg()
    
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
    
    sleep_ms(1)

cliente.disconnect()
