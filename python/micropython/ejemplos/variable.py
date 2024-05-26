# Mostrar la dirección en memoria de una variable

datos = "Variable datos con dirección:"

direccion = hex(id(datos))
print(datos, direccion)
