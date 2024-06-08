# Comandos

## awk

awk es um pequeño lemnguaje de programación para manipular columnas de datos.

## find

find busca los archivos especificados en todos los directorios de la computadora.

```bash
find /tmp -type d -print
```

- `type [TYPE]` `f`: archivo regular, `l`: enlace simbolico, `d`: directorio
- `size 0` busca archivos vacíos
- `exec COMMAND` ejecuta *COMMAND* en cada archivo encontrado
- `print0` imprime los nombres de archivos sin separación
- `delete` borra los archivos encontrados
