#!/bin/bash

mi_variable="hola mundo"

if [ "$mi_variable" == "hola mundo" ]; then
    echo "La variable es igual a 'hola mundo'"
fi

mi_variable="hola"

if [[ $mi_variable == "hola" ]]; then
    echo "La variable es igual a 'hola'"
fi