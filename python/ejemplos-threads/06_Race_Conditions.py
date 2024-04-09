# Condiciones de carrera

import concurrent.futures
import logging
import time

class BaseDatos:
    def __init__(self):
        self.value = 0

    def update(self, name):
        logging.info("Thread %s: comenzando la actualizacion", name)
        local_copy = self.value
        local_copy += 1
        time.sleep(0.1)
        self.value = local_copy
        logging.info("Thread %s: finalizando la actualizacion", name)

if __name__ == "__main__":
    format = "%(asctime)s: %(message)s"
    logging.basicConfig(format=format, level=logging.INFO,
                        datefmt="%H:%M:%S")

    database = BaseDatos()
    logging.info("Testing update. Starting value is %d.", database.value)
    with concurrent.futures.ThreadPoolExecutor(max_workers=2) as executor:
        for index in range(2):
            executor.submit(database.update, index)
    logging.info("Probando actualizaciones. Valor de finalizacion es %d.", database.value)
