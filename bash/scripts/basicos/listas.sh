#!/bin/bash

frutas=(manzana banana naranja)

echo ${frutas[0]}  # Imprime "manzana"
echo ${frutas[1]}  # Imprime "banana"
echo ${frutas[@]}  # Imprime "manzana banana naranja"

for elemento in "${frutas[@]}"; do
    echo "for #1 - Acciones con $elemento"
done

for fruta in "${frutas[@]}"; do
    echo "for #2 - Fruta: $fruta"
done

for ((i=0; i<${#frutas[@]}; i++)); do
    echo "for #3 - Fruta ${i}: ${frutas[i]}"
done