# Al programa anterior le agregamos objetos
import tkinter as tk

# Clase para la ventana principal
class MainWindow:
    def __init__(self, root):
        root.geometry("640x480")
        # creando un boton
        button = tk.Button(app, text = "Hola", command = self.hola)
        # enpaqueto el boton
        button.pack()
    # funcion asociada al boton
    def hola(self):
        print("Hola mundo")

# creo la ventana
app = tk.Tk()
# tamano de la ventana
window = MainWindow(app)
# bucle infinito, siempre al final
app.mainloop()