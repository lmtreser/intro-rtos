# Uso de bitmaps en OLED

# Descripción
Este es un ejemplo de uso del OLED de la Base expansion de XIAO con una placa ESP32-C3. Se muestra un bitmap (logo de Seeed Studio) en modo directo e inverso.

![OLED Demo](images/OLEDLogo.jpg)


# Librerías
Este proyecto utiliza la librería `ssd1306.py` creada por [rdagger](https://github.com/rdagger/micropython-ssd1306). La misma ha sido incluida bajo la licencia MIT.
Hay que copiarla en la carpeta \lib de la XIAO manualmente o usando **MIP**

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
>>> 

```

# Imágenes
El código carga la imagen `seeedLogo.mono` desde la carpeta **images** en el sistema de archivos.

Esta imagen y la original en formato BMP están en la carpeta **images** del repositorio. En la misma carpeta se encuentra el programa **img2monoHMSB.py** que permite convertir la imagen BMP al formato monoHMSB

Esto se hace de la siguiente forma:

(En la ventana de comandos)

```
python img2monoHMSB.py seeedLogo.bmp
```

El archivo `seeedLogo.mono` generado debe cargarse en la carpeta **images** de la XIAO

