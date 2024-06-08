# Comandos

## awk

awk es um pequeño lemnguaje de programación para manipular columnas de datos.

## find

find busca los archivos especificados en todos los directorios de la computadora.

```bash
find /tmp -type d -print
```

- `path` busca el path completo, por ejemplo `-path '/home/*/*.pdf'`
- `ipath` igual que *path* pero es *case insensitive*
- `maxdepth NUM` solo niveles *NUM* descendentes cuando busca directorios
- `name` busca el nombre de archivo, por ejemplo `-name '*.txt'`
- `iname` igual que *name* pero es *case insensitive*
- `type [TYPE]` *f*: archivo regular, *l*: enlace simbolico, *d*: directorio
- `size 0` busca archivos vacíos
- `print` imprime en pantalla
- `print0` imprime en pantalla los nombres de archivos sin separación
- `exec COMMAND` ejecuta *COMMAND* en cada archivo encontrado
- `delete` borra los archivos encontrados

## kill

### kill doesn't just kill programs

You can send **ANY** signal to a program with `kill`!

```
$ kill -SIGNAL PID
```
*name or number*

---

### which signal kill sends

```
kill       => SIGTERM 15
kill -9    => SIGKILL 9
kill -KILL => SIGKILL 9
kill -HUP  => SIGHUP 1
kill -STOP => SIGSTOP 19
```

---

### kill -l

Lists all signals
```
 1 HUP   2 INT   3 QUIT   4 ILL
 5 TRAP  6 ABRT  7 BUS    8 FPE
 9 KILL 10 USR1 11 SEGV  12 USR2
13 PIPE 14 ALRM 15 TERM  16 STKFLT
17 CHLD 18 CONT 19 STOP  20 TSTP
21 TTIN 22 TTOU 23 URG   24 XCPU
25 XFSZ 26 VTALRM 27 PROF 28 WINCH
29 POLL 30 PWR  31 SYS
```

---

### killall -SIGNAL NAME

Signals all processes called NAME. For example:
```
$ killall firefox
```

Useful flags:
-w Wait for all signaled processes to die
-i Ask before signalling

---

### pgrep

Prints PIDs of matching running programs.

```
pgrep fire    matches    firefox
                         firebird
```
*NOT* `bash firefox.sh`

To search the whole command line (e.g. `bash firefox.sh`), use `pgrep -f`

---

### pkill

Same as `pgrep`, but signals PIDs found. Example:
```
$ pkill -f firefox
```

*I use pkill more than killall these days*

Claro, aquí tienes el texto de la imagen traducido al español:

---
# grep

**grep** te permite buscar archivos por texto.

```
$ grep bananas foo.txt
```

¡Aquí hay algunos de mis argumentos de línea de comando grep favoritos!

---

### E

Usa si quieres regexps como ".+" para trabajar. De lo contrario, necesitas usar ".*".

---

### -r

Recursivo! Busca en todos los archivos de un directorio.

---

### -v

Invierte la coincidencia: encuentra todas las líneas que **no** coinciden.

---

### -o

Solo imprime la parte coincidente de la línea (no toda la línea).

---

### -i

Insensible a mayúsculas y minúsculas.

---

### -l

Solo muestra los nombres de los archivos que coincidieron.

---

### -a

Busca binarios: lee datos binarios como texto en lugar de ignorarlos.

---

### -A NUM

Muestra contexto para tu búsqueda.

```
$ grep -A 3 foo
```

mostrará 3 líneas de contexto **después** de una coincidencia.

---

### -F

No trata la cadena de coincidencia como una expresión regular.

```
ej. $ grep -F ...
```

---

### grep alternatives

```
ack  ag  ripgrep (mejor para buscar código!)
```

---

Fuente: wizardzines.com