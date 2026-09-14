#ifndef TABLERO_H
#define TABLERO_H


unsigned int calcularCantidadBytes(unsigned int filas,
                                   unsigned int columnas);


unsigned char *crearTablero(unsigned int filas,
                            unsigned int columnas);


void liberarTablero(unsigned char *tablero);


unsigned char obtenerFicha(const unsigned char *tablero,
                           unsigned int fila,
                           unsigned int columna,
                           unsigned int columnas);


void establecerFicha(unsigned char *tablero,
                     unsigned int fila,
                     unsigned int columna,
                     unsigned int columnas,
                     unsigned char ficha);


#endif
