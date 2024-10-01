# Scripting básico en Bash

Un script de **Bash** es un archivo de texto que contiene comandos y sentencias de Bash. Para ejecutar un script, se puede utilizar el comando `bash nombre_script.sh` o hacer que el script sea ejecutable con `chmod +x nombre_script.sh` y luego ejecutarlo con `./nombre_script.sh`.

## Declarar un intérprete por defecto

La primera línea de un script de Bash debe ser `#!/bin/bash` (o el path al intérprete de Bash en tu sistema). Esto le indica al sistema operativo que utilice Bash para ejecutar el script y a menudo se lo conoce como *hash-bang*, *she-bang* o *sha-bang*.

Ejemplo de script básico:

```bash
#!/bin/bash
echo "Hola, mundo!"
```

Guardar este script en un archivo llamado `hola_mundo.sh`, hacerlo ejecutable con `chmod +x hola_mundo.sh` y ejecutarlo con `./hola_mundo.sh`.

## Estructura básica de un script

Generalmente la estructura de un script es la siguiente:

- Shebang (`#!/bin/bash`)
- Comentarios (`# Comentarios...`)
- Declaraciones de variables
- Sentencias de control (if, for, while, etc.)
- Llamadas a comandos y funciones
- Fin del script

### Variables

- Declarar una variable: `nombre_variable=valor`
- Acceder a una variable: `$nombre_variable`

```bash
mi_variable="hola mundo"
echo $mi_variable
```

### Entrada de ordenes (input)

- Leer entrada del usuario: `read variable`

```bash
echo "Ingrese su nombre: "
read nombre
echo "Hola, $nombre!"
```

### Operadores de comparación

- Números:
  - `-eq` igual (equal)
  - `-ne` diferente (not equal)
  - `-gt` mayor que (greater than)
  - `-lt` menor que (low than)
  - `-ge` mayor o igual que (greater than equal)
  - `-le` menor o igual que (low than equal)

- Lógicos:
  - `&&` y (and)
  - `||` o (or)

- Strings:
  - `==` igual
  - `!=` diferente
  - `>` mayor que (lexicográficamente)
  - `<` menor que (lexicográficamente)

### Condicional (if)

- Sintaxis básica: `if condición; then acciones; fi`

```bash
if [ "$mi_variable" == "hola mundo" ]; then
  echo "La variable es igual a 'hola mundo'"
fi
```

Estructura condicional if, else, y elif:

```bash
if [ condición1 ]; then
    # Bloque de código si la condición1 es verdadera
elif [ condición2 ]; then
    # Bloque de código si la condición1 es falsa y la condición2 es verdadera
else
    # Bloque de código si todas las condiciones anteriores son falsas
fi
```

```bash
read -p "Introduce un número: " num

if [ "$num" -lt 0 ]; then
    echo "El número es negativo."
elif [ "$num" -eq 0 ]; then
    echo "El número es cero."
else
    echo "El número es positivo."
fi
```

### [ versus [[

Hay 2 comandos que se usan a menudo en las declaraciones if: `[` y `[[`:

`/usr/bin/[` También conocido como *test*, es un programa que devuelve `0` si la prueba que se le pasa tiene éxito.

```bash
if [ -e file.txt ]
```

`[[` Está integrado en bash. Permite realizar pruebas como `[[ -e x.txt && -e y.txt ]]` que no funcionarían con una herramienta de línea de comandos.

```bash
if [[ -e file.txt ]]
```

Ejemplos:

- `if COMMAND` ¿*COMMAND* devolvió *0*?
- `if ! COMMAND` ¿*COMMAND* **no** devolvió *0*?
- `if [ -n "$var." ]` ¿*$var* no esta vacio?
- `if [ -d somedir ]` ¿Existe *somedir*?
- `if [ -e file.txt ]` ¿Existe *file.txt*?
- `if [ -x script.sh ]` ¿*script.sh* es ejecutable?
- `if true` *true* siempre devuelve *0* :)
- `if [ -e archivo ] && [ -e archivo2 ]` combinar con *&&* y *||*

Con `man [` se puede aprender más.

### Bucle for

- Sintaxis básica: `for variable in lista; do acciones; done`

```bash
for numero in 1 2 3; do
  echo "Número: $numero"
done
```

### Bucle while

- Sintaxis básica: `while condición; do acciones; done`
- Ejecuta las acciones mientras la condición sea verdadera

```bash
contador=0
while [ $contador -lt 5 ]; do
  echo "Contador: $contador"
  ((contador++))
done
```

### Bucle case

- Sintaxis básica: `case valor in patron1) acciones1;; patron2) acciones2;; esac`
- Compara el valor con los patrones y ejecuta las acciones correspondientes

```bash
echo "Ingrese un color (rojo, verde, azul): "
read color
case $color in
  rojo) echo "El color es rojo";;
  verde) echo "El color es verde";;
  azul) echo "El color es azul";;
  *) echo "Color desconocido";;
esac
```

### Bucle until

- Sintaxis básica: `until condición; do acciones; done`
- Ejecuta las acciones mientras la condición sea falsa
- Es similar al bucle while, pero con la condición invertida

```bash
contador=0
until [ $contador -ge 5 ]; do
  echo "Contador: $contador"
  ((contador++))
done
```

## Listas

En Bash, las listas se pueden implementar utilizando arreglos (*arrays*). Un arreglo es una variable que puede almacenar múltiples valores, y se puede acceder a cada valor utilizando un índice.

Para declarar un arreglo en Bash: `nombre_arreglo=(valor1 valor2 valor3 ...)`:

```bash
frutas=(manzana banana naranja)
```

Para acceder a un valor en el arreglo: `${nombre_arreglo[indice]}`:

```bash
echo ${frutas[0]}  # Imprime "manzana"
echo ${frutas[1]}  # Imprime "banana"
```

También se puede utilizar `${nombre_arreglo[@]}` para acceder a todos los valores en el arreglo:

```bash
echo ${frutas[@]}  # Imprime "manzana banana naranja"
```

Otras operaciones que se pueden realizar con arreglos en Bash incluyen:

- `nombre_arreglo=("${nombre_arreglo[@]}" "nuevo_valor")`: Agrega un nuevo valor al final del arreglo.
- `nombre_arreglo=("${nombre_arreglo[@]:0:${#nombre_arreglo[@]}-1}")`: Elimina el último valor del arreglo.
- `nombre_arreglo=("${nombre_arreglo[@]/valor_a_reemplazar/nuevo_valor}")`: Reemplaza un valor en el arreglo.

Para recorrer una lista en Bash utilizando un bucle `for`:

```bash
for elemento in "${lista[@]}"; do
  # Acciones con $elemento
done
```

Donde `lista` es el nombre de la lista y `elemento` es la variable que tomará cada valor de la lista en cada iteración. Por ejemplo:

```bash
frutas=(manzana banana naranja)
for fruta in "${frutas[@]}"; do
  echo "Fruta: $fruta"
done
```

Esto imprimirá:

```bash
Fruta: manzana
Fruta: banana
Fruta: naranja
```

También se puede utilizar `for ((i=0; i<${#lista[@]}; i++)); do` para recorrer la lista utilizando un índice, donde `${#lista[@]}` devuelve el número de elementos en la lista:

```bash
# Definir un array
frutas=("manzana" "banana" "naranja")

# Obtener la longitud del primer elemento (manzana)
echo "Longitud de 'manzana': ${#frutas[0]}"
```

```bash
frutas=(manzana banana naranja)
for ((i=0; i<${#frutas[@]}; i++)); do
  echo "Fruta ${i}: ${frutas[i]}"
done
```

Esto imprimirá:

```bash
Fruta 0: manzana
Fruta 1: banana
Fruta 2: naranja
```

## Funciones

En Bash, una función es un bloque de código que se puede llamar varias veces desde diferentes partes de un script.

### Declarar una función

- Sintaxis básica: `nombre_funcion() { acciones; }`

```bash
saludar() {
  echo "Hola, $1!"
}
```

En este ejemplo, se declara una función llamada `saludar` que toma un argumento (`$1`) y lo utiliza para saludar.

### Llamar a una función

- Sintaxis básica: `nombre_funcion argumentos`

```bash
saludar Juan
```

En este ejemplo, se llama a la función `saludar` con el argumento `Juan`, lo que produce la salida `Hola, Juan!`.

### Pasar argumentos a una función

- Los argumentos se pasan separados por espacios
- Los argumentos se acceden dentro de la función con `$1`, `$2`, `$3`, etc.

```bash
sumar() {
  echo "$1 + $2 = $(( $1 + $2 ))"
}
sumar 2 3
```

En este ejemplo, se declara una función `sumar` que toma dos argumentos, los suma y muestra el resultado.

## Recursos

- [Curso de BASH en YouTube](https://youtu.be/geyLYfZcdtQ?si=oQMi_0npN5E9pyXA)
- [La guía definitiva de línea de comandos de Linux: tutorial completo de bash](https://www.freecodecamp.org/espanol/news/la-guia-definitiva-de-linea-de-comandos-de-linux-tutorial-completo-de-bash/)
- [Bash Script: qué es, cómo escribir uno y ejemplos](https://www.hostinger.com.ar/tutoriales/bash-script-linux)
- [Scripts en Bash](https://atareao.es/tutorial/scripts-en-bash/)
- [El terminal](https://atareao.es/tutorial/terminal/)
- [Programación de tareas con cron](https://atareao.es/software/utilidades/programacion-de-tareas-con-cron/)
