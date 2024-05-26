# Trabajo Publicaciones/Suscripciones/Node-RED
# Lucas Martín Treser - Noviembre de 2022
#
# /lmtreser/salidas/led_rojo
# Una llave en el dashboard que permita permutar entre encendido y 
# apagado de un LED.
#
# /lmtreser/salidas/servo
# Un control deslizante en el dashboard que permita posicionar un 
# servomotor en la placa de desarrollo para moverlo entre 10 y 170 grados.
#
# /lmtreser/salidas/neopixel/1
# Un control de colores RGB en el dashboard que permita cambiar de color 
# a uno o varios LED NeoPixel.
#
# /lmtreser/entradas/nivel
# Informar en el dashboard el valor medido utilizando el conversor 
# analógico-digital de la placa de desarrollo. Se sugiere que la medición sea 
# de forma continua (periódica a intervalos de 1 segundo) y graficar valores 
# históricos. 
# 
# /lmtreser/entradas/alarma
# Generar una notificación en el dashboard al dispararse una alarma implementada
# en la placa de desarrollo.
# 
# /lmtreser/entradas/temperatura
# /lmtreser/entradas/humedad
# Informar en el dashboard el valor sensado en la placa de desarrollo de 
# temperatura y humedad de forma continua. Se sugieren graficar los valores 
# históricos.

import network
from dht import DHT11
from time import sleep_ms
from neopixel import NeoPixel
from machine import ADC, Pin, PWM, Timer
from umqtt.robust import MQTTClient

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

# ----- Funcion map
def escalar(variable, in_min, in_max, out_min, out_max):
    result = (variable - in_min) * (out_max - out_min) // (in_max - in_min) + out_min 
    return result

# ----- Lectura de nivel, humedad y temperatura
def niveles(timer):

    # ADC
    lectura = adc.read_uv()
    milivolts = lectura / 1000

    # DHT11
    dht.measure()
    temp = dht.temperature()
    hum = dht.humidity()
    
    cliente.publish("/lmtreser/entradas/temperatura", str(temp))
    cliente.publish("/lmtreser/entradas/humedad", str(hum))
    cliente.publish("/lmtreser/entradas/nivel", str(milivolts))

# ----- Funcion Neopixel
def pixel(nro, r, g, b):
    np[nro] = (int(r), int(g), int(b))
    np.write()

# ----- Funcion servo
def servito(angulo):
    posicion = escalar(int(angulo), 0, 180, 51, 102) 
    servo.duty(posicion)

# ----- Funcion callback MQTT
def callback(topic, msg):
    
    # Recibo y decodifico los datos
    mensaje = msg.decode()
    topico = topic.decode()
    
    # Neopixel
    if (topico == "/lmtreser/salidas/neopixel/1"):
        color = mensaje.split(",")
        pixel(0, color[0], color[1], color[2])
    
    # Servo
    if (topico == "/lmtreser/salidas/servo"):
        servito(mensaje)
        
    # LED ROJO
    if (topico == "/lmtreser/salidas/led_rojo"):
        if (mensaje == "true"):
            led_rojo.value(1)
        elif (mensaje == "false"):
            led_rojo.value(0)

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
tim.init(period=2000, mode=Timer.PERIODIC, callback=niveles)

# ----- Bucle infinito
while True:
    
    cliente.check_msg()
    
    # Alarma
    if (boton2.value() == False):
        sleep_ms(10)
        if (boton2.value() == True):
            payload = "Intruso detectado"
            cliente.publish("/lmtreser/entradas/alarma", payload) 
    
    sleep_ms(1)

cliente.disconnect()
