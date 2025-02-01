# Uso de bitmaps en OLED

# Descripción
Este es un ejemplo de uso del OLED de la Base expansion con una placa **XIAO RP2040** . Se muestra un bitmap (logo de Seeed Studio) en modo directo e inverso.

![Demo bitmaps](images/RP2040Bitmaps.jpg)


# Librerías
Este proyecto utiliza la librería `ssd1306.py` creada por [rdagger](https://github.com/rdagger/micropython-ssd1306). La misma ha sido incluida bajo la licencia MIT.
Hay que copiarla en la XIAO manualmente (no se puede instalar empleando el Gestor de paquetes de Thonny).

Descargala de la URL provista mas arriba como un archivo .ZIP y luego copia el archivo **ssd1306.py** al sistema de archivos de la XIAO.


# Imágenes
El código carga la imagen `seeedLogo.mono` desde la carpeta **images** en el sistema de archivos.

Esta imagen y la original en formato BMP están en la carpeta **images** del repositorio. En la misma carpeta se encuentra el programa **img2monoHMSB.py** que permite convertir la imagen BMP al formato monoHMSB

Esto se hace de la siguiente forma:

(En la ventana de comandos)

```
python img2monoHMSB.py seeedLogo.bmp
```

El archivo `seeedLogo.mono` generado debe cargarse en la carpeta **images** de la XIAO

