#!/bin/bash

# sudo apt install dialog

dialog --backtitle "Mi App" --title "Menú principal" --menu "Elige una opción" 15 50 4 \
1 "Iniciar sistema" \
2 "Configurar red" \
3 "Apagar" 2>temp.txt

opcion=$(<temp.txt)
rm temp.txt

case $opcion in
    1) echo "Iniciando sistema..." ;;
    2) echo "Configurando red..." ;;
    3) echo "Apagando..." ;;
esac
