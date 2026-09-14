#include <iostream>
#include "tablero.h"

using namespace std;


int main()
{
    unsigned int filas = 2;
    unsigned int columnas = 4;

    unsigned char *tablero =
        crearTablero(filas, columnas);


    establecerFicha(tablero, 0, 0, columnas, 0);
    establecerFicha(tablero, 0, 1, columnas, 1);
    establecerFicha(tablero, 0, 2, columnas, 2);
    establecerFicha(tablero, 0, 3, columnas, 3);

    establecerFicha(tablero, 1, 0, columnas, 4);
    establecerFicha(tablero, 1, 1, columnas, 5);
    establecerFicha(tablero, 1, 2, columnas, 0);
    establecerFicha(tablero, 1, 3, columnas, 1);


    cout << "Cantidad de bytes: "
         << calcularCantidadBytes(filas, columnas)
         << endl;


    for (unsigned int fila = 0; fila < filas; fila++)
    {
        for (unsigned int columna = 0;
             columna < columnas;
             columna++)
        {
            cout
                << static_cast<unsigned int>(
                       obtenerFicha(tablero,
                                    fila,
                                    columna,
                                    columnas))
                << " ";
        }

        cout << endl;
    }


    liberarTablero(tablero);

    tablero = nullptr;


    return 0;
}
