#!/bin/bash

# Crear un archivo con timestamp en el nombre

# Obtener el timestamp (fecha y hora actual)
timestamp=$(date +"%Y%m%d_%H%M%S")

# Obtener solo la fecha (formato: YYYY-MM-DD)
# timestamp=$(date +"%Y-%m-%d")

# Crear un archivo con el timestamp en el nombre
nombre_archivo="log_$timestamp.txt"
echo "Este es un archivo con timestamp" > "$nombre_archivo"

# Confirmación
echo "Archivo creado: $nombre_archivo"
