#!/bin/bash

# El comando date en bash es muy flexible.
# A continuación, algunos formatos útiles de timestamp:

echo "Fecha en formato año-mes-día (YYYY-MM-DD)"
date +"%Y-%m-%d"
echo ""
echo "Fecha y hora en formato año-mes-día_hora-minuto-segundo (YYYYMMDD_HHMMSS)"
date +"%Y%m%d_%H%M%S"
echo ""
echo "Solo la hora en formato de 24 horas (HH:MM)"
date +"%H:%M:%S"
echo ""
echo "Fecha y hora con nombre del mes"
date +"%d-%b-%Y %H:%M:%S"
echo ""
echo "Timestamp de UNIX (número de segundos desde el 1 de enero de 1970)"
date +"%s"
