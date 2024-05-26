class Soldado:
    
    def __init__(self, nombre, raza):
        self.nombre = nombre
        self.raza = raza
        self.arma = ""
        if raza == "Elfo":
            self.vida = 80
            self.velocidad = 100
            self.coste = 200
        elif raza == "Humano":
            self.vida = 100
            self.velocidad = 7
            self.coste = 100
        elif raza == "Enano":
            self.vida = 120
            self.velocidad = 3
            self.coste = 180

    def mi_arma(self, arma):
        self.arma = arma
#creamos una lista ejercito para almacenar los soldados creados
ejercito = []
cantidad_soldados = int(input("¿Cuántos soldados queres crear?: "))
#recorremos la cantidad de soldados creados
for i in range(cantidad_soldados):
    #preguntamos nombre y raza
    nombre = input("Nombre del nuevo soldado: ")
    raza = input("Raza del nuevo soldado (Elfo/Humano/Enano): ")
    #creamos el nuevo soldado
    soldado = Soldado(nombre, raza)
    #guardamos el objeto soldado en la lista ejercito
    ejercito.append(soldado)
#llamamos a cada objeto por su posición en la lista ejercito
for i in range(len(ejercito)):
    print(ejercito[i].nombre)