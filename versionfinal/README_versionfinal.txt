A diferencia del Avance_5, que se centró en las operaciones de modificación dinámica del tablero y la gestión de memoria, esta versión incorpora el menú de interacción, la configuración inicial, el sistema de puntuación, los contadores de estado, la representación binaria y la condición de finalización de la partida.

De esta manera, el programa pasó de ejecutar pruebas controladas de sus funciones a permitir que el usuario desarrolle una partida completa.

Funcionalidades implementadas:

-Creación dinámica del tablero a partir de las dimensiones ingresadas por el usuario.
-Almacenamiento compacto utilizando 3 bits por ficha.
-Generación aleatoria de fichas.
-Visualización del tablero mediante letras y representación binaria.
-Detección de combinaciones horizontales y verticales de tres o más fichas iguales.
-Eliminación de combinaciones.
-Aplicación de gravedad sobre las fichas restantes.
-Relleno automático de posiciones vacías.
-Resolución de cascadas sucesivas.
-Eliminación individual de fichas.
-Adición y eliminación de filas en cualquier posición.
-Adición y eliminación de columnas en cualquier posición.
-Redimensionamiento dinámico de memoria.
-Aplicación de la regla del 65 % para la reducción de memoria.
-Sistema de puntuación y control de turnos.

Representación de las fichas:

Binario:	Representación:
000	        A
001	        B
010	        C
011	        D
100	        E
101	        F
110	       Posición vacía
111	       Valor reservado o inválido

Funcionamiento del juego:

Al iniciar, el usuario ingresa las dimensiones del tablero, con un mínimo de 3 filas y 3 columnas.

El programa genera las fichas aleatoriamente y resuelve las combinaciones iniciales antes de comenzar la partida.

Durante cada turno, el usuario puede seleccionar una de las siguientes operaciones:

1.Eliminar una ficha.
2.Agregar una fila.
3.Eliminar una fila.
4.Agregar una columna.
5.Eliminar una columna.

Las filas y columnas pueden agregarse o eliminarse en cualquier posición válida, incluyendo posiciones intermedias.

Después de cada operación se procesan las posibles combinaciones y cascadas generadas.

Sistema de puntuación: 

Se estableció el siguiente criterio:

-Cada ficha eliminada: 10 puntos.
-Cada cascada realizada: 20 puntos adicionales.

El objetivo del juego es alcanzar o superar los 300 puntos.

La partida finaliza cuando la puntuación acumulada alcanza dicho valor.

Organización del código: 

El programa se desarrolló modularmente mediante cinco archivos:

main.cpp: contiene la ejecución principal del juego, la interacción con el usuario y el control de la partida.

tablero.h: contiene las declaraciones de las funciones relacionadas con el almacenamiento y la modificación del tablero.

tablero.cpp: implementa la gestión de memoria, las operaciones bitwise, la visualización y la modificación dinámica de filas y columnas.

juego.h: contiene las declaraciones de las funciones relacionadas con las reglas del juego.

juego.cpp: implementa la eliminación de fichas y combinaciones, gravedad, relleno, cascadas y demás operaciones propias del juego.

Consideraciones finales: 

El desarrollo se realizó utilizando solamente memoria dinámica, sin emplear matrices convencionales para almacenar las fichas del tablero, STL, struct, etc.

Las operaciones de lectura y escritura se implementaron mediante operadores bitwise, permitiendo manipular correctamente fichas incluso cuando sus 3 bits se encuentran distribuidos entre dos bytes.

Las diferentes funcionalidades fueron desarrolladas progresivamente y documentadas en los avances anteriores del repositorio.

