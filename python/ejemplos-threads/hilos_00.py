# HILOS CON ARGUMENTOS

import threading

def contar(num_hilo, **datos):
    contador = datos['inicio']
    incremento = datos['incremento']
    limite = datos['limite']
    while contador<=limite:                
        print('hilo:', num_hilo, 'contador:', contador)        
        contador+=incremento

NUM_HILOS = 3

# *args permite pasar un número variable de argumentos
# **kwargs permite pasar un número variable de argumentos con 'key: value'
for num_hilo in range(NUM_HILOS):
    hilo = threading.Thread(target=contar, 
                            args=(num_hilo,),
                            kwargs={'inicio':0, 
                                    'incremento':2,
                                    'limite':5})
    hilo.start()