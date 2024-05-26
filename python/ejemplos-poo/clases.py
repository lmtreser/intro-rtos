class Soldado:
    #definimos el constructor, es decir, la función __init__
    #y situamos los parámetros que queremos y el obligado self al principio
    def __init__(self, nombre, raza):
        self.nombre = nombre
        self.raza = raza
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

    def armamento(self, arma):
        self.arma = arma
    
#creo mi primer soldado e indico que es de la clase Soldado
primer_soldado = Soldado("Legolas", "Elfo")
primer_soldado.armamento("Arco")
#imprimimos datos de nuestro soldado
print("Nombre:")
print(primer_soldado.nombre)
print("Raza:")
print(primer_soldado.raza)
print("Vida:")
print(primer_soldado.vida)
print("Velocidad:")
print(primer_soldado.velocidad)
print("Coste de entrenamiento:")
print(primer_soldado.coste)
#veamos de qué tipo es la variable primer_soldado
print(type(primer_soldado))

#creamos más soldados
segundo_soldado = Soldado("Marcelo", "Humano")
segundo_soldado.armamento("Espada")
tercer_soldado = Soldado("Carlos", "Enano")
tercer_soldado.armamento("Hacha")