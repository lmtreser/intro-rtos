# Comenzando con hilos en Python mediante el modulo threading
# https://realpython.com/intro-to-python-threading/

import logging
import threading
import time

# Funcion que ejecutara el hilo
def thread_function(name):
    logging.info("Thread %s: comenzando", name)
    time.sleep(2)
    logging.info("Thread %s: finalizando", name)

if __name__ == "__main__":
    format = "%(asctime)s: %(message)s"
    logging.basicConfig(format=format, level=logging.INFO, datefmt="%H:%M:%S")
    logging.info("Main    : antes de crear el thread")
	
    # Para crear un nuevo thread, creamos un objeto de clase Thread: 
    # target: la funcion a ser ejecutada por el thread
    # args: los argumentos a ser pasados a la funcion
    x = threading.Thread(target=thread_function, args=(1,))
    logging.info("Main    : antes de ejecutar el thread")
    
    # Arranca el hilo
    x.start()
    logging.info("Main    : esperando a que el thread finalice")
    
    # Espera a que el hilo termine para finalizar el proceso
    #x.join()
    logging.info("Main    : listo")
