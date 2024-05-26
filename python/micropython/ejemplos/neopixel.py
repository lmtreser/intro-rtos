from neopixel import NeoPixel
from machine import Pin

np = NeoPixel(Pin(27), 3)

# Orden: R, G, B
np[0] = (255, 0, 0)
np[1] = (0, 255, 0)
np[2] = (0, 0, 255)
np.write()
