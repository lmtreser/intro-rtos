import multiprocessing

def suma_numeros(lista):
    print(f'La suma de los números es: {sum(lista)}')

if __name__ == "__main__":
    lista1 = [1, 2, 3, 4, 5]
    lista2 = [6, 7, 8, 9, 10]

    p1 = multiprocessing.Process(target=suma_numeros, args=(lista1,))
    p2 = multiprocessing.Process(target=suma_numeros, args=(lista2,))

    p1.start()
    p2.start()

    p1.join()
    p2.join()