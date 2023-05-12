# Laboratorio 5: Servicios web
El objetivo de este laboratorio es familiarizar al alumno/a con el consumo de servicios web en Python.  

El objetivo es desarrollar un programa en Python que permita utilizar el servicio de conversión de temperaturas que se encuentra disponible en: [w3schools.com/xml/tempconvert.asmx](https://www.w3schools.com/xml/tempconvert.asmx).  

Puedes encontrar un ejemplo de creación de servicio web (y cliente) en [`ws-calc/`](ws-calc).


## Instalación y ejecución

First install [`zeep`](https://pypi.org/project/zeep/):
```bash
pip3 install zeep
```

Execute as regular:
```bash
python3 ws-tempconvert-client.py
```