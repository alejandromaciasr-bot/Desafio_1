en este avance me centre en implementar las funcionalidades que permiten ya no solo modificar el contenido de tablero, sino también sus dimensiones y la cantidad de memoria que reservamos


Hasta el avance anterior, el programa podía detectar combinaciones, eliminar fichas, aplicar gravedad, rellenar espacios vacíos y resolver cascadas, pero las dimensiones del tablero permanecían constantes. En este avance se agregaron operaciones para eliminar fichas individuales y para agregar o eliminar filas y columnas en cualquier posición del tablero

a continuación las funciones incluidas y una breve descripción:

- eliminarFichaUsuario() recibe una fila y una columna, verifica que la posición exista y marca la ficha seleccionada como vacía utilizando el valor 6
- agregarFila() y agregarColumna(), estas dos permiten agregar una fila o columna en cualquier posición, no solo en los extremos y la nueva fila o columna se llena con fichas aleatorias 0-5 es importante entender que para estas lo que se debe hacer es un tablero nuevo, debido a que el tablero no es una matriz convencional sino una secuencia compacta de bits, no podemos simplemente insertar una posición en medio de la memoria, por eso construimos temporalmente un nuevo tablero y reorganizamos las fichas
- eliminarFila() y eliminarColumna(), estas permiten eliminar una fila o columna en cualquier posición. Aquí pasa algo parecido y es que las filas y columnas que no queremos eliminar las llevamos a un nuevo tablero que no contenga las que queremos eliminar, por la misma razón de que el tablero no es una matriz normal

cabe recalcar que con esto debemos tener mucho cuidado siendo responsables con la liberación de la memoria

finalmente se implemento la regla de 65%, esto si no requirió una función, simplemente operaciones matemáticas y condicionales