import network
from time import sleep_ms
from umqtt.robust import MQTTClient

wlan = network.WLAN(network.STA_IF)
if not wlan.active():
    wlan.active(True)

if not wlan.isconnected():
    wlan.connect("FIWIFI", "")

    print("Conectando...")
    while not wlan.isconnected():
        sleep_ms(1000)

config = wlan.ifconfig()
print(f"Conectado con ip {config[0]}")

def callback(topic, msg):
    print(f"Llegó {msg.decode()} de {topic.decode()}")

cliente = MQTTClient("esp32-1", "livra.local", port=1884)
print("Conectando a servidor MQTT...")
cliente.set_callback(callback)
cliente.connect()
cliente.subscribe("#")
print("Conectado")

while True:
    cliente.publish("envio", "prueba")
    cliente.check_msg()
    sleep_ms(500)

cliente.disconnect()
