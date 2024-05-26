# Aplicacion con GUIZERO
# HOLA MUNDO!

from guizero import App, Text

app = App (title="Hola mundo")
mensaje = Text(app, text="Bienvenido a mi aplicacion")
app.display()