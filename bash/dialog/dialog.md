# dialog

**dialog** permite mostrar interfaces gráficas de texto en la terminal (menús, input, cajas de mensaje, etc.)

## Instalación

```bash
sudo apt install dialog
```

## Estructura básica

```bash
dialog [OPCIONES GENERALES] --TIPO_DE_CAJA "TÍTULO" ALTO ANCHO [DATOS]
```

- ALTO: alto de la ventana en líneas
- ANCHO: ancho de la ventana en columnas

## Tipos de cajas

### `--msgbox` — Mensaje

```bash
dialog --msgbox "Hola mundo" 10 30
```

### `--yesno` — Sí/No

```bash
dialog --yesno "¿Estás seguro?" 10 30
```

### `--inputbox` — Entrada de texto

```bash
dialog --inputbox "Ingresá tu nombre:" 10 40 2> salida.txt
nombre=$(<salida.txt)
```

dialog escribe la selección del usuario en `stderr` (no en `stdout`), por eso hay que redirigir con `2>` (redirección estándar de `stderr` a un archivo).

### `--menu` — Menú de opciones

```bash
dialog --menu "Elegí una opción:" 15 50 4 \
1 "Iniciar sistema" \
2 "Configurar red" \
3 "Salir" 2> salida.txt
```

- 4: cantidad máxima de ítems visibles en la lista.

### `--checklist` — Selección múltiple

```bash
dialog --checklist "Elegí opciones:" 15 50 4 \
1 "Opción A" off \
2 "Opción B" on \
3 "Opción C" off 2> salida.txt
```

Cada ítem de la lista se define como:

- TAG (un identificador, en este caso 1, 2, 3)
- Texto visible ("Opción A")
- Estado inicial: on (seleccionada) u off (no seleccionada).

### `--radiolist` — Selección única

```bash
dialog --radiolist "Elegí una opción:" 15 50 4 \
1 "Opción 1" off \
2 "Opción 2" on \
3 "Opción 3" off 2> salida.txt
```

### `--passwordbox` — Entrada oculta

```bash
dialog --passwordbox "Ingresá tu clave:" 10 40 2> clave.txt
```

### `--progressbox` — Progreso

```bash
some_command | dialog --title "Progreso" --progressbox 20 70
```

### `--gauge` — Barra de progreso real

```bash
(
  echo 10; sleep 1
  echo 30; sleep 1
  echo 60; sleep 1
  echo 100
) | dialog --gauge "Cargando..." 10 50
```

Ejecuta el subshell () y lo envia a dialog mediante un pipe.

## Opciones útiles

| Opción                   | Descripción                        |
| ------------------------ | ---------------------------------- |
| `--title "Título"`       | Título de la ventana               |
| `--backtitle "Fondo"`    | Texto en el fondo superior         |
| `--clear`                | Limpia la pantalla al terminar     |
| `--stdout` o `2>`        | Dirección de salida de datos       |
| `--nocancel`             | Elimina el botón "Cancelar"        |
| `--ok-label "Texto"`     | Cambia el texto del botón OK       |
| `--cancel-label "Texto"` | Cambia el texto del botón Cancelar |
