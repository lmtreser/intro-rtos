""" 
    ARCHIVOS EN PYTHON
    Instituto Superior IDRA 
    Lucas Martín Treser - 19 de octubre de 2026
        
    En GNU/Linux, las operaciones de archivos interactúan con el sistema de
    archivos del kernel mediante descriptores de archivo. Python simplifica
    esto usando la función open() con diferentes modos:

      - 'w' (Write): Crea el archivo o lo sobrescribe si ya existe.
      - 'a' (Append): Abre el archivo para modificarlo/agregar contenido al
                      final sin borrar lo anterior.
      - 'r' (Read): Lee el contenido.
"""
nombre_archivo = "./idra/python_os/datos.txt"

print("Creando archivo y escribiendo...")
with open(nombre_archivo, "w") as archivo:
  archivo.write("Línea 1: Inicio del sistema.\n")

print("Modificando el archivo (agregando líneas)...")
with open(nombre_archivo, "a") as archivo:
  archivo.write("Línea 2: Proceso de respaldo iniciado.\n")
  archivo.write("Línea 3: Operación completada con éxito.\n")

print("\nLeyendo contenido final del archivo:")
with open(nombre_archivo, "r") as archivo:
  contenido = archivo.read()
  print(contenido)