# Sumatoria de números pares
# La función se llama mediante pares(cantidad)

def pares(cant):
    aux = 0
    for numero in range(2,cant,2):
        aux = aux + numero
    return aux

cant = input ("Ingrese el máximo: ") 
cant = int(cant) + 2
print ("El resultado es", pares(cant))