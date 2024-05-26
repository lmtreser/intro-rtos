# Sincronización de hilos con objetos CONDITION

import threading
import random
import math

# Función que espera a que se generen los números

def funcion1(condicion):
    global lista
    print(threading.current_thread().name,
          'esperando a que se generen los números')
    with condicion:
        condicion.wait()
        print('Elementos:', len(lista))
        print('Suma total:', math.fsum(lista))

# Función que genera 1000 números aleatorios

def funcion2(condicion):
    global lista
    print(threading.current_thread().name,
          'generando números')
    with condicion:
        for numeros in range(1, 1001):
            entero = random.randint(1, 100)
            lista.append(entero)
        print('Se generaron 1000 números aleatorios')
        # Despertar a todos los hilos que estén esperando a la condición variable
        condicion.notifyAll()

# Función que espera por el usuario

def funcion3(condicion):
    print(threading.current_thread().name,
          'esperando el fin de la suma para finalizar la ejecución')
    with condicion:
        print('¿Desea mostrar el contenido de \'lista\'?')
        accion = input()
        if accion == 's':
            print(lista)
        else:
            print('Fin de programa')


lista = []
# Permitir a uno o más threads a esperar hasta que sean notificados por otro thread
condicion = threading.Condition()
hilo1 = threading.Thread(name='Hilo 1', target=funcion1, args=(condicion,))
hilo2 = threading.Thread(name='Hilo 2', target=funcion2, args=(condicion,))
hilo3 = threading.Thread(name='Hilo 3', target=funcion3, args=(condicion,))

hilo1.start()
hilo2.start()
hilo3.start()
