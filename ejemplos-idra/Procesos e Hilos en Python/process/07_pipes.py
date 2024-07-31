# Ejemplo PIPES
# Publisher // Subscriber

import time
import multiprocessing

class Publisher(multiprocessing.Process):
    def __init__(self, connection):
        self.connection = connection
        multiprocessing.Process.__init__(self)

    def run(self):
        print("Proceso Publisher")

        for x in range(20):
            self.connection.send(f"Proceso Publisher, con el valor {x}")
            time.sleep(0.5)

        self.connection.send(None)
        self.connection.close()

        print("Conexión cerrada para Publisher")

class Subscriber(multiprocessing.Process):
    def __init__(self, connection):
        self.is_alive = True
        self.connection = connection
        multiprocessing.Process.__init__(self)

    def run(self):
        print("Proceso Subscriber")

        while self.is_alive:
            result = self.connection.recv()

            self.is_alive = result is not None

            print(result)
        else:
            self.connection.close()
            print("Conexión cerrada para Subscriber")

if __name__ == '__main__':
    connection1, connection2 = multiprocessing.Pipe()

    publisher = Publisher(connection1)
    subscriber = Subscriber(connection2)

    publisher.start()
    subscriber.start()
