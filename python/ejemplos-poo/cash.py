""" Sistema para almacén (caja registradora)
El sistema debe poder escanear un producto (el cajero puede tipear el código del producto), 
y agregarlo a la lista de productos comprados para ese cliente. Además debe mostrar el subtotal.
El cajero cuando lo desee puede finalizar la compra y el sistema deberá aplicar los descuentos 
correspondientes a los productos. Luego, el cajero indica con cuánto paga el cliente y el sistema
debe mostrar el cambio que debe devolver al cliente. """

class TipoProducto:
    def __init__(self, codigo, tipo, categoria, precio, stock):
        self.codigo = codigo
        self.tipo = tipo
        self.categoria = categoria
        self.precio = precio
        self.stock = stock

# Creo la lista de productos disponibles
almacen =[] 
producto1 = TipoProducto(50, "Desodorante", "Perfumeria", 100, 25)
almacen.append (producto1)
producto2 = TipoProducto(55, "Vino", "Bebidas", 85, 20)
almacen.append (producto2)
producto3 = TipoProducto(60, "Galletitas", "Ramos Generales", 15, 5)
almacen.append (producto3)

bucle = True
subtotal = 0
descuentos = 0
total = 0
vuelto = 0

while(bucle):
    code = int(input("Ingrese el código del producto o [1] para finalizar\n> "))

    # Asigno precios a los códigos ingresados
    for i in range(len(almacen)):
        if almacen[i].codigo == code:
            subtotal = subtotal + almacen[i].precio
        if code == 1:
            bucle = False

print("El subtotal es: $", subtotal)

pago = input("Forma de pago, ¿[E]fectivo o [T]arjeta?\n> ")
if pago == "E":
    descuentos = (subtotal * 10) / 100

print("Se aplicará el siguiente descuentos: -$", descuentos)
total = subtotal - descuentos
print("El TOTAL a pagar es: $", total)

cash = int(input("Usted paga con: $ "))
vuelto = cash - total
print("Su vuelto es: $", vuelto)
print("¡Qué tenga un buen día!")
