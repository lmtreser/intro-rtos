# Colas

import time
import multiprocessing

def get_elements(queue):
    while not queue.empty():
        element = queue.get(block=True)
        print(f"El elemento es: {element}")

if __name__ == '__main__':
    manager = multiprocessing.Manager()
    queue = manager.Queue()

    for x in range(1, 21):
        queue.put(x)

    print("La cola ya posee elementos")

    process1 = multiprocessing.Process(target=get_elements, args=(queue, ))
    process2 = multiprocessing.Process(target=get_elements, args=(queue, ))
    process3 = multiprocessing.Process(target=get_elements, args=(queue, ))

    process1.start()
    process2.start()
    process3.start()

    process1.join()
    process2.join()
    process3.join()

    print("Fin de los procesos")
