#include <iostream>
#include <cstdlib>
#include "tablero.h"

using namespace std;


unsigned int calcularCantidadBytes(unsigned int filas,
                                   unsigned int columnas)
{
    unsigned int cantidadBits =
        filas * columnas * 3;

    unsigned int cantidadBytes =
        (cantidadBits + 7) / 8;

    return cantidadBytes;
}


unsigned char generarFichaAleatoria()
{
    unsigned long cantidadValores =
        static_cast<unsigned long>(RAND_MAX) + 1UL;

    unsigned long limite =
        cantidadValores - (cantidadValores % 6UL);

    unsigned long valor;

    do
    {
        valor =
            static_cast<unsigned long>(rand());
    }
    while (valor >= limite);

    return static_cast<unsigned char>(valor % 6UL);
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

    // creamos una mascara de tres bits
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
            unsigned char ficha =
                generarFichaAleatoria();

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
            unsigned char ficha =
                obtenerFicha(tablero,
                             fila,
                             columna,
                             columnas);

            if (ficha <= 5)
            {
                char simbolo =
                    static_cast<char>('A' + ficha);

                cout << simbolo << " ";
            }
            else if (ficha == 6)
            {
                cout << ". ";
            }
            else
            {
                cout << "? ";
            }
        }

        cout << endl;
    }
}


void mostrarTableroBinario(const unsigned char *tablero,
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
            unsigned char ficha =
                obtenerFicha(tablero,
                             fila,
                             columna,
                             columnas);

            for (int bit = 2;
                 bit >= 0;
                 bit = bit - 1)
            {
                unsigned int valorBit =
                    (static_cast<unsigned int>(ficha) >> bit) & 0x01;

                cout << valorBit;
            }

            cout << " ";
        }

        cout << endl;
    }
}


bool agregarFila(unsigned char *&tablero,
                 unsigned int &filas,
                 unsigned int columnas,
                 unsigned int posicion,
                 unsigned int &bytesReservados)
{
    if (posicion > filas)
    {
        return false;
    }

    unsigned int nuevasFilas =
        filas + 1;

    unsigned int bytesNecesarios =
        calcularCantidadBytes(nuevasFilas, columnas);

    unsigned char *nuevoTablero =
        new unsigned char[bytesNecesarios]();

    for (unsigned int nuevaFila = 0;
         nuevaFila < nuevasFilas;
         nuevaFila = nuevaFila + 1)
    {
        for (unsigned int columna = 0;
             columna < columnas;
             columna = columna + 1)
        {
            if (nuevaFila == posicion)
            {
                unsigned char ficha =
                    generarFichaAleatoria();

                establecerFicha(nuevoTablero,
                                nuevaFila,
                                columna,
                                columnas,
                                ficha);
            }
            else
            {
                unsigned int filaAnterior;

                if (nuevaFila < posicion)
                {
                    filaAnterior =
                        nuevaFila;
                }
                else
                {
                    filaAnterior =
                        nuevaFila - 1;
                }

                unsigned char ficha =
                    obtenerFicha(tablero,
                                 filaAnterior,
                                 columna,
                                 columnas);

                establecerFicha(nuevoTablero,
                                nuevaFila,
                                columna,
                                columnas,
                                ficha);
            }
        }
    }

    if (bytesNecesarios > bytesReservados)
    {
        delete[] tablero;

        tablero =
            nuevoTablero;

        bytesReservados =
            bytesNecesarios;
    }
    else
    {
        for (unsigned int i = 0;
             i < bytesReservados;
             i = i + 1)
        {
            tablero[i] =
                0;
        }

        for (unsigned int i = 0;
             i < bytesNecesarios;
             i = i + 1)
        {
            tablero[i] =
                nuevoTablero[i];
        }

        delete[] nuevoTablero;

        nuevoTablero =
            nullptr;
    }

    filas =
        nuevasFilas;

    return true;
}


bool eliminarFila(unsigned char *&tablero,
                  unsigned int &filas,
                  unsigned int columnas,
                  unsigned int posicion,
                  unsigned int &bytesReservados)
{
    if (posicion >= filas || filas <= 1)
    {
        return false;
    }

    unsigned int nuevasFilas =
        filas - 1;

    unsigned int bytesNecesarios =
        calcularCantidadBytes(nuevasFilas, columnas);

    unsigned char *nuevoTablero =
        new unsigned char[bytesNecesarios]();

    unsigned int nuevaFila =
        0;

    for (unsigned int filaAnterior = 0;
         filaAnterior < filas;
         filaAnterior = filaAnterior + 1)
    {
        if (filaAnterior != posicion)
        {
            for (unsigned int columna = 0;
                 columna < columnas;
                 columna = columna + 1)
            {
                unsigned char ficha =
                    obtenerFicha(tablero,
                                 filaAnterior,
                                 columna,
                                 columnas);

                establecerFicha(nuevoTablero,
                                nuevaFila,
                                columna,
                                columnas,
                                ficha);
            }

            nuevaFila =
                nuevaFila + 1;
        }
    }

    bool reducirMemoria =
        (bytesNecesarios * 100) < (bytesReservados * 65);

    if (reducirMemoria)
    {
        delete[] tablero;

        tablero =
            nuevoTablero;

        bytesReservados =
            bytesNecesarios;
    }
    else
    {
        for (unsigned int i = 0;
             i < bytesReservados;
             i = i + 1)
        {
            tablero[i] =
                0;
        }

        for (unsigned int i = 0;
             i < bytesNecesarios;
             i = i + 1)
        {
            tablero[i] =
                nuevoTablero[i];
        }

        delete[] nuevoTablero;

        nuevoTablero =
            nullptr;
    }

    filas =
        nuevasFilas;

    return true;
}


bool agregarColumna(unsigned char *&tablero,
                    unsigned int filas,
                    unsigned int &columnas,
                    unsigned int posicion,
                    unsigned int &bytesReservados)
{
    if (posicion > columnas)
    {
        return false;
    }

    unsigned int nuevasColumnas =
        columnas + 1;

    unsigned int bytesNecesarios =
        calcularCantidadBytes(filas, nuevasColumnas);

    unsigned char *nuevoTablero =
        new unsigned char[bytesNecesarios]();

    for (unsigned int fila = 0;
         fila < filas;
         fila = fila + 1)
    {
        for (unsigned int nuevaColumna = 0;
             nuevaColumna < nuevasColumnas;
             nuevaColumna = nuevaColumna + 1)
        {
            if (nuevaColumna == posicion)
            {
                unsigned char ficha =
                    generarFichaAleatoria();

                establecerFicha(nuevoTablero,
                                fila,
                                nuevaColumna,
                                nuevasColumnas,
                                ficha);
            }
            else
            {
                unsigned int columnaAnterior;

                if (nuevaColumna < posicion)
                {
                    columnaAnterior =
                        nuevaColumna;
                }
                else
                {
                    columnaAnterior =
                        nuevaColumna - 1;
                }

                unsigned char ficha =
                    obtenerFicha(tablero,
                                 fila,
                                 columnaAnterior,
                                 columnas);

                establecerFicha(nuevoTablero,
                                fila,
                                nuevaColumna,
                                nuevasColumnas,
                                ficha);
            }
        }
    }

    if (bytesNecesarios > bytesReservados)
    {
        delete[] tablero;

        tablero =
            nuevoTablero;

        bytesReservados =
            bytesNecesarios;
    }
    else
    {
        for (unsigned int i = 0;
             i < bytesReservados;
             i = i + 1)
        {
            tablero[i] =
                0;
        }

        for (unsigned int i = 0;
             i < bytesNecesarios;
             i = i + 1)
        {
            tablero[i] =
                nuevoTablero[i];
        }

        delete[] nuevoTablero;

        nuevoTablero =
            nullptr;
    }

    columnas =
        nuevasColumnas;

    return true;
}


bool eliminarColumna(unsigned char *&tablero,
                     unsigned int filas,
                     unsigned int &columnas,
                     unsigned int posicion,
                     unsigned int &bytesReservados)
{
    if (posicion >= columnas || columnas <= 1)
    {
        return false;
    }

    unsigned int nuevasColumnas =
        columnas - 1;

    unsigned int bytesNecesarios =
        calcularCantidadBytes(filas, nuevasColumnas);

    unsigned char *nuevoTablero =
        new unsigned char[bytesNecesarios]();

    for (unsigned int fila = 0;
         fila < filas;
         fila = fila + 1)
    {
        unsigned int nuevaColumna =
            0;

        for (unsigned int columnaAnterior = 0;
             columnaAnterior < columnas;
             columnaAnterior = columnaAnterior + 1)
        {
            if (columnaAnterior != posicion)
            {
                unsigned char ficha =
                    obtenerFicha(tablero,
                                 fila,
                                 columnaAnterior,
                                 columnas);

                establecerFicha(nuevoTablero,
                                fila,
                                nuevaColumna,
                                nuevasColumnas,
                                ficha);

                nuevaColumna =
                    nuevaColumna + 1;
            }
        }
    }

    bool reducirMemoria =
        (bytesNecesarios * 100) < (bytesReservados * 65);

    if (reducirMemoria)
    {
        delete[] tablero;

        tablero =
            nuevoTablero;

        bytesReservados =
            bytesNecesarios;
    }
    else
    {
        for (unsigned int i = 0;
             i < bytesReservados;
             i = i + 1)
        {
            tablero[i] =
                0;
        }

        for (unsigned int i = 0;
             i < bytesNecesarios;
             i = i + 1)
        {
            tablero[i] =
                nuevoTablero[i];
        }

        delete[] nuevoTablero;

        nuevoTablero =
            nullptr;
    }

    columnas =
        nuevasColumnas;

    return true;
}
