# Trabajando con muchos hilos

import logging
import threading
import time

def thread_function(name):
    logging.info("Thread %s: comenzando", name)
    time.sleep(2)
    logging.info("Thread %s: finalizando", name)

if __name__ == "__main__":
    format = "%(asctime)s: %(message)s"
    logging.basicConfig(format=format, level=logging.INFO,
                        datefmt="%H:%M:%S")

    # Crear varios hilos
    threads = list()
    for index in range(3):
        logging.info("Main    : crear y comenzar el thread %d.", index)
        x = threading.Thread(target=thread_function, args=(index,))
        threads.append(x)
        x.start()

    for index, thread in enumerate(threads):
        logging.info("Main    : antes de finalizar el thread %d.", index)
        thread.join()
        logging.info("Main    : thread %d listo", index)
