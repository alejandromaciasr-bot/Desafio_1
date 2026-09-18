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
    for (unsigned int columna = 0;
         columna < columnas;
         columna = columna + 1)
    {
        int filaEscritura =
            static_cast<int>(filas) - 1;


        for (int filaLectura = static_cast<int>(filas) - 1;
             filaLectura >= 0;
             filaLectura = filaLectura - 1)
        {
            unsigned char ficha =
                obtenerFicha(tablero,
                             static_cast<unsigned int>(filaLectura),
                             columna,
                             columnas);


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
        aplicarGravedad(tablero,
                        filas,
                        columnas);


        rellenarVacios(tablero,
                       filas,
                       columnas);


        cantidadCascadas =
            cantidadCascadas + 1;


        huboCombinaciones =
            eliminarCombinaciones(tablero,
                                  filas,
                                  columnas);
    }


    return cantidadCascadas;
}


bool eliminarFichaUsuario(unsigned char *tablero,
                          unsigned int filas,
                          unsigned int columnas,
                          unsigned int fila,
                          unsigned int columna,
                          unsigned int &cantidadCascadas)
{
    // verificamos que la posicion seleccionada exista
    if (fila >= filas || columna >= columnas)
    {
        return false;
    }


    // marcamos la ficha seleccionada como vacia
    establecerFicha(tablero,
                    fila,
                    columna,
                    columnas,
                    6);


    // las fichas superiores ocupan el espacio generado
    aplicarGravedad(tablero,
                    filas,
                    columnas);


    // completamos nuevamente el tablero
    rellenarVacios(tablero,
                   filas,
                   columnas);


    // procesamos las combinaciones producidas por el movimiento
    cantidadCascadas =
        resolverCascadas(tablero,
                         filas,
                         columnas);


    return true;
}
