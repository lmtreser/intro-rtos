# Creación de procesos en Python utilizando el módulo multiprocessing
# Creado 24 de mayo de 2024

import multiprocessing
import os, time

# child_process será ejecutada por el proceso hijo
def child_process():
    print(f"Child Process ID: {os.getpid()} - Parent Process ID: {os.getppid()}")
    time.sleep(1)

def main():
    
    print(f"Main Process ID: {os.getpid()}")
    
    # Crear el proceso hijo
    process = multiprocessing.Process(target=child_process, args=())    
    # Iniciar el proceso hijo
    process.start()
    # Esperar a que el proceso hijo termine
    process.join()
    
    print("Child process has finished.")

if __name__ == "__main__":
    main()
