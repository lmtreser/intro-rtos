# Aplicacion con GUIZERO
# Manejo de imagenes

from guizero import App, Text, Picture

# Creacion de la ventana
app = App("Buscado")
app.bg = "#FBFBD0"

# Objeto de texto
wanted_text = Text(app, "BUSCADO")
wanted_text.text_size = 50
wanted_text.text_color = "brown"
wanted_text.font = "Courier"

# Importar una imagen
gato = Picture(app, image="gatito.png")
gato.width = 540
gato.height = 380

# Lazo infinito
app.display()