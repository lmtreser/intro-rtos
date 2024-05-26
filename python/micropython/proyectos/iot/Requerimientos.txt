Escribir un programa de flujo de NodeRED que permita interactuar con un programa desarrollado sobre la placa de desarrollo que se comunique a través del protocolo MQTT.

Debe incluir mínimamente:

* Una llave en el dashboard que permita permutar entre encendido y apagado de un LED.

* Un control de colores RGB en el dashboard que permita cambiar de color a uno o varios LED NeoPixel.

* Un control deslizante en el dashboard que permita posicionar un servomotor en la placa de desarrollo para moverlo entre 10 y 170 grados.

* Generar una notificación en el dashboard al dispararse una alarma implementada en la placa de desarrollo.

* Informar en el dashboard el valor medido utilizando el conversor analógico-digital de la placa de desarrollo. Se sugiere que la medición sea de forma continua (periódica a intervalos de 1 segundo) y graficar valores históricos.

* Informar en el dashboard el valor sensado en la placa de desarrollo de temperatura y humedad de forma continua. Se sugieren graficar los valores históricos.

Para completar la tarea, se debe entregar: el programa de MicroPython usado y el json del programa de NodeRED.
