#include <iostream>
#include <cstdlib>
#include <ctime>
#include "tablero.h"
#include "juego.h"

using namespace std;


int main()
{
    unsigned int filas =
        5;

    unsigned int columnas =
        5;


    // inicializamos la semilla del generador de numeros aleatorios
    srand(
        static_cast<unsigned int>(
            time(nullptr)
            )
        );


    // creamos dinamicamente el tablero
    unsigned char *tablero =
        crearTablero(filas, columnas);


    // llenamos el tablero con fichas aleatorias
    llenarTablero(tablero,
                  filas,
                  columnas);


    // forzamos una combinacion horizontal de tres fichas B
    establecerFicha(tablero,
                    1,
                    0,
                    columnas,
                    1);

    establecerFicha(tablero,
                    1,
                    1,
                    columnas,
                    1);

    establecerFicha(tablero,
                    1,
                    2,
                    columnas,
                    1);


    // forzamos una combinacion vertical de tres fichas E
    establecerFicha(tablero,
                    2,
                    4,
                    columnas,
                    4);

    establecerFicha(tablero,
                    3,
                    4,
                    columnas,
                    4);

    establecerFicha(tablero,
                    4,
                    4,
                    columnas,
                    4);


    cout << "Tablero antes de resolver combinaciones:" << endl;
    cout << endl;


    mostrarTablero(tablero,
                   filas,
                   columnas);


    cout << endl;


    unsigned int cantidadCascadas =
        resolverCascadas(tablero,
                         filas,
                         columnas);


    cout << "Tablero despues de resolver las cascadas:" << endl;
    cout << endl;


    mostrarTablero(tablero,
                   filas,
                   columnas);


    cout << endl;

    cout << "Cantidad de cascadas realizadas: "
         << cantidadCascadas
         << endl;


    cout << "Cantidad de bytes utilizados: "
         << calcularCantidadBytes(filas, columnas)
         << endl;


    // liberamos la memoria dinamica
    liberarTablero(tablero);

    tablero =
        nullptr;


    return 0;
}
