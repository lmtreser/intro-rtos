validar = [1, 2, 3, 4, 5, 6, 7, 8, 9]
while True:
    try:
        posicion = int(input ())
        validar.remove(posicion)
        break
    except ValueError:
        print("Oops! No era válido. Intente nuevamente...")

print(validar)

