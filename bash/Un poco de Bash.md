# Un poco de Bash

> Sobre el trabajo de Nicolás Wolovick, *Lab2: Un Baash* [1].

1. Introducción
2. Operación Básica
3. Procesos en Segundo Plano
4. Redirección de la Entrada/Salida
5. Tuberías
6. Tareas
7. Fuentes

## Introducción

**GNU Bash** [2] o simplemente **Bash (Bourne-again shell)** es una interfaz de usuario de línea de comandos popular, específicamente un shell de Unix; así como un lenguaje de scripting. Bash fue originalmente escrito por Brian Fox para el sistema operativo GNU, y pretendía ser el reemplazo de software libre del shell Bourne. Lanzado por primera vez en 1989, se ha utilizado ampliamente como el intérprete de inicio de sesión (login) predeterminado para la mayoría de las distribuciones de GNU/Linux, y también de Mac OS X de Apple hasta la versión 10.15. Una versión también está disponible para Windows 10 y Android. También es el intérprete de órdenes de usuario predeterminado en Solaris 11.

La interfaz más tradicional de un sistema operativo **UNIX-like** (*NIX) es el intérprete de línea de comandos. Este programa, que ejecuta en modo usuario, funciona en cualquier *NIX que soporte interface de caracteres y su función es aceptar comandos ingresados por entrada estandar (teclado), parsearlos, ejecutar la órden y mostrar el resultado en salida estandar (pantalla), para luego volver a repetir el proceso.

Los usos más comunes de Bash son [3]:

**Interacción directa con el sistema operativo.** Los usuarios pueden ejecutar comandos, manipular archivos y directorios, gestionar procesos y realizar tareas administrativas directamente desde la línea de comandos.

- Navegar por el sistema de archivos (`cd`, `ls`, `pwd`).
- Manipular archivos (`cp`, `mv`, `rm`, `touch`).
- Administrar procesos (`ps`, `kill`, `top`).

**Automatizar tareas repetitivas.** Mediante scripts que se pueden programar para ejecutarse automáticamente en momentos específicos utilizando herramientas como `cron` y `at`, es posible realizar copias de seguridad, limpieza periódica de archivos temporales, actualizar el sistema.

**Administración de sistemas.** En algunos entornos, Bash permite el despliegue de aplicaciones en varios servidores, monitorización de uso de disco y memoria, y gestión de cuentas de usuarios.

**Desarrollo de software.** También es utilizado por desarrolladores de software para crear scripts de construcción y despliegue, automatizar pruebas y gestionar entornos de desarrollo. Es una herramienta esencial en el desarrollo ágil y la integración continua.

**Procesamiento de datos.** Además, es una herramienta eficaz para el procesamiento y análisis de datos, especialmente cuando se combina con otras utilidades como `grep`, `awk`, `sed` y `sort`. Los scripts de Bash pueden manipular grandes volúmenes de datos de manera eficiente para: la extracción y transformación de datos, el análisis de logs y generación de reportes, y la automatización de flujos de trabajo de datos.

Por defecto UNIX ejecuta un proceso shell cada vez que un usuario interactivo ingresa al sistema. Aunque esto puede ser configurado de otra manera (ver el último campo de cada línea del archivo `/etc/passwd`), en la mayoría de los casos luego de ingresar nuestro nombre de usuario y contraseña, el proceso que maneja el ingreso de usuarios genera un proceso hijo que ejecuta un shell, con el *uid/gid* (identificador de usuario y grupo) correspondiente al usuario. En este momento la pantalla se suele presentar de la siguiente manera:

```bash
usuario@host:~$ 
```

Después de este texto inicial llamado *prompt*, que contiene información de entorno como por ejemplo el nombre del usuario, el nombre del host y el último tramo del directorio corriente, el shell espera datos a través de la `stdin` que normalmente se asocia al dispositivo teclado. Podemos escribir el comando que deseamos que el shell ejecute, e iniciar la ejecución ingresando el caracter NEWLINE `'\n'` generalmente asociado con la tecla Enter o Return.

```bash
usuario@host:~$ sleep 10 
```

Hará que el shell ejecute un proceso con el programa binario que se encuentra en `/bin/sleep`, pasándole el argumento `10`.

