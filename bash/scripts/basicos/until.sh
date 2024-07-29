#!/bin/bash

contador=0

until [ $contador -ge 5 ]; do
    echo "Contador: $contador"
    ((contador++))
done