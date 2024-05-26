# Aplicacion con GUIZERO
# Generador de memes

from guizero import App, TextBox, Drawing

app = App("Generador de memes")
#app.width = 640
#app.height = 480

def dibujar():
    meme.clear()
    meme.image(0,0, "pajarito.png", width=380, height=620)
    meme.text(20, 20, top_text.value, color="red", font="Courier", size=40)
    meme.text(20, 320, botton_text.value)

# Cajas de texto
top_text = TextBox(app, "texto superior", command=dibujar)
botton_text = TextBox(app, "texto inferior", command=dibujar)

meme = Drawing(app, width="fill", height="fill")
dibujar()

# Bucle infinito
app.display()