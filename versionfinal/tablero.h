#ifndef TABLERO_H
#define TABLERO_H

unsigned int calcularCantidadBytes(unsigned int filas,
                                   unsigned int columnas);

unsigned char generarFichaAleatoria();

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

void llenarTablero(unsigned char *tablero,
                   unsigned int filas,
                   unsigned int columnas);

void mostrarTablero(const unsigned char *tablero,
                    unsigned int filas,
                    unsigned int columnas);

void mostrarTableroBinario(const unsigned char *tablero,
                           unsigned int filas,
                           unsigned int columnas);

bool agregarFila(unsigned char *&tablero,
                 unsigned int &filas,
                 unsigned int columnas,
                 unsigned int posicion,
                 unsigned int &bytesReservados);

bool eliminarFila(unsigned char *&tablero,
                  unsigned int &filas,
                  unsigned int columnas,
                  unsigned int posicion,
                  unsigned int &bytesReservados);

bool agregarColumna(unsigned char *&tablero,
                    unsigned int filas,
                    unsigned int &columnas,
                    unsigned int posicion,
                    unsigned int &bytesReservados);

bool eliminarColumna(unsigned char *&tablero,
                     unsigned int filas,
                     unsigned int &columnas,
                     unsigned int posicion,
                     unsigned int &bytesReservados);

#endif
