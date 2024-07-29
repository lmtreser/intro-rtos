#!/bin/bash

saludar() {
    echo "Hola, $1!"
}

saludar Lucas

sumar() {
    echo "$1 + $2 = $(( $1 + $2 ))"
}
sumar 2 3