#!/bin/bash

# Códigos de Colores Básicos
# Los colores básicos se pueden aplicar utilizando la secuencia \e[, seguida del 
# código del color, y finalizando con m.

# Texto:
Negro='\e[30m'
Rojo='\e[31m'
Verde='\e[32m'
Amarillo='\e[33m'
Azul='\e[34m'
Magenta='\e[35m'
Cian='\e[36m'
Blanco='\e[37m'

# Fondo:
F_Negro='\e[40m'
F_Rojo='\e[41m'
F_Verde='\e[42m'
F_Amarillo='\e[43m'
F_Azul='\e[44m'
F_Magenta='\e[45m'
F_Cian='\e[46m'
F_Blanco='\e[47m'

# Resetear color:
NC='\e[0m'

echo -e "\e[35mEste texto es magenta.\e[0m"
echo -e "${Azul}Lorem Ipsum is simply dummy text.${NC}"
echo -e "${F_Amarillo}Lorem Ipsum has been the industry's standard.${NC}"