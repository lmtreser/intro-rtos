# Instalar módulos con MIP

Desde la versión 1.20, el firmware de Micropython trae consigo una herramienta llamada mip que nos permite instalar módulos o bibliotecas en nuestra placa. Se llama mip (mip install packages) y se usa en reemplazo de upip, que es similar a la herramienta pip de Python en una PC.

**mip** permite la instalación de módulos desde el repositorio oficial `micropython-lib` como así también desde cualquier otro repositorio de *Github* o en general desde cualquier sitio de Internet. Si disponemos de una placa con conexión a Internet, nos permitirá descargar e instalar directamente los módulos que le pidamos. Y si nuestra placa no tiene conexión, como en el caso de una Pico, podemos emplear como alternativa la herramienta `mpremote` para realizar la instalación.

## Usando mip

Desde el REPL, hay que importar el módulo mip, para luego poder instalar paquetes. Por ejemplo, para instalar el módulo `ssd1306` que sirve para controlar un display, que se encuentra en el repositorio `micropython-lib`, debemos:

```python
import mip
mip.install ("ssd1306")
```

En este caso el módulo se encuentra en formato `.mpy`, es decir precompilado, así que mip lo descarga directamente en ese formato.

mpi también permite instalar módulos ubicados en otros repositorios o, en general, en cualquier sitio de Internet. Sólo debemos proveer la dirección completa para que mpi lo encuentre. En el siguiente ejemplo, instalamos el módulo `ahtx10` para poder leer un sensor AHT10 de temperatura y humedad que está en [este repositorio](https://github.com/targetblank/micropython_ahtx0).

```python
import mip
mip.install ("https://github.com/targetblank/micropython_ahtx0/blob/master/ahtx0.py")
```

## Usando mpremote

Para instalar módulos en placas que no cuentan con Wifi para conectar a Internet, debemos tener instalado [mpremote](https://docs.micropython.org/en/latest/reference/mpremote.html) en una PC y la placa conectada a la PC a través del puerto USB.

- Instalar mpremote con `pip install mpremote`
- Instalar el módulo SSD1306 en la placa `mpremote mip install ssd1306`
- Instalar el módulo AHT10 en la placa `mpremote mip install ("https://github.com/targetblank/micropython_ahtx0/blob/master/ahtx0.py")`
