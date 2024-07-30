#!/bin/bash

# Funcion para chequear si un comando existe
command_exists() {
    command -v "$1" &>/dev/null
}

read -p "Ingrese al paquete a comprobar: " paquete

# Verifica si un paquete está instalado
if ! command_exists $paquete; then
    echo "El paquete no está instalado. Ejecute:"
    echo "sudo apt-get install $paquete"
else
    echo "El paquete está instalado en el sistema"
fi
