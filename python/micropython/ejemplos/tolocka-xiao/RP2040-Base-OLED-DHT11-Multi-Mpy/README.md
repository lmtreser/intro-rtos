# Sensor de temperatura y humedad multifunción

# Descripción
Este proyecto consiste en un sensor de temperatura y humedad basado en la placa **XIAO RP2040** y el módulo **Grove DHT11**. El módulo se conecta a la Placa de expansión y los valores de temperatura y humedad se muestran en el display OLED.

![alt text](images/multi1.jpg)

![alt text](images/multi2.jpg)


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

El programa usa las fuentes **PerfectPixel_23x32** y **FixedFont5x8** que deben estar copiadas en la carpeta **fonts** del sistema de archivos de la RP2040

# Imágenes

Se usan dos imágenes tipo bitmap para acompañar a los valores numéricos. Estas son **TempIcon.mono** y **HumIcon.mono** que se deben copiar en el sistema de archivos de la RP2040 en la carpeta **images**


# Funcionamiento

El sensor mide constantemente valores de temperatura y humedad y almacena en memoria las últimas 100 mediciones.  Tiene 5 modos de visualización que se seleccionan pulsando secuencialmente el botón de usuario incluido en la placa de expansión. 
Los modos de visualización son los siguientes:

- Temperatura y humedad actuales: Muestra los últimos valores medidos
- Temperatura y humedad mínimas: Muestra los valores mínimos dentro de los últimos 100 medidos.
- Temperatura y humedad máximas: Muestra los valores máximos dentro de los últimos 100 medidos.
- Temperatura y humedad medias: Muestra los valores medios dentro de los últimos 100 medidos.
- Gráfica de Temperatura: Muestra los últimos 100 valores medidos de temperatura en forma gráfica.
- Gráfica de Humedad: Muestra los últimos 100 valores medidos de humedad en forma gráfica.

# Proyectos relacionados

[Demo de bitmaps](https://github.com/profetolocka/XIAO/tree/main/Espa%C3%B1ol/RP2040-Base-OLED-Bitmap-Mpy)

[Sensor DHT mas bitmaps](https://github.com/profetolocka/XIAO/tree/main/Espa%C3%B1ol/RP2040-Base-OLED-DHT11-Bitmap-Mpy)

