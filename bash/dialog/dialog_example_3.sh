#!/bin/bash

while true; do
    # Menú principal
    OPCION=$(dialog --stdout --menu "Menú Principal" 15 50 3 \
        1 "Ver información del sistema" \
        2 "Configurar red" \
        3 "Salir")

    case $OPCION in
        1)
            dialog --msgbox "Información del sistema:\n\n$(uname -a)" 15 60
            ;;
        2)
            dialog --inputbox "Ingrese la nueva IP:" 10 50 2>ip.txt
            if [ $? -eq 0 ]; then
                IP=$(<ip.txt)
                dialog --msgbox "Se configuraría la IP en: $IP" 10 50
            fi
            ;;
        3)
            dialog --yesno "¿Seguro que quiere salir?" 10 40
            [ $? -eq 0 ] && break
            ;;
        *)
            break
            ;;
    esac
done

clear