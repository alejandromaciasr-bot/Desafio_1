#include <cstdlib>
#include "juego.h"
#include "tablero.h"


bool eliminarCombinaciones(unsigned char *tablero,
                           unsigned int filas,
                           unsigned int columnas)
{
    unsigned int cantidadBytes =
        calcularCantidadBytes(filas, columnas);


    // hacemos una copia compacta del tablero original
    unsigned char *copia =
        new unsigned char[cantidadBytes];


    for (unsigned int i = 0;
         i < cantidadBytes;
         i = i + 1)
    {
        copia[i] =
            tablero[i];
    }


    bool huboCombinaciones =
        false;


    // buscamos combinaciones horizontales
    for (unsigned int fila = 0;
         fila < filas;
         fila = fila + 1)
    {
        unsigned int columna =
            0;


        while (columna < columnas)
        {
            unsigned char ficha =
                obtenerFicha(copia,
                             fila,
                             columna,
                             columnas);


            // solamente analizamos las fichas validas entre 0 y 5
            if (ficha <= 5)
            {
                unsigned int inicio =
                    columna;

                unsigned int cantidad =
                    1;


                while ((inicio + cantidad) < columnas &&
                       obtenerFicha(copia,
                                    fila,
                                    inicio + cantidad,
                                    columnas) == ficha)
                {
                    cantidad =
                        cantidad + 1;
                }


                // si encontramos tres o mas fichas iguales las eliminamos
                if (cantidad >= 3)
                {
                    huboCombinaciones =
                        true;


                    for (unsigned int i = 0;
                         i < cantidad;
                         i = i + 1)
                    {
                        establecerFicha(tablero,
                                        fila,
                                        inicio + i,
                                        columnas,
                                        6);
                    }
                }


                columna =
                    inicio + cantidad;
            }
            else
            {
                columna =
                    columna + 1;
            }
        }
    }


    // buscamos combinaciones verticales
    for (unsigned int columna = 0;
         columna < columnas;
         columna = columna + 1)
    {
        unsigned int fila =
            0;


        while (fila < filas)
        {
            unsigned char ficha =
                obtenerFicha(copia,
                             fila,
                             columna,
                             columnas);


            // solamente analizamos las fichas validas entre 0 y 5
            if (ficha <= 5)
            {
                unsigned int inicio =
                    fila;

                unsigned int cantidad =
                    1;


                while ((inicio + cantidad) < filas &&
                       obtenerFicha(copia,
                                    inicio + cantidad,
                                    columna,
                                    columnas) == ficha)
                {
                    cantidad =
                        cantidad + 1;
                }


                // si encontramos tres o mas fichas iguales las eliminamos
                if (cantidad >= 3)
                {
                    huboCombinaciones =
                        true;


                    for (unsigned int i = 0;
                         i < cantidad;
                         i = i + 1)
                    {
                        establecerFicha(tablero,
                                        inicio + i,
                                        columna,
                                        columnas,
                                        6);
                    }
                }


                fila =
                    inicio + cantidad;
            }
            else
            {
                fila =
                    fila + 1;
            }
        }
    }


    delete[] copia;

    copia =
        nullptr;


    return huboCombinaciones;
}


void aplicarGravedad(unsigned char *tablero,
                     unsigned int filas,
                     unsigned int columnas)
{
    // recorremos cada columna de forma independiente
    for (unsigned int columna = 0;
         columna < columnas;
         columna = columna + 1)
    {
        int filaEscritura =
            static_cast<int>(filas) - 1;


        // recorremos la columna desde abajo hacia arriba
        for (int filaLectura = static_cast<int>(filas) - 1;
             filaLectura >= 0;
             filaLectura = filaLectura - 1)
        {
            unsigned char ficha =
                obtenerFicha(tablero,
                             static_cast<unsigned int>(filaLectura),
                             columna,
                             columnas);


            // si encontramos una ficha real la movemos hacia abajo
            if (ficha <= 5)
            {
                establecerFicha(tablero,
                                static_cast<unsigned int>(filaEscritura),
                                columna,
                                columnas,
                                ficha);


                filaEscritura =
                    filaEscritura - 1;
            }
        }


        // las posiciones restantes en la parte superior quedan vacias
        while (filaEscritura >= 0)
        {
            establecerFicha(tablero,
                            static_cast<unsigned int>(filaEscritura),
                            columna,
                            columnas,
                            6);


            filaEscritura =
                filaEscritura - 1;
        }
    }
}


void rellenarVacios(unsigned char *tablero,
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


            // si encontramos una posicion vacia generamos una nueva ficha
            if (ficha == 6)
            {
                unsigned char nuevaFicha =
                    static_cast<unsigned char>(rand() % 6);


                establecerFicha(tablero,
                                fila,
                                columna,
                                columnas,
                                nuevaFicha);
            }
        }
    }
}


unsigned int resolverCascadas(unsigned char *tablero,
                              unsigned int filas,
                              unsigned int columnas)
{
    unsigned int cantidadCascadas =
        0;


    bool huboCombinaciones =
        eliminarCombinaciones(tablero,
                              filas,
                              columnas);


    while (huboCombinaciones)
    {
        // hacemos caer las fichas hacia la parte inferior
        aplicarGravedad(tablero,
                        filas,
                        columnas);


        // generamos nuevas fichas en las posiciones vacias
        rellenarVacios(tablero,
                       filas,
                       columnas);


        cantidadCascadas =
            cantidadCascadas + 1;


        // verificamos si las nuevas posiciones forman otra combinacion
        huboCombinaciones =
            eliminarCombinaciones(tablero,
                                  filas,
                                  columnas);
    }


    return cantidadCascadas;
}
