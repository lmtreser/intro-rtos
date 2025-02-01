# Autor: Ernesto Tolocka (profe Tolocka)
# Fecha de Creación: 15-12-2024
# Descripción: Programa para medir temperatura y humedad con la placa XIAO RP2040 y el módulo Grove DHT11.
# 	Muestra valores en OLED de placa de expansión
# 	Usa fonts grandes y bitmaps
# 	Muestra TH actual, max, min, promedio y curvas de valores
# Licencia: MIT

from time import sleep
from machine import Pin, SoftI2C, PWM
from ssd1306 import Display
from xglcd_font import XglcdFont

from collections import deque  #doble-ended queue

from dht import DHT11

################  Constantes ####################

#Equivalencias entre nombres de pines y GPIOs
D0 = 26
D1 = 27
D2 = 28
D3 = 29
D4 = 6
D5 = 7
D6 = 0
D7 = 1
D8 = 2
D9 = 4
D10 = 3

# Pines de I2C de la RP2040
SDA_PIN = D4
SCL_PIN = D5

# Pin de conexion del DHT11
DHT11_PIN = D7

#Buzzer
BUZZER_PIN = D3

#Botón
BUTTON_PIN = D1

# Cantidad de valores a graficar
maxValues = 100

# Tiempo entre mediciones (seg)
sampleTime = 1

# Modos de visualizacion
modes = ["Values", "Min", "Max", "Avg", "PlotTemp", "PlotHum"]

####################  Funciones ###################

def printBig (temp, hum):
    #Imprime dos valores con font grande
    
    tempStr = f"{temp:.1f}"
    humStr  = f"{hum:.0f}"
    
    #Imprime valores con numeros grandes
    #Borra antes porque el "1" no tapa
    display.draw_text(5, 31, "     ", perfect, False)
    display.draw_text(5, 31, tempStr, perfect, False)
    display.draw_text(85, 31, "   ", perfect, False)  
    display.draw_text(85, 31, humStr, perfect, False)

def showBitmaps ():
    #Mostrar bitmaps
    display.draw_bitmap("images/TempIcon.mono", 25, 0, 32, 32, True)
    display.draw_bitmap("images/HumIcon.mono",  85, 0, 32, 32, True)

def readButton ():
    # Lee el User Button de la placa de expansion en D1
    # Retorna el valor leido
    return (button.value())
    
def beep():
    # Hace un beep en el buzzer pasivo
    buzzer = PWM(Pin(BUZZER_PIN))
    buzzer.freq(1000)
    buzzer.duty_u16(32768)  # 50% Duty Cycle

    sleep(0.1)
    buzzer.deinit()  #Libera recursos

        
def showTH (temp, hum):
    # Muestra TyH actual con bitmaps
    
    # Imprime valores con font grande
    printBig (temp, hum)
    
    # Muestra bitmaps de temp y hum
    showBitmaps ()

    #Actualizar pantalla
    display.present()
    

def plotHum (values):
    # Grafica los valores de humedad
    
    maxHum = 100
    
    display.draw_rectangle(20, 4, 104, 56, invert=False)
    
    #Escala de valores de humedad
    display.draw_text(0, 0, "100", fixed, False)
    display.draw_text(5, 28, "50", fixed, False)
    display.draw_text(10, 54, "0", fixed, False)
    
    #Titulo
    display.draw_text(5, 15, "H", fixed, False)

    #Plotear los valores almacenados
    x = 22
    for i in values:
        h = int (i[1]*56/maxHum)  #Escalar
        display.draw_vline(x, 5, 56-h, invert=True)
        display.draw_vline(x, 60-h, h, invert=False)
        x=x+1
    
    display.present ()

def plotTemp (values):
    # Grafica los valores de temperatura
    
    maxTemp = 50
    
    display.draw_rectangle(20, 4, 104, 56, invert=False)
    
    #Escala de valores de humedad
    display.draw_text(5, 0, "50", fixed, False)
    display.draw_text(5, 28, "25", fixed, False)
    display.draw_text(10, 54, "0", fixed, False)
    
    #Titulo
    display.draw_text(5, 15, "T", fixed, False)
    
    #Plotear los valores almacenados
    x = 22
    for i in values:
        h = int (i[0]*56/maxTemp)  #Escalar
        display.draw_vline(x, 60-h, h, invert=False)
        x=x+1
    
    display.present ()

def showMin (values):
    #Muestra valores mínimos de las últimas 100 mediciones
    
    #Buscar los mínimos
    tempMin = 50
    humMin = 100
    
    for value in values:
        if (value[0] < tempMin):  #Temperatura
            tempMin = value[0]
        if (value[1] < humMin):   #Humedad
            humMin = value[1]
    
    # Imprime valores con font grande
    printBig (tempMin, humMin)
    
    # Muestra bitmaps
    showBitmaps ()

    display.draw_text(0, 0, "MIN", fixed, False)

    #Actualizar pantalla
    display.present()

def showMax (values):
    #Muestra valores máximos de las últimas 100 mediciones
    tempMax = 0
    humMax = 0
    
    for value in values:
        if (value[0] > tempMax):  #Temperatura
            tempMax = value[0]
        if (value[1] > humMax):   #Humedad
            humMax = value[1]
    
    # Imprime valores con font grande
    printBig (tempMax, humMax)
    
    # Muestra bitmaps
    showBitmaps ()
    
    display.draw_text(0, 0, "MAX", fixed, False)

    #Actualizar pantalla
    display.present()

def showAvg (values):
    #Muestra valores promedio de las últimas 100 mediciones
    tempSum = 0
    humSum = 0
    
    for value in values:
        tempSum = tempSum + value[0]   #Temperatura
        humSum  = humSum  + value[1]   #Humedad
    
    tempAvg = tempSum / len(values)
    humAvg  = humSum  / len(values)

    # Imprime valores con font grande
    printBig (tempAvg, humAvg)
    
    # Muestra bitmaps
    showBitmaps ()
    
    display.draw_text(0, 0, "AVG", fixed, False)

    #Actualizar pantalla
    display.present()

def printError ():
    
    display.clear()

    # Mensaje de error
    display.draw_text(0, 0, "ERROR Sensor!", fixed, False)

    #Actualizar pantalla
    display.present()
    
####################  Código principal  ###################

#Crear objeto I2C
i2c = SoftI2C(freq=400000, scl=Pin(SCL_PIN), sda=Pin(SDA_PIN)) 

#Crear objeto display
display = Display(i2c=i2c, width=128, height=64)

#Crear objeto sensor
sensorTH = DHT11 (Pin(DHT11_PIN))

# Crear objeto para el User button de la placa
button = Pin (D1, Pin.IN, Pin.PULL_UP)

# Carga fonts
perfect = XglcdFont('fonts/PerfectPixel_23x32.c', 23, 32)
fixed   = XglcdFont('fonts/FixedFont5x8.c',5,8)

# Crear objeto lista para guardar los valores para el gráfico
listTH = deque ([], maxValues)  #No usa maxlen=

# Arranca mostrando valores
modeIndex = 0

# Reset condicion de error
errorFlag = False

# Loop
while (True):
        
    # Medir temperatura y humedad
    try:        
        sensorTH.measure ()
    
        # Separar valores
        temp = sensorTH.temperature()
        hum  = sensorTH.humidity()
        
    except Exception as e:
        print(f"Error al leer el sensor: {e}")
        printError ()
        sleep (5)
 
        errorFlag = True
        
        continue  # Saltar lo que sigue    
    
        # Sigue si no hay error de lectura
    
    if (errorFlag==True):         #Viene de condicion de error
        errorFlag = False
        print ("Limpiar!")

        display.clear ()
        
    # Guardarlo en la lista (deque)
    listTH.append ((temp,hum))

    # Imprimir por consola
    print (temp,"grados")
    print (hum ,"%")
    
    # Cambiar la visualizacion si pulsan boton
    if (readButton()==0):
        beep ()
        modeIndex = (modeIndex + 1) % len (modes)
        display.clear()

    # Mostrar la visualizacion activa
    if (modes[modeIndex] == "Values"):
        showTH (temp, hum)
    elif (modes[modeIndex] == "Min"):
        showMin (listTH)
    elif (modes[modeIndex] == "Max"):
        showMax (listTH)
    elif (modes[modeIndex] == "Avg"):
        showAvg (listTH)
    elif (modes[modeIndex] == "PlotTemp"):
        plotTemp (listTH)
    else:
        plotHum (listTH)
            
    # Esperar para la próxima medición
    sleep(sampleTime)
