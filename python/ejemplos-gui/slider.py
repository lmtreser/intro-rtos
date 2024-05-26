# Aplicacion con GUIZERO
# Generador de memes, uso de slider

from guizero import App, TextBox, Drawing, Combo, Slider

app = App("Generador de memes")
#app.width = 640
#app.height = 480

def dibujar():
    meme.clear()
    meme.image(0,0, "pajarito.jpg", width=380, height=620)
    meme.text(20, 20, top_text.value, color=selector_color.value, font="Courier", size=tam_fuente.value)
    meme.text(20, 320, botton_text.value)

# Cajas de texto
top_text = TextBox(app, "texto superior", command=dibujar)
botton_text = TextBox(app, "texto inferior", command=dibujar)

# Widget Combo
selector_color = Combo(app, options=["red", "brown", "blue", "white"], command=dibujar, selected="blue")

# Widget Slider
tam_fuente = Slider(app, start=20, end=40, command=dibujar)

meme = Drawing(app, width="fill", height="fill")
dibujar()

# Bucle infinito
app.display()