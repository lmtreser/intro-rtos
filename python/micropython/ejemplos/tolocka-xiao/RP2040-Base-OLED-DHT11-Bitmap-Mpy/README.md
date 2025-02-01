# Sensor de temperatura y humedad con DHT11

# Descripción
Este proyecto consiste en un sensor de temperatura y humedad basado en la placa **XIAO RP2040** y el módulo **Grove DHT11**. El módulo se conecta a la Placa de expansión y los valores de temperatura y humedad se muestran en el display OLED.
Se usan fonts grandes para los valores numéricos y se muestran imágenes bitmaps relacionadas con las magnitudes.

![alt text](images/RP2040BaseOledDHT11Bitmaps.jpg)



# Librerías
Este proyecto usa la [librería de rdagger](https://github.com/rdagger/micropython-ssd1306) para controlar el OLED.
Hay que instalar la librería del OLED (ssd1306.py) y la que permite el manejo de fonts (xglcd_font.py). Se lo puede hacer manualmente o usando MIP:

```python annotate
>>> import network
>>> wlan=network.WLAN (network.STA_IF)
>>> wlan.active (True)
True
>>> wlan.connect ("xxxx", "xxxx")
>>> import mip
>>> mip.install ("https://raw.githubusercontent.com/rdagger/micropython-ssd1306/refs/heads/main/ssd1306.py")
Downloading https://raw.githubusercontent.com/rdagger/micropython-ssd1306/refs/heads/main/ssd1306.py to /lib
Copying: /lib/ssd1306.py
Done
>>> mip.install ("https://raw.githubusercontent.com/rdagger/micropython-ssd1306/refs/heads/main/xglcd_font.py")
Downloading https://raw.githubusercontent.com/rdagger/micropython-ssd1306/refs/heads/main/xglcd_font.py to /lib
Copying: /lib/xglcd_font.py
Done
>>> 

```
# Fonts
Para imprimir en el OLED los valores de temperatura y humedad, se usa la fuente **PerfectPixel_23x32** que debe estar copiada en el sistema de archivos de la RP2040 en la carpeta **fonts**

# Imágenes
Se usan dos imágenes tipo bitmap para acompañar a los valores numéricos. Estas son **TempIcon.mono** y **HumIcon.mono** que se deben copiar en el sistema de archivos de la RP2040 en la carpeta **images**

