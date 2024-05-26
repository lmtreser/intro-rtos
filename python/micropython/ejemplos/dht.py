from dht import DHT11
from machine import Pin
from time import sleep_ms

dht = DHT11(Pin(32))

while True:
    dht.measure()
    print(f"Temperatura: {dht.temperature()} °C")
    print(f"Humedad: {dht.humidity()} %")
    sleep_ms(1000)