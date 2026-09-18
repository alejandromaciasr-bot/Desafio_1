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


    srand(
        static_cast<unsigned int>(
            time(nullptr)
            )
        );


    unsigned int bytesReservados =
        calcularCantidadBytes(filas, columnas);


    unsigned char *tablero =
        crearTablero(filas, columnas);


    llenarTablero(tablero,
                  filas,
                  columnas);


    cout << "Tablero inicial:" << endl;
    cout << endl;

    mostrarTablero(tablero,
                   filas,
                   columnas);


    cout << endl;

    cout << "Dimensiones: "
         << filas
         << " x "
         << columnas
         << endl;

    cout << "Bytes necesarios: "
         << calcularCantidadBytes(filas, columnas)
         << endl;

    cout << "Bytes reservados: "
         << bytesReservados
         << endl;


    // eliminamos una fila intermedia
    eliminarFila(tablero,
                 filas,
                 columnas,
                 2,
                 bytesReservados);


    resolverCascadas(tablero,
                     filas,
                     columnas);


    cout << endl;
    cout << "Despues de eliminar la fila 2:" << endl;
    cout << endl;

    mostrarTablero(tablero,
                   filas,
                   columnas);


    cout << endl;

    cout << "Dimensiones: "
         << filas
         << " x "
         << columnas
         << endl;

    cout << "Bytes necesarios: "
         << calcularCantidadBytes(filas, columnas)
         << endl;

    cout << "Bytes reservados: "
         << bytesReservados
         << endl;


    // eliminamos una columna intermedia
    eliminarColumna(tablero,
                    filas,
                    columnas,
                    2,
                    bytesReservados);


    resolverCascadas(tablero,
                     filas,
                     columnas);


    cout << endl;
    cout << "Despues de eliminar la columna 2:" << endl;
    cout << endl;

    mostrarTablero(tablero,
                   filas,
                   columnas);


    cout << endl;

    cout << "Dimensiones: "
         << filas
         << " x "
         << columnas
         << endl;

    cout << "Bytes necesarios: "
         << calcularCantidadBytes(filas, columnas)
         << endl;

    cout << "Bytes reservados: "
         << bytesReservados
         << endl;


    // agregamos nuevamente una fila intermedia
    agregarFila(tablero,
                filas,
                columnas,
                2,
                bytesReservados);


    resolverCascadas(tablero,
                     filas,
                     columnas);


    // agregamos nuevamente una columna intermedia
    agregarColumna(tablero,
                   filas,
                   columnas,
                   1,
                   bytesReservados);


    resolverCascadas(tablero,
                     filas,
                     columnas);


    cout << endl;
    cout << "Despues de agregar una fila y una columna:" << endl;
    cout << endl;

    mostrarTablero(tablero,
                   filas,
                   columnas);


    cout << endl;

    cout << "Dimensiones finales: "
         << filas
         << " x "
         << columnas
         << endl;

    cout << "Bytes necesarios: "
         << calcularCantidadBytes(filas, columnas)
         << endl;

    cout << "Bytes reservados: "
         << bytesReservados
         << endl;


    liberarTablero(tablero);

    tablero =
        nullptr;


    return 0;
}
