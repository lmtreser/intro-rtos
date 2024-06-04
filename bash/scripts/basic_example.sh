# Sencillo script que permite ingresar un dato, almacenar en una variable
# y aplicarlo a una condicion.

#!/bin/bash

# Definir algunos estilos
Color_Off='\033[0m'
Green='\033[0;32m'
Purple='\033[0;35m'

echo "${Purple}Sencillo script que permite ingresar un dato, almacenarlo en una variable y aplicarle una condicion.${Color_Off}"
read -p "Ingrese un numero entre 0 y 10: " numero_ingresado
echo "${Green}Ingreso el numero: $numero_ingresado ${Color_Off}"

if [ $numero_ingresado -gt 5 ]; then
    echo "El número ingresado es MAYOR que 5"
elif [ $numero_ingresado -eq 5 ]; then
    echo "El número ingresado es IGUAL a 5"
else
    echo "El número ingresado es MENOR que 5"
fi

echo "--Fin--"