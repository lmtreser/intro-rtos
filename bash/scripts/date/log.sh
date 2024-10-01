#!/bin/bash

# Usar el timestamp con un log de eventos

# Nombre del archivo de log
archivo_log="evento_log.txt"

# Obtener timestamp con formato completo (YYYY-MM-DD HH:MM:SS)
timestamp=$(date +"%Y-%m-%d %H:%M:%S")

# Agregar una entrada al log con el timestamp
echo "[$timestamp] Se ejecutó el script." >> "$archivo_log"

# Confirmación
echo "Entrada agregada al log: $archivo_log"
