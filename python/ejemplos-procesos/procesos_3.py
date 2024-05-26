# Creación de procesos en Python utilizando el módulo multiprocessing
# Creado 24 de mayo de 2024

import multiprocessing
import os

def exec_child_program():
    print(f"Child Process ID before exec: {os.getpid()}")
    # Reemplazar la imagen del proceso hijo con otro programa
    os.execlp("echo", "echo", "Hello from the new program!")

def main():
    print(f"Main Process ID: {os.getpid()}")

    # Crear el proceso hijo
    process = multiprocessing.Process(target=exec_child_program)
    # Iniciar el proceso hijo
    process.start()
    # Esperar a que el proceso hijo termine
    process.join()
    
    print("Child process has finished.")

if __name__ == "__main__":
    main()
