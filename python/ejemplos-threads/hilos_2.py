# Los objetos LOCK permiten gestionar los bloqueos que evitan que los hilos
# modifiquen variables compartidas al mismo tiempo. El método acquire() permite
# que un hilo bloquee a otros hilos en un punto del programa, donde se leen y
# actualizan datos, hasta que dicho hilo libere el bloqueo con el método release().
# En el momento que se produzca el desbloqueo otro hilo (o el mismo) podrá bloquear
# de nuevo.

import threading

total = 0


def acumulador():

    global total
    contador = 0
    # Devuelve el nombre del hilo actual
    hilo_actual = threading.current_thread().getName()

    while contador < 20:
        print("Esperando para bloquear a:", hilo_actual)
        bloquear.acquire()
        try:
            contador += 1
            total += 5
            print("Bloqueado por:", hilo_actual, "- Contador:", contador)
            print("Total:", total)

        finally:
            print("Liberado bloqueo por:", hilo_actual)
            print("------")
            bloquear.release()

bloquear = threading.Lock()
hilo1 = threading.Thread(name="Hilo 1", target=acumulador)
hilo2 = threading.Thread(name="Hilo 2", target=acumulador)
hilo1.start()
hilo2.start()
