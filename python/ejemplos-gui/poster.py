# Aplicacion con GUIZERO
# Manejo de texto

from guizero import App, Text

# Creacion de la ventana
app = App("Buscado")
app.bg = "#FBFBD0"

# Objeto de texto
wanted_text = Text(app, "BUSCADO")
wanted_text.text_size = 50
wanted_text.text_color = "brown"
wanted_text.font = "Courier"

# Lazo infinito
app.display()