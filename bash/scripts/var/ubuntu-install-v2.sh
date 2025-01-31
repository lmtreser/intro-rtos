 #! /bin/bash

 # Utilizamos el modificador -e para agregar colores "\e[0;35texto\e[0m"
 # Negro = 0;30
 # Gris oscuro = 1;30
 # Azul = 0;34
 # Azul resaltado = 1;34
 # Verde = 0;32
 # Verde resaltado = 1;32
 # Cian = 0;36
 # Cyan resaltado = 1;36
 # Rojo = 0;31
 # Rojo resaltado = 1;31
 # Púrpura = 0;35
 # Púrpura resaltado = 1;35
 # Café = 0;33
 # Amarillo = 1;33
 # Gris = 0;37
 # Blanco = 1;37

 # Mensaje de bienvenida y tiempo de espera
echo -e "\n\e[1;32m*** INSTALACION DESATENDIDA DE UBUNTU ***\e[0m\n"
sleep 1s

 # Crea un archivo de registro con un timestamp
date +"%D - %T" >> log.txt
echo "*****INICIO DE LA INSTALACION*****" >> log.txt

 # ENTORNOS DE ESCRITORIO
echo -e "\e[0;34mElija el entorno de escritorio a instalar:\e[0m"
echo "   (1) XFCE"
echo "   (2) FLUXBOX"
echo "   (3) CONTINUAR SIN INSTALAR NADA"
echo ""
read -p ">>> " VAR1

date +"%D - %T" >> log.txt
echo "*****ENTORNO DE ESCRITORIO*****" >> log.txt

case $VAR1 in
	1) sudo apt-get install xubuntu-desktop | tee -a log.txt ;;
	2) sudo apt-get install fluxbox | tee -a log.txt ;;
	3) echo "Nada para instalar" >> log.txt ;;
	*) echo -e "ERROR: OPCION INCORRECTA\n" | tee -a log.txt ;;
esac

 # PROGRAMAS
echo -e "\n\e[0;31mElija los programas a instalar:\e[0m"
echo "   (1) ARDUINO"
echo "   (2) SAKURA TERMINAL"
echo "   (3) THE GIMP"
echo "   (4) CONTINUAR SIN INSTALAR NADA"
echo ""
read -p ">>> " VAR2

date +"%D - %T" >> log.txt
echo "*****PROGRAMAS VARIOS*****" >> log.txt

case $VAR2 in
	1) sudo apt-get install arduino | tee -a log.txt ;;
	2) sudo apt-get install sakura | tee -a log.txt ;;
	3) sudo apt-get install gimp | tee -a log.txt ;;
	4) echo "Nada para instalar" >> log.txt ;;
	*) echo -e "ERROR: OPCION INCORRECTA\n" | tee -a log.txt ;;
esac

 # DRIVERS
echo -e "\n\e[0;33mElija los drivers a instalar:\e[0m"
echo "   (1) CODECS PROPIETARIOS"
echo "   (2) SOPORTE PARA DVD ENCRIPTADO"
echo "   (3) COMPLEMENTOS DE COMPRESION"
echo "   (4) CONTINUAR SIN INSTALAR NADA"
echo ""
read -p ">>> " VAR3

date +"%D - %T" >> log.txt
echo "*****COMPLEMENTOS*****" >> log.txt

case $VAR3 in
	1) sudo apt-get install ubuntu-restricted-extras | tee -a log.txt ;;
	2) sudo apt-get install libdvdread4 | tee -a log.txt ;;
	3) sudo apt-get install rar unace p7zip-full p7zip-rar sharutils mpack arj | tee -a log.txt ;;
	4) echo "Nada para instalar" >> log.txt ;;
	*) echo -e "ERROR: OPCION INCORRECTA\n" | tee -a log.txt ;;
esac

date +"%D - %T" >> log.txt
echo "*****FIN DE INSTALACION*****" >> log.txt
echo -e "\n\e[1;32m*** INSTALACION TERMINADA ***\e[0m"