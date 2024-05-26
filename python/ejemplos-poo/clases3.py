class Galleta:
    
    # Constructor
    def __init__(self, sabor = "dulce", chocolate = False):
        self.sabor = sabor
        self.chocolate = chocolate
        print("Creaste un objeto de tipo galleta")

    # Metodo
    def chocolatear(self):
        self.chocolate = True

    # Metodo String
    def __str__(self):
        resumen = "Soy una galleta " + self.sabor
        if self.chocolate:
            resumen += " con chocolate"
        return resumen

galleta = Galleta()
print(galleta)
galleta2 = Galleta("salada", True)
print(galleta2)