## Operación Básica

La sintáxis básica del intérprete de comandos más usual de *NIX, conocido como Bourne shell (Bourne again shell - bash, en Linux) es la siguiente,

> comando argumento1 argumento2 ...

donde el comando y los argumentos son secuencias de caracteres separados por uno o más espacios.

La semántica dice que al presionar Enter el shell buscará el *comando* dentro de los comandos internos y si no lo encuentra tratará de buscar un archivo ejecutable con ese nombre, siguiendo las reglas de camino de *NIX o componiendo el comando a la secuencia de la *variable de entorno* `PATH`, para luego crear un *proceso hijo* que cargará y ejecutará el contenido de ese archivo con los argumentos correspondientes.

Los *comandos internos* son manejados directamente por el shell, sin requerir de ningún archivo externo. Un ejemplo es el comando de cambio de directorio `cd`, el cual no se encuentra como archivo ejecutable en ningún lugar del árbol de directorio (el comando `find /bin /sbi /usr/bin /usr/sbin -perm +400 -type f -name cd` no devuelve nada).
Con `man builtin` obtenemos una lista de todos los comandos internos implementados en *bash*.

Si un comando no es un *builtin*, el shell deberá buscar un archivo dentro de su sistema de archivos, cargarlo y ejecutarlo pasándole los argumentos. El problema principal es dónde buscar este archivo. Existen tres formas:

- Camino absoluto
- Camino relativo
- Búsqueda en secuencia `PATH`

Cuando el comando comienza con `/`, este se toma como un camino absoluto dentro del árbol del sistema de archivos, el shell cargará en memoria y ejecutará el comando. En cambio si el comando comienza con el nombre de un directorio, `.` o `..`, se debe seguir las reglas usuales de camino relativo de *NIX, cargar y ejecutar el archivo comando, relativo al camino actual (ver comando `pwd`).

Otro mecanismo entra en juego cuando el comando no comienza con un delimitador de camino absoluto o relativo. La variable de entorno `PATH`, que puede ser leida con el comando `env` o con `echo $PATH`, sirve de secuencia de caminos absolutos o relativos, separados por *':'* que serán prefijados a commando hasta encontrar un archivo que pueda ser leído y ejecutado.

Usemos el archivo ejecutable `/bin/date` [4] que nos proporciona la fecha y hora del sistema para ejemplificar los mecanismos de camino absoluto, relativo y secuencia `PATH`.

```bash
usuario@host:~$ /bin/date
mar 04 jun 2024 11:06:20 -03
usuario@host:~$ cd /usr
usuario@host:/usr$ ../bin/date
mar 04 jun 2024 11:07:08 -03
usuario@host:/usr$ cd /
usuario@host:/$ bin/date
mar 04 jun 2024 11:07:43 -03
usuario@host:/$ cd ~
usuario@host:~$ date
mar 04 jun 2024 11:08:23 -03
```

Todos los comandos ejecutados por bash son el mismo `/bin/date`.

### Ejercicios

1. ¿Cómo ejecutamos un archivo que se llama exactamente como un *builtin*?
2. ¿Por qué las recomendaciones de seguridad indican que es peligroso tener `./` en `PATH` al más puro estilo *MS-DOS*?
3. Supongamos que existen 2 comandos posibles dentro de la secuencia que contiene `PATH`, donde el primero en la secuencia no está marcado como ejecutable y el segundo si. ¿Qué hace el intérprete `bash`, ejecuta el segundo o informa que el primero no tiene permiso de ejecución?
4. Indique qué sucede cuando se tiene un directorio en el `pwd` actual con el mismo nombre que un archivo ejecutable en el `PATH`. ¿Dice que no puede ejecutar un directorio o ejecuta el comando que encontró?
5. Obtenga la lógica más sencilla que unifique los tres tipos de búsqueda.
6. ¿Podemos poner directorios relativos en `PATH`?

## Procesos en Segundo Plano

En el paradigma básico para ejecutar un comando, el shell es el proceso padre que crea a un hijo que cargará y ejecutará el comando que se encuentra en el sistema de archivos. Mientras tanto el padre quedará esperando hasta que el proceso hijo termine.
La semántica puede ser cambiada para que el padre **no espere la terminación del hijo**, si le agregamos al final el símbolo `&`.
Este operador, que puede ser pensado como operador de *composición paralela*, crea la posibilidad de ejecutar procesos de manera concurrente, es decir, si el comando que ejecutamos termina con `&` y demora un tiempo relativamente largo, todo lo que iniciemos desde el shell y el shell mismo estarán ejecutándose al mismo tiempo (paralelamente, concurrentemente).

Esta característica resulta muy útil cuando el kernel esta corriendo sobre un motherboard SMP (symmetric multiprocessing) [5], que soporta varios microprocesadores compartiendo una única imagen de memoria principal. Si tenemos un par de programas que tardan mucho en calcular decimales de *pi* o de *e*, podemos ponerlos a correr de manera que cada uno ocupe un microprocesador, mientras utilizamos un poco de los dos micros para jugar.

```bash
usuario@host:~/calculosLargos$ ./decimalesPi salidaPi.txt &
usuario@host:~/calculosLargos$ ./decimalesE salidaE.txt &
usuario@host:~/calculosLargos$ freeciv 
```

Existe un problema con los procesos hijos en *background*, la entrada y salida estandar se comparten entre todos, con lo cual tendremos salidas de pantalla entrelazadas y las entradas por teclado serán no-deterministicamente asignadas a alguno de los procesos que están corriendo. Este ejemplo nos muestra el lio que se puede armar.

```bash
usuario@host:~$ yes "HOLA" & yes "CHAU" &
... ud. acaba de perder el control de esa shell ...
```

### Ejercicios

1. Investigue cuales son los comandos internos para manejo de procesos en *background* de `bash`.
2. En el ejemplo de arriba el operador `&` funciona como **operador de composición paralela**. ¿Cuál es el operador de composición **secuencial** en Bourne shell?
3. Investigue como `bash` forma el árbol de procesos cuando ejecutamos `cmd1 & cmd2 & cmd3 & ... & cmdN`. Piense la respuesta y luego utilice `pstree` para corroborarla.
4. Indique cuantas letras `a` debería imprimir el siguiente programa.

```c
fork();
fork();
fork();
printf("a"); 
```

## Redirección de la Entrada/Salida

Cuando se crea un proceso, se le asignan tres identificadores de archivos (*file descriptors*): `stdin`, `stdout` y `stderr`. Si se lee desde `stdin`, los datos que se reciben serán dirigidos desde el teclado al *file descriptor* `stdin`. Similarmente, los datos escritos en `stdout`, `stderr` serán mapeados a la pantalla de la terminal.

El usuario puede redefinir el `stdin` desde la línea de comandos del shell si se provee al final del comando un embudo de entrada `<` y un nombre de archivo. Este archivo reemplazará la corriente estandar de entrada, por lo que los valores que lea el comando serán extraidos desde el archivo.
Similarmente podemos redefinir el *file descriptor* de `stdout` con el embudo de salida `>` y un nombre de archivo al final del comando y los argumentos, para indicar que toda la salida estandar del comando se acumule en el archivo.

Como ejemplo podemos recolectar estadísticas sobre un *header* del código fuente del kernel y ponerlo en un archivo de estadísticas.

```bash
usuario@host:~$ wc < kernel.h > kernel.h.stats
```

O si nuestros programas *cpu-bound* [6] generan sus resultados en pantalla podemos ejecutarlos concurrentemente y mantener sus salidas separadas, mientras las monitoreamos con el comando `tail`.

```bash
usuario@host:~$ forest3d -n 0.2 > n0.2.out &
usuario@host:~$ forest3d -n 0.3 > n0.3.out &
usuario@host:~$ tail -f n0.2.out n0.3.out
```

### Ejercicios

1. Las corrientes estandar `stdout` y `stderr` están dirigidas ambas a la consola. ¿Cómo podemos utilizar los operadores de redirección para separarlas?
2. De más ejemplos de como usar la redireccion de entrada? Tenga cuidado que muchos programas deshabilitan la posibilidad de redirigir la entrada estandar a otra cosa que no sea una terminal.
3. ¿Podemos redirigir de manera independiente la entrada y la salida de una secuencia de comandos separados por `&`? ¿Qué sucede con la composición sequencial `;`?

## Tuberías

Las tuberías o *pipes* son el principal mecanismo de **Comunicación entre Procesos (IPC)** para *NIX. Una tubería se compone de dos puntas, una entrada y una salida, cada una conectada a un proceso. Las puntas de una tubería son un par de *file descriptors*, uno para escribir y el otro para leer. Un *pipe* es básicamente un buffer *FIFO*, donde tenemos un **productor**, sobre el *write-end* y un **consumidor** sobre el *read-end*. Como sabemos que todas las colas que se encuentran en el sistema operativo son acotadas (memoria finita), además de tener un *read* bloqueante cuando no hay datos para consumir, tenemos un *send* bloqueante cuando la capacidad del buffer está excedida.

El shell provee la funcionalidad de un pipe a través del operador `|`, denominado justamente **pipe**, el cual conecta la salida estandar del proceso lanzado por el comando de la izquierda del pipe, con la entrada estandar del proceso que se genera con el comando a la derecha del símbolo de tubería.

Las tuberías se pueden componer secuencialmente para generar una linea de *producción de datos*, el cual es un estilo arquitectural denominado *pipes&filters*.

Estos ejemplos cuentan cuantas veces Juan ingresó al sistema, los pids (process identifiers) de todos los mozillas, y el listado ordenado de mayor a menor de todos los usuarios del sistema que tienen `bash`,

```bash
juan@host:~$ last juan | wc -l
juan@host:~$ ps aux | grep mozilla-bin
juan@host:~$ grep bash /etc/passwd | cut -d ":" -f 1 | sort -r

```

mientras que el siguiente es un poco más complicado y permite reestablecer interactivamente un *dump* de una partición *ext2* [7], que ha sido partido para sortear la limitación de 2GB de tamaño del sistema de archivos *ext2*.

```bash
juan@host:~$ cat backupL0.gza? | gzip -dc | /sbin/restore -i -f -

```

### Ejercicios

1. ¿Cúal es el mecanismo para que este estilo *pipes&filters*, hasta ahora absolutamente lineal, permita bifurcaciones? Si tuvieramos bifurcaciones, podríamos capturar la salida estandar en un archivo y al mismo tiempo visualizarla en consola.
2. Los pipes existen en el sistema de archivos mientras dura el comando. ¿Dónde se encuentran y que atributos tiene?
3. ¿Cómo es el pipe de comandos para generar el *dump* de nivel 0 que se reestablece interactivamente con el ejemplo anterior?
4. Muestre el *uid* máximo en su sistema NIS (`ypcat passwd` realiza el trabajo básico).
5. Muestre todos los login repetidos de su sistema NIS.

## Fuentes

[1] Lab2: Un Baash [https://cs.famaf.unc.edu.ar/~nicolasw/Docencia/so2003/lab2.html](https://cs.famaf.unc.edu.ar/~nicolasw/Docencia/so2003/lab2.html)
[2] Bash, Wikipedia [https://es.wikipedia.org/wiki/Bash](https://es.wikipedia.org/wiki/Bash)
[3] Introducción al Bash Scripting #1 [https://voidnull.es/introduccion-al-bash-scripting/](https://voidnull.es/introduccion-al-bash-scripting/)
[4] date(1) — Linux manual page [https://man7.org/linux/man-pages/man1/date.1.html](https://man7.org/linux/man-pages/man1/date.1.html)
[5] Multiprocesamiento simétrico, Wikipedia [https://es.wikipedia.org/wiki/Multiprocesamiento_sim%C3%A9trico](https://es.wikipedia.org/wiki/Multiprocesamiento_sim%C3%A9trico)
[6] CPU-bound, Wikipedia [https://en.wikipedia.org/wiki/CPU-bound](https://en.wikipedia.org/wiki/CPU-bound)
[7] Linux 6.9 Deprecates The EXT2 File-System Driver [https://www.phoronix.com/news/Linux-6.9-Deprecates-EXT2](https://www.phoronix.com/news/Linux-6.9-Deprecates-EXT2)