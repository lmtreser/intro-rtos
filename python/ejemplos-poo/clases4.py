# HERENCIA y MIXINS

# Superclase
class MixingInstancia:
    def instancia(self):
        print(hex(id(self)))

class MixingClase:
    def clase(self):
        print(type(self).__name__)

# Clase A hereda de las dos superclase sus metodos
class A(MixingInstancia, MixingClase):
    pass

# Clase B hereda de la superclase sus metodos
class B(MixingInstancia):
    pass

a = A()
a.instancia()
a.clase()

b = B()
b.instancia()