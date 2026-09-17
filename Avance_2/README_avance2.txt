ahora el programa es capaz de generar un tablero aleatorio diferente cada vez que lo ejecutamos, tuve que usar ctime para poder tener una semilla diferente cada vez que ejecuto el código, me pareció interesante que rand() realmente genera números pseudoaleatorios respecto a una semilla particular.

en el código como tal lo que hice fue esto:
- cree llenarTablero() que recorre todas las posiciones y genera fichas aleatorias entre 0 y 5
- cree mostrarTablero() que recorre el tablero y muestra los valores 0-5 como letras A-F
- hice uso de rand() srand() y time() para que el tablero no salga igual en cada ejecución	