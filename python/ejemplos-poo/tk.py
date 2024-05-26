import tkinter as tk

# funcion asociada al boton
def hola():
    print("Hola mundo")

# creo la ventana
app = tk.Tk()
# tamano de la ventana
app.geometry("640x480")

# creando un boton
button = tk.Button(app, text = "Hola", command = hola)
# enpaqueto el boton
button.pack()

# bucle infinito, siempre al final
app.mainloop()