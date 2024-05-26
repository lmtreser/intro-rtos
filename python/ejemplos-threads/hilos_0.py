# Un objeto Thread representa una determinada operación que se ejecuta
# como un subproceso independiente, es decir, representa a un hilo.

import threading

def contar():
    # Contar hasta 10
    contador = 0
    while contador < 10:
        contador += 1
        print('Hilo:',
              threading.current_thread().getName(), 'con identificador:',
              threading.current_thread().ident, '| Contador:', contador)


NUM_HILOS = 2

# Se crean dos hilos que llaman a la función contar()
for num_hilo in range(NUM_HILOS):
    hilo = threading.Thread(name='hilo-%s' % num_hilo, target=contar)
    # Se inician los dos hilos
    hilo.start()