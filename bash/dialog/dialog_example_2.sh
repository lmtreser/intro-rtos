#!/bin/bash

dialog --title "Inicio" --menu "Elegí una opción" 15 50 4 \
1 "Ver estado" \
2 "Reiniciar servicio" \
3 "Salir" 2> opcion.txt

case $(<opcion.txt) in
  1) dialog --msgbox "Estado: OK" 10 30 ;;
  2) dialog --msgbox "Reiniciando..." 10 30 ;;
  3) clear; exit ;;
esac

clear
