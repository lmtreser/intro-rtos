# Trabajo Suscripciones - Lucas Martín Treser
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

import network
from time import sleep_ms
from neopixel import NeoPixel
from machine import Pin, PWM
from umqtt.robust import MQTTClient

# ----- Definicion de dispositivos
np = NeoPixel(Pin(27), 8)
servo = PWM(Pin(14), freq=50)
led_rojo = Pin(0, Pin.OUT)
led_verde = Pin(15, Pin.OUT)
led_amarillo = Pin(2, Pin.OUT)

# Funcion map
def escalar(variable, in_min, in_max, out_min, out_max):
    result = (variable - in_min) * (out_max - out_min) // (in_max - in_min) + out_min 
    return result

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
    wlan.connect("Fibertel WiFi973 2.4GHz", "0043062806")
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

while True:
    cliente.check_msg()
    sleep_ms(1)

cliente.disconnect()
