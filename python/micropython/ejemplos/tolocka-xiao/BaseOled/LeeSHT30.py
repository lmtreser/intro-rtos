from machine import Pin,I2C

from xglcd_font import XglcdFont
from ssd1306 import Display
from sht30 import SHT30

sensor = SHT30()

i2cDisp = I2C(-1, freq=400000, scl=Pin(7), sda=Pin(6))  # Qt-Py S2 I2C bus 1
display = Display(i2c=i2cDisp)

#Cargar fonts
perfect = XglcdFont('fonts/PerfectPixel_23x32.c', 23, 32)
robotron = XglcdFont('fonts/Robotron7x11.c', 7, 11)



temperature, humidity = sensor.measure()

print('Temperature:', temperature, 'ºC, RH:', humidity, '%')

tempStr = f"{temperature:.1f}"
humStr  = f"{humidity:.0f}"

display.draw_text(5, 10, "Temp        Hum", robotron, True)


display.draw_text(5, 30, tempStr, perfect, False)
display.draw_text(80, 30, humStr, perfect, False)


display.present()