# Registrador de datos (datalogger)
# Timestamp + Sensor de temperatura
# Viernes 29 de octubre de 2021

import time, random

while (True):
    
    # Leer sensor de temperatura (simulación)
    temperatura = random.randint(0, 40)
    
    # Obtener fecha y hora
    tiempo = (time.localtime())
    
    # Separar campos
    dia = tiempo[2]
    mes = tiempo[1]
    hora = tiempo[3]
    min = tiempo[4]
    seg = tiempo[5]
    
    # Formatear el registro tiempo/hora
    timestamp = "{:02}".format(dia) + "{:02}".format(mes) + "{:02}".format(hora) + "{:02}".format(min) + "{:02}".format(seg)
    print(timestamp,": ",temperatura, "°C")
    
    # Almacenar la información en un archivo
    file=open ("datalogger.dat", "a")
    file.write (timestamp + "\n")
    file.close()
    
    # Registrar datos cada dos segundos
    time.sleep(2)
