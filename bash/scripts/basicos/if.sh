#!/bin/bash

# [ ... ]       POSIX clásico           Requiere comillas, limitado
# [[ ... ]]     Bash moderno            Soporta regex, &&,
# (( ... ))     Aritmética              Sin $, más limpio para números
# if comando    Resultado de comandos   Evalúa exit code

# Comparaciones de strings
# =     Igualdad                [ "$a" = "$b" ]     POSIX estándar
# ==    Igualdad                [ "$a" == "$b" ]    Solo en Bash
# !=    Distinto                [ "$a" != "$b" ]    —
# <     Menor alfabéticamente   [ "$a" \< "$b" ]    hay que escapar <
# >     Mayor alfabéticamente   [ "$a" \> "$b" ]    hay que escapar >
# -z    Cadena vacía            [ -z "$a" ]         true si está vacía
# -n    Cadena no vacía         [ -n "$a" ]         true si tiene algo

texto="hola mundo"

# Comparación de strings
if [ "$texto" = "hola mundo" ]; then
    echo "El texto coincide"
fi

# Cadena vacía
cadena=""

if [ -z "$cadena" ]; then
    echo "La variable está vacía"
fi

mi_variable="hola"

if [[ "$mi_variable" == "hola" ]]; then
    echo "La variable es igual a 'hola'"
fi

# Comparaciones de números
# Igual         [ "$a" -eq "$b" ]       equal
# Distinto      [ "$a" -ne "$b" ]       not equal
# Mayor que     [ "$a" -gt "$b" ]       greater than
# Menor que     [ "$a" -lt "$b" ]       less than
# Mayor o igual [ "$a" -ge "$b" ]       greater or equal
# Menor o igual [ "$a" -le "$b" ]       less or equal

a=10
b=20
texto="hola"

# Comparación numérica
if [ "$a" -lt "$b" ]; then
    echo "a es menor que b"
fi

