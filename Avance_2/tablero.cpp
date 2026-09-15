#include <iostream>
#include <cstdlib>
#include "tablero.h"

using namespace std;


unsigned int calcularCantidadBytes(unsigned int filas,
                                   unsigned int columnas)
{
    unsigned int cantidadBits = filas * columnas * 3;

    unsigned int cantidadBytes = (cantidadBits + 7) / 8;

    return cantidadBytes;
}


unsigned char *crearTablero(unsigned int filas,
                            unsigned int columnas)
{
    unsigned int cantidadBytes =
        calcularCantidadBytes(filas, columnas);

    unsigned char *tablero =
        new unsigned char[cantidadBytes]();

    return tablero;
}


void liberarTablero(unsigned char *tablero)
{
    delete[] tablero;
}


unsigned char obtenerFicha(const unsigned char *tablero,
                           unsigned int fila,
                           unsigned int columna,
                           unsigned int columnas)
{
    // convertimos fila y columna en una posicion lineal
    unsigned int indice =
        fila * columnas + columna;


    // cada ficha ocupa exactamente 3 bits
    unsigned int bitInicial =
        indice * 3;


    // determinamos en que byte comienza la ficha
    unsigned int byte =
        bitInicial / 8;


    // determinamos en que posicion dentro del byte comienza
    unsigned int desplazamiento =
        bitInicial % 8;


    // copiamos el byte donde comienza la ficha
    unsigned int bloque =
        tablero[byte];


    // si la ficha comienza en el bit 6 o 7,
    // parte de ella esta almacenada en el siguiente byte
    if (desplazamiento > 5)
    {
        bloque =
            bloque |
            (static_cast<unsigned int>(tablero[byte + 1]) << 8);
    }


    // movemos la ficha hasta los tres bits menos significativos
    bloque =
        bloque >> desplazamiento;


    // conservamos solamente los ultimos 3 bits
    return static_cast<unsigned char>(bloque & 0x07);
}


void establecerFicha(unsigned char *tablero,
                     unsigned int fila,
                     unsigned int columna,
                     unsigned int columnas,
                     unsigned char ficha)
{
    // convertimos fila y columna en una posicion lineal
    unsigned int indice =
        fila * columnas + columna;


    // calculamos el bit donde comienza la ficha
    unsigned int bitInicial =
        indice * 3;


    // calculamos el byte donde comienza
    unsigned int byte =
        bitInicial / 8;


    // calculamos la posicion dentro de ese byte
    unsigned int desplazamiento =
        bitInicial % 8;


    // copiamos el byte donde comienza la ficha
    unsigned int bloque =
        tablero[byte];


    // si la ficha esta dividida entre dos bytes,
    // agregamos temporalmente el siguiente byte al bloque
    if (desplazamiento > 5)
    {
        bloque =
            bloque |
            (static_cast<unsigned int>(tablero[byte + 1]) << 8);
    }


    // creamos una mascara de tres bits ubicada
    // exactamente donde queremos guardar la ficha
    unsigned int mascara =
        0x07 << desplazamiento;


    // ponemos en cero los tres bits donde estaba la ficha
    bloque =
        bloque & ~mascara;


    // colocamos la nueva ficha en su posicion
    bloque =
        bloque |
        ((static_cast<unsigned int>(ficha) & 0x07)
         << desplazamiento);


    // guardamos nuevamente los primeros 8 bits
    tablero[byte] =
        static_cast<unsigned char>(bloque & 0xFF);


    // si utilizamos parte del siguiente byte,
    // tambien debemos actualizarlo
    if (desplazamiento > 5)
    {
        tablero[byte + 1] =
            static_cast<unsigned char>((bloque >> 8) & 0xFF);
    }
}


void llenarTablero(unsigned char *tablero,
                   unsigned int filas,
                   unsigned int columnas)
{
    for (unsigned int fila = 0;
         fila < filas;
         fila = fila + 1)
    {
        for (unsigned int columna = 0;
             columna < columnas;
             columna = columna + 1)
        {
            // generamos una ficha aleatoria entre 0 y 5
            unsigned char ficha =
                static_cast<unsigned char>(rand() % 6);


            // almacenamos la ficha utilizando los 3 bits correspondientes
            establecerFicha(tablero,
                            fila,
                            columna,
                            columnas,
                            ficha);
        }
    }
}


void mostrarTablero(const unsigned char *tablero,
                    unsigned int filas,
                    unsigned int columnas)
{
    for (unsigned int fila = 0;
         fila < filas;
         fila = fila + 1)
    {
        for (unsigned int columna = 0;
             columna < columnas;
             columna = columna + 1)
        {
            // obtenemos la ficha almacenada en esta posicion
            unsigned char ficha =
                obtenerFicha(tablero,
                             fila,
                             columna,
                             columnas);


            // convertimos los valores 0-5 en las letras A-F
            char simbolo =
                static_cast<char>('A' + ficha);


            cout << simbolo << " ";
        }

        cout << endl;
    }
}
