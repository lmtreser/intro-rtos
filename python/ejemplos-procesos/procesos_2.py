# Creación de procesos en Python utilizando el módulo multiprocessing
# Creado 24 de mayo de 2024

import multiprocessing
import os

def worker(name):
    print(f"Worker {name}: starting, Process ID: {os.getpid()}")
    print(f"Worker {name}: finishing")

def main():
    print(f"Main Process ID: {os.getpid()}")

    # Crear los procesos
    processes = []
    NUM_PROCESS = 4
    for i in range(NUM_PROCESS):
        process = multiprocessing.Process(target=worker, args=(i,))
        processes.append(process)
        process.start()

    # Esperar a que todos los procesos terminen
    for process in processes:
        process.join()

    print("All worker processes have finished.")

if __name__ == "__main__":
    main()
