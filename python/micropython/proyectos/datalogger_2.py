# Registrador de datos
# Técnicatura Superior en Desarrollo de Software
# Lunes 1 de noviembre de 2021

import machine, onewire, ds18x20, time, os

# Sensor DS18B20
ds_pin = machine.Pin(22)
ds_sensor = ds18x20.DS18X20(onewire.OneWire(ds_pin))
roms = ds_sensor.scan()
print('Found DS devices: ', roms)

while True:
  ds_sensor.convert_temp()
  time.sleep_ms(750)
  print(ds_sensor.read_temp(roms[0]),"°C")
  ArchTemp = ds_sensor.read_temp(roms[0])
  Archivo = open ("Fecha.txt","a")
  Archivo.write(str(ArchTemp)+ "\n")
  Archivo.close()
  time.sleep(5)
