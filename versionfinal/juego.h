#ifndef JUEGO_H
#define JUEGO_H

bool eliminarCombinaciones(unsigned char *tablero,
                           unsigned int filas,
                           unsigned int columnas,
                           unsigned int &combinacionesDetectadas,
                           unsigned int &fichasEliminadas);

void aplicarGravedad(unsigned char *tablero,
                     unsigned int filas,
                     unsigned int columnas);

void rellenarVacios(unsigned char *tablero,
                    unsigned int filas,
                    unsigned int columnas);

unsigned int resolverCascadas(unsigned char *tablero,
                              unsigned int filas,
                              unsigned int columnas,
                              unsigned int &combinacionesDetectadas,
                              unsigned int &fichasEliminadas);

bool eliminarFichaUsuario(unsigned char *tablero,
                          unsigned int filas,
                          unsigned int columnas,
                          unsigned int fila,
                          unsigned int columna,
                          unsigned int &cantidadCascadas,
                          unsigned int &combinacionesDetectadas,
                          unsigned int &fichasEliminadas);

#endif
