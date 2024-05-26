# Aplicacion con GUIZERO
# GUI interactivo

from guizero import App, Text, PushButton
from random import choice

app = App("Ultrasecreto")
titulo = Text(app, "Presione el boton rojo")

# Funciones
def botonito():
    nombre = ["Lucas", "Martin", "Frido", "Majo", "Martita"]
    apellido = ["Perez", "Lopez", "Gibson", "Thompson", "Zak"]
    espia = choice(nombre) + " " + choice(apellido)
    nomb.value = espia

# Uso de botones
boton = PushButton(app, botonito, text = "Apretar")
boton.bg = "red"
boton.text_size = 30

# Widget texto
nomb = Text(app, text="")

app.display()