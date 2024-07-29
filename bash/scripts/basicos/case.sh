#!/bin/bash

echo "Ingrese un color (rojo, verde, azul): "
read color
case $color in
    rojo) echo "El color es rojo";;
    verde) echo "El color es verde";;
    azul) echo "El color es azul";;
    *) echo "Color desconocido";;
esac
