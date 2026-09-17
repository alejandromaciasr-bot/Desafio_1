en este avance ya empecé a implementar la lógica proia del juego

la función principal nueva para este avance es eliminarCombinaciones() esta revisa primero las filas buscando combinaciones verticales y luego las columnas buscando combinaciones horizontales

con 3 bits podemos representar 0-7, en nuestro programa 0-5 vienen siendo las fichas normales A-F, pero 6 lo vamos a usar como espacio vacío y se va a imprimir en pantalla como "." para esto tuvimos que modificar la función mostrarTablero()

pude resolver el problema de cuando una ficha quedaba en medio de 2 combinaciones al mismo tiempo, lo que hacemos es hacer una copia de todo el tablero, para posteriormente establecer todas las fichas pertenecientes almenos a una combinación como ficha vacía y así no perder información 

finalmente hice un main de prueba y pasa algo muy curioso, y es que yo de manera manual forcé dos combinaciones, una horizontal y otro vertical, el caso es que al ejecutar el programa varias veces vemos que también se eliminan las demás combinaciones que no estaban planeadas porque igualmente era posible que se presentaran