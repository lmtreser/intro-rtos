# join() a Thread

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
    x = threading.Thread(target=thread_function, args=(1,))
    logging.info("Main    : antes de ejecutar el thread")
    
    # Arranca el hilo
    x.start()
    logging.info("Main    : esperando a que el thread finalice")   
    # Espera a que el hilo termine para finalizar el proceso
    x.join()
    logging.info("Main    : listo")
