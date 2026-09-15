#include <iostream>
#include <cstdlib>
#include <ctime>
#include "tablero.h"

using namespace std;


int main()
{
    unsigned int filas = 5;
    unsigned int columnas = 5;


    // inicializamos la semilla del generador de numeros aleatorios
    srand(static_cast<unsigned int>(time(nullptr)));


    // creamos dinamicamente el tablero
    unsigned char *tablero =
        crearTablero(filas, columnas);


    // llenamos el tablero con fichas aleatorias
    llenarTablero(tablero,
                  filas,
                  columnas);


    cout << "Tablero:" << endl;
    cout << endl;


    // mostramos las fichas utilizando los simbolos A-F
    mostrarTablero(tablero,
                   filas,
                   columnas);


    cout << endl;

    cout << "Cantidad de bytes utilizados: "
         << calcularCantidadBytes(filas, columnas)
         << endl;


    // liberamos la memoria dinamica
    liberarTablero(tablero);

    tablero = nullptr;


    return 0;
}
