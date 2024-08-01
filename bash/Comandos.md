# Comandos

## find

*find* busca los archivos especificados en todos los directorios de la computadora. La sintaxis básica es la siguiente:

```bash
find [ruta] [opciones] [expresión]
```

```bash
find /tmp -type d -print
```

- `ruta`: especifica el directorio en el que se debe comenzar la búsqueda. Si se omite, find buscará en el directorio actual.

- `opciones`: Modifican el comportamiento de la búsqueda.

- `expresión`: Define los criterios de búsqueda (por ejemplo, nombre del archivo, tipo, tamaño, etc.).

A continuación, desglosamos algunas de las opciones y expresiones más comunes:

- `path` busca el path completo, por ejemplo `-path '/home/*/*.pdf'`
- `ipath` igual que *path* pero es *case insensitive*
- `maxdepth NUM` solo niveles *NUM* descendentes cuando busca directorios
- `name` busca el nombre de archivo, por ejemplo `-name '*.txt'`
- `iname` igual que *name* pero es *case insensitive*
- `type [TYPE]` *f*: archivo regular, *l*: enlace simbolico, *d*: directorio
- `size [tamaño]` busca archivos de un tamaño específico
- `print` imprime en pantalla
- `print0` imprime en pantalla los nombres de archivos sin separación
- `delete` borra los archivos encontrados
- `perm [permisos]` busca archivos con permisos específicos.
- `exec [comando] {} \;` ejecuta un comando sobre cada archivo encontrado. `{}` es un marcador de posición para el archivo encontrado.

### Buscar archivos por nombre

Este comando busca un archivo llamado `archivo.txt` en el directorio `/home/user` y sus subdirectorios.

```bash
find /home/user -name "archivo.txt"
```

### Buscar directorios por nombre

Este comando busca directorios llamados `logs` en el directorio `/var` y sus subdirectorios.

```bash
find /var -type d -name "logs"
```

### Buscar archivos por tamaño

Este comando busca archivos mayores de 100 megabytes en el sistema de archivos a partir de la raíz (/).

```bash
find / -type f -size +100M
```

### Buscar archivos modificados recientemente

Este comando busca archivos en el directorio `/tmp` que fueron modificados en los últimos 7 días.

```bash
find /tmp -type f -mtime -7
```

### Buscar archivos con permisos determinados

Este comando busca archivos en el directorio `/home/user` que tienen permisos `644`.

```bash
find /home/user -type f -perm 644
```

### Ejecutar un comando sobre archivos encontrados

Este comando busca archivos con extensión `.log` en el directorio `/var/log` y los comprime usando `gzip`.

```bash
find /var/log -type f -name "*.log" -exec gzip {} \;
```

### Buscar archivos y eliminarlos

Este comando busca y elimina archivos con extensión `.tmp` en el directorio `/tmp`.

```bash
find /tmp -type f -name "*.tmp" -delete
```

## kill

Es un comando utilizado para enviar señales a procesos. Aunque se le conoce principalmente por su uso para terminar procesos, kill es en realidad una herramienta más versátil que puede enviar diferentes tipos de señales a procesos para controlar su comportamiento.

### Señales Básicas

- *SIGTERM (15)*: Es la señal predeterminada y la forma más segura de terminar un proceso. Le indica al proceso que se cierre de manera limpia, liberando recursos y guardando los datos necesarios antes de salir.

- *SIGKILL (9)*: Esta señal fuerza al proceso a terminar inmediatamente. No permite que el proceso realice ninguna limpieza o guardado, por lo que debe usarse como último recurso.

- *SIGSTOP (17, 19, 23)*: Detiene temporalmente un proceso, sin terminarlo. El proceso puede reanudarse más tarde.

### Terminar un proceso con SIGTERM

Sustituye [PID] con el ID del proceso que deseas terminar. Este es el método preferido para cerrar procesos, ya que les da la oportunidad de cerrar archivos y liberar recursos de manera adecuada.

```bash
kill [PID]
```

### Forzar la terminación de un proceso con SIGKILL

Usa esta opción solo si el proceso no responde a un SIGTERM.

```bash
kill -9 [PID]
```

### Detener un Proceso con SIGSTOP

Es útil para detener un proceso sin terminarlo, permitiendo su análisis o depuración.

```bash
kill -STOP [PID]
```

### Listar Todas las Señales Disponibles

Este comando te mostrará todas las señales que puedes enviar con kill.

```bash
kill -l
```

### Uso de pkill y killall

Para evitar tener que buscar el PID, puedes usar `pkill` o `killall` seguido del nombre del proceso. Por ejemplo, `pkill firefox` enviará la señal predeterminada a todos los procesos llamados `firefox`.

### Combinando ps y grep con kill

Si no conoces el PID, puedes encontrarlo combinando `ps` y `grep`. Luego, usa el PID encontrado con el comando `kill`.

```bash
ps aux | grep [nombre_proceso]
```

## cat

El comando `cat` significa del inglés catenate, que significa concatenar, ya que la función principal de este comando es unir varios archivos de entrada enviando secuencialmente su contenido a la salida estándar.

Crear dos archivos llamados `file_domain` y `file_path` con el siguiente contenido cada uno. Estos dos archivos los utilizaremos para los ejemplos que veremos a continuación.

```bash
# file_domain
voidnull.es

# file_path
/diccionario-comandos-gnu-linux/
```

Como hemos mencionado `cat` sirve para concatenar archivos, por lo que podemos hacerlo de la siguiente forma:

```bash
cat file_domain file_path > file_result
```

Si mostramos el fichero `file_result`:

```bash
cat file_result 

voidnull.es
/diccionario-comandos-gnu-linux
```

### Concatenar dos archivos con separador

utilizamos `cat` sin ningún argumento, el comando `cat` mostrará los datos de la entrada estándar y los mostrará en su salida estándar, algo que puede ser útil pero que en realidad es un poco inútil... a menos que se utilice alguna opción para transformar los datos. Además de pasar rutas de archivos por el comando `cat`, también entiende el guión como un alias para la entrada estándar. De esta forma, podemos insertar datos leídos de la entrada estándar entre dos archivos.

Por ejemplo, vamos a añadir `####` entre los dos archivos con los que estamos trabajando:

```bash
echo '####' | cat file_domain - file_path 

voidnull.es
####
/diccionario-comandos-gnu-linux
```

### Concatenar imágenes

Puede parecer increíble, pero sí, podemos concatenar archivos binarios con el comando `cat`. Como por ejemplo imágenes, tenemos una imagen de un lindo gatito, y hemos descargado el fichero en dos mitades:

```bash
curl -s -r 0-50000 https://upload.wikimedia.org/wikipedia/commons/thumb/b/b6/Felis_catus-cat_on_snow.jpg/1024px-Felis_catus-cat_on_snow.jpg -o image_first_half &
curl -s -r 50001- https://upload.wikimedia.org/wikipedia/commons/thumb/b/b6/Felis_catus-cat_on_snow.jpg/1024px-Felis_catus-cat_on_snow.jpg -o image_second_half &
```

Con el comando anterior, lo que hacemos es descargarnos parte de la imagen, para eso usamos la opción `-r` para indicar el rango de bytes a descargar. Para concatenar los dos trozos de la imagen, deberemos de ejecutar el siguiente comando:

```bash
cat image_first_half image_second_half > gatito.jpg
```

### Mostrar archivos de texto con información

El comando `cat` permite mostrar diferentes informaciones que pueden ser útiles. Por ejemplo el número de línea con la opción `-n`:

```bash
cat -n file_result 
     1  voidnull.es
     2  /diccionario-comandos-gnu-linux
```

Con la opción `-s` podemos suprimir líneas vacías que se repitan, por ejemplo tenemos este contenido en el fichero `file_clean`:

```bash
voidnull.es


/diccionario-comandos-gnu-linux
```

Podemos eliminar un salto de línea:

```bash
cat -s file_clean 
voidnull.es

/diccionario-comandos-gnu-linux
```

Pero si utilizamos la opción `-n` con el fichero `file_clean`, nos indicará que hay 4 líneas y dos de ellas estarán vacías. Si queremos que cuenta únicamente las líneas donde hay contenido, podemos usar la opción `-b`.

```bash
cat -b file_clean 
     1  voidnull.es


     2  /diccionario-comandos-gnu-linux
```

También podemos mostrar otro tipo de caracteres, como por ejemplos tabulaciones dentro del fichero, con la opción `-t` y también podemos marcar las líneas vacías o final de línea con la opción `-e`. Por lo tanto, si mostramos el fichero con estas dos opciones:

```bash
cat -te file_clean
voidnull.es$
^I$
$
/diccionario-comandos-gnu-linux$
```

Donde aparece `$` indica que hay un final de línea. Si aparece además también `^I` indica que hay una tabulación.

## Recursos

- [Wizard Zines](https://wizardzines.com/)
- [Comandos Linux](https://voidnull.es/tag/cmd/)