#!/bin/bash

# Suma simple
a=5
b=3
resultado=$((a + b))
echo "La suma de $a y $b es $resultado"

# Multiplicación
a=4
b=6
resultado=$((a * b))
echo "El producto de $a y $b es $resultado"

# Incremento
contador=10
((contador++))  # Post-incremento, primero usa el valor y luego lo incrementa
echo "Después del incremento: $contador"

# Decremento
((contador--))  # Post-decremento, primero usa el valor y luego lo decrementa
echo "Después del decremento: $contador"
