#!/bin/bash

contador=0

while [ $contador -lt 5 ]; do
    echo "Contador: $contador"
    ((contador++))
done