#include <iostream>
#include <cstdlib>
#include <ctime>
#include "tablero.h"
#include "juego.h"

using namespace std;


int leerEntero()
{
    int valor;

    while (!(cin >> valor))
    {
        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Entrada invalida. Intente nuevamente: ";
    }

    return valor;
}


int main()
{
    const unsigned int PUNTOS_POR_FICHA =
        10;

    const unsigned int PUNTOS_POR_CASCADA =
        20;

    const unsigned int META_PUNTOS =
        300;


    srand(
        static_cast<unsigned int>(
            time(nullptr)
            )
        );


    int entradaFilas;
    int entradaColumnas;


    do
    {
        cout << "Cantidad inicial de filas: ";
        entradaFilas =
            leerEntero();
    }
    while (entradaFilas < 3);


    do
    {
        cout << "Cantidad inicial de columnas: ";
        entradaColumnas =
            leerEntero();
    }
    while (entradaColumnas < 3);


    unsigned int filas =
        static_cast<unsigned int>(entradaFilas);

    unsigned int columnas =
        static_cast<unsigned int>(entradaColumnas);


    unsigned int bytesReservados =
        calcularCantidadBytes(filas, columnas);


    unsigned char *tablero =
        crearTablero(filas, columnas);


    llenarTablero(tablero,
                  filas,
                  columnas);


    // estabilizamos el tablero inicial sin otorgar puntos
    unsigned int combinacionesIniciales =
        0;

    unsigned int fichasInicialesEliminadas =
        0;

    resolverCascadas(tablero,
                     filas,
                     columnas,
                     combinacionesIniciales,
                     fichasInicialesEliminadas);


    unsigned int eliminacionesUsuario =
        0;

    unsigned int fichasEliminadasTotal =
        0;

    unsigned int combinacionesDetectadasTotal =
        0;

    unsigned int cascadasActuales =
        0;

    unsigned int puntuacion =
        0;


    while (puntuacion < META_PUNTOS)
    {
        cout << endl;
        cout << "================ SWEET CRUSH ================" << endl;
        cout << endl;

        cout << "Tablero:" << endl;
        mostrarTablero(tablero,
                       filas,
                       columnas);

        cout << endl;
        cout << "Tablero en binario:" << endl;
        mostrarTableroBinario(tablero,
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

        cout << "Eliminaciones del usuario: "
             << eliminacionesUsuario
             << endl;

        cout << "Fichas eliminadas en total: "
             << fichasEliminadasTotal
             << endl;

        cout << "Combinaciones detectadas: "
             << combinacionesDetectadasTotal
             << endl;

        cout << "Cascadas de la accion anterior: "
             << cascadasActuales
             << endl;

        cout << "Puntuacion: "
             << puntuacion
             << " / "
             << META_PUNTOS
             << endl;

        cout << endl;
        cout << "1. Eliminar ficha" << endl;
        cout << "2. Agregar fila" << endl;
        cout << "3. Eliminar fila" << endl;
        cout << "4. Agregar columna" << endl;
        cout << "5. Eliminar columna" << endl;
        cout << endl;
        cout << "Opcion: ";


        int opcion =
            leerEntero();


        bool accionValida =
            false;

        unsigned int fichasEliminadasTurno =
            0;

        unsigned int combinacionesTurno =
            0;

        cascadasActuales =
            0;


        if (opcion == 1)
        {
            cout << "Fila: ";
            int filaEntrada =
                leerEntero();

            cout << "Columna: ";
            int columnaEntrada =
                leerEntero();

            if (filaEntrada >= 0 && columnaEntrada >= 0)
            {
                accionValida =
                    eliminarFichaUsuario(
                        tablero,
                        filas,
                        columnas,
                        static_cast<unsigned int>(filaEntrada),
                        static_cast<unsigned int>(columnaEntrada),
                        cascadasActuales,
                        combinacionesTurno,
                        fichasEliminadasTurno
                        );
            }

            if (accionValida)
            {
                eliminacionesUsuario =
                    eliminacionesUsuario + 1;
            }
        }
        else if (opcion == 2)
        {
            cout << "Posicion de la nueva fila: ";
            int posicionEntrada =
                leerEntero();

            if (posicionEntrada >= 0)
            {
                accionValida =
                    agregarFila(
                        tablero,
                        filas,
                        columnas,
                        static_cast<unsigned int>(posicionEntrada),
                        bytesReservados
                        );
            }

            if (accionValida)
            {
                cascadasActuales =
                    resolverCascadas(tablero,
                                     filas,
                                     columnas,
                                     combinacionesTurno,
                                     fichasEliminadasTurno);
            }
        }
        else if (opcion == 3)
        {
            cout << "Fila a eliminar: ";
            int posicionEntrada =
                leerEntero();

            unsigned int fichasDirectas =
                columnas;

            if (posicionEntrada >= 0)
            {
                accionValida =
                    eliminarFila(
                        tablero,
                        filas,
                        columnas,
                        static_cast<unsigned int>(posicionEntrada),
                        bytesReservados
                        );
            }

            if (accionValida)
            {
                eliminacionesUsuario =
                    eliminacionesUsuario + 1;

                fichasEliminadasTurno =
                    fichasEliminadasTurno + fichasDirectas;

                cascadasActuales =
                    resolverCascadas(tablero,
                                     filas,
                                     columnas,
                                     combinacionesTurno,
                                     fichasEliminadasTurno);
            }
        }
        else if (opcion == 4)
        {
            cout << "Posicion de la nueva columna: ";
            int posicionEntrada =
                leerEntero();

            if (posicionEntrada >= 0)
            {
                accionValida =
                    agregarColumna(
                        tablero,
                        filas,
                        columnas,
                        static_cast<unsigned int>(posicionEntrada),
                        bytesReservados
                        );
            }

            if (accionValida)
            {
                cascadasActuales =
                    resolverCascadas(tablero,
                                     filas,
                                     columnas,
                                     combinacionesTurno,
                                     fichasEliminadasTurno);
            }
        }
        else if (opcion == 5)
        {
            cout << "Columna a eliminar: ";
            int posicionEntrada =
                leerEntero();

            unsigned int fichasDirectas =
                filas;

            if (posicionEntrada >= 0)
            {
                accionValida =
                    eliminarColumna(
                        tablero,
                        filas,
                        columnas,
                        static_cast<unsigned int>(posicionEntrada),
                        bytesReservados
                        );
            }

            if (accionValida)
            {
                eliminacionesUsuario =
                    eliminacionesUsuario + 1;

                fichasEliminadasTurno =
                    fichasEliminadasTurno + fichasDirectas;

                cascadasActuales =
                    resolverCascadas(tablero,
                                     filas,
                                     columnas,
                                     combinacionesTurno,
                                     fichasEliminadasTurno);
            }
        }


        if (accionValida)
        {
            fichasEliminadasTotal =
                fichasEliminadasTotal + fichasEliminadasTurno;

            combinacionesDetectadasTotal =
                combinacionesDetectadasTotal + combinacionesTurno;

            unsigned int puntosTurno =
                fichasEliminadasTurno * PUNTOS_POR_FICHA +
                cascadasActuales * PUNTOS_POR_CASCADA;

            puntuacion =
                puntuacion + puntosTurno;

            cout << endl;
            cout << "Fichas eliminadas en esta accion: "
                 << fichasEliminadasTurno
                 << endl;

            cout << "Combinaciones en esta accion: "
                 << combinacionesTurno
                 << endl;

            cout << "Cascadas en esta accion: "
                 << cascadasActuales
                 << endl;

            cout << "Puntos obtenidos: "
                 << puntosTurno
                 << endl;
        }
        else
        {
            cout << endl;
            cout << "Operacion invalida." << endl;
        }
    }


    cout << endl;
    cout << "================ FIN DEL JUEGO ================" << endl;
    cout << "Puntuacion final: "
         << puntuacion
         << endl;

    cout << "Fichas eliminadas en total: "
         << fichasEliminadasTotal
         << endl;

    cout << "Combinaciones detectadas: "
         << combinacionesDetectadasTotal
         << endl;

    cout << "Eliminaciones del usuario: "
         << eliminacionesUsuario
         << endl;


    liberarTablero(tablero);

    tablero =
        nullptr;


    return 0;
}
