# Laboratorio 2: Concurrencia

## Ejercicio 1
Se dispone del código del siguiente programa (`p1.c`), así como un archivo `Makefile` que permite compilar dicho programa (así como el resto de los programas descritos en el resto de los ejercicios).   Para compilar este programa ejecute:
```bash
make p1
```
Este programa crea dos procesos ligeros, cada uno de los cuales ejecuta una serie de iteraciones en las que el thread se bloquea un tiempo aleatorio entre 0 y 100 ms e imprime su identificador y el número de la iteración.  
Compile y ejecute el código anterior varias veces. Identifique los problemas de ejecución que observa.

## Ejercicio 2
Modifique el programa anterior de forma que cada uno de los threads imprima su identificador (0 o 1) de forma que los dos threads ejecuten el código de forma alternada, primero el thread 0, luego el 1, luego el 0 y así sucesivamente. El nombre de este programa será `p2.c`.  
Utilice para ello un mutex y variables condicionales.

Para compilarlo utilice:
```bash
make p2
```

## Ejercicio 3
Modifique el programa anterior de forma que se creen 10 threads que ejecuten todos el código de la función `funcion`.  
Todos los threads tienen que alternar la ejecución del bucle de la función: primero el 0, luego el 1..., luego el 9, luego el 0, luego el 1, y así sucesivamente.  
El nombre de este programa será `p3.c`.


## Ejercicio 4
En el material de apoyo se proporciona el código de un programa (`pi.c`) que calcula el número pi mediante el cálculo de la siguiente integral definida con el método de los trapecios:  
$\int_{0}^{1}{\sqrt{4 \cdot (1 - x^2)}}\ dx = \frac{\pi}{2}$

El programa `pi2.c` es una versión similar que está pensada como un primer paso para paralelizar el código y que pueda ser ejecutada por varios threads. Modifique el código `pi2.c` para que el cálculo sea hecho por una serie de threads en paralelo. El programa permite obtener el tiempo de ejecución. 

Compruebe cómo es el tiempo de ejecución de la versión secuencial respecto a la versión paralela.  
Para poder compilar estos programas deberá modificar previamente el archivo `Makefile` para incluir las reglas necesarias para su compilación.

## Ejercicio 5
Se proporciona el código de un programa productor-consumidor (`p5.c`). 

El programa copia un archivo pasado como parámetro en otro. El proceso productor lee del fichero e inserta los caracteres en un buffer, y el consumidor extrae los caracteres del buffer y los escribe en el fichero de salida. Compile, ejecute y analice el funcionamiento del programa.  

Modifique, a continuación, el programa anterior para que la ejecución de los dos procesos sea correcta. Tenga en cuenta que cuando el proceso productor finaliza la lectura del fichero debe notificar al consumidor dicho evento.

## Ejercicio 6
Se proporciona el código (`p6.c`) de un programa que intenta resolver el problema de los lectores-escritores (dando prioridad a los lectores).

Ejecute el programa e identifique el problema existente.  
Modifique, a continuación, el programa anterior para que la ejecución de los procesos sea la correcta.

## Ejercicio 7
Resuelva todos los problemas anteriores en Python.