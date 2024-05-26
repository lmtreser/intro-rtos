# Los objetos barrera (barrier) son otro mecanismo de sincronización de hilos. 
# Como su propio nombre sugiere actúan como una verdadera barrera que mantiene
# los hilos bloqueados en un punto del programa hasta que todos hayan alcanzado 
# ese punto. En el siguiente ejemplo se inician cinco hilos que obtienen un número
# aleatorio y permanecen bloqueados en el punto donde se encuentra el método wait() 
# a la espera de que el último hilo haya obtenido su número. Después, continúan 
# todos mostrando el factorial del número obtenido en cada caso. 

import threading, random, math

def funcion1(barrera):
    nom_hilo = threading.current_thread().name 
    print(nom_hilo, 'esperando con', barrera.n_waiting, 'hilos más')
    numero = random.randint(1,10)
    ident = barrera.wait()
    print(nom_hilo, 'ejecutando después de la espera', ident)
    print('El factorial de', numero, 'es', math.factorial(numero))

NUM_HILOS = 4
barrera = threading.Barrier(NUM_HILOS)
hilos = [threading.Thread(name='Hilo-%s' % i, 
                          target=funcion1, 
                          args=(barrera,),
                          ) for i in range(NUM_HILOS)]

for hilo in hilos:
    print(hilo.name, 'comenzando a ejecutarse')
    hilo.start()