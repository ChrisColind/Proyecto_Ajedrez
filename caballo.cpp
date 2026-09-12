#include "caballo.h"

Caballo::Caballo(char color, int fila, int columna): Pieza(color, 'C', fila, columna){
}

bool Caballo::esMovimientoValido(int filaDestino, int columnaDestino, bool hayPiezaDestino, bool hayPiezaIntermedia){
    int diferenciaFila=filaDestino-getFila();
    int diferenciaColumna=columnaDestino-getColumna();

    int filaAbsoluta=(diferenciaFila<0) ? -diferenciaFila : diferenciaFila;
    int columnaAbsoluta=(diferenciaColumna<0) ? -diferenciaColumna : diferenciaColumna;
    bool movimientoEnL=(filaAbsoluta==2 && columnaAbsoluta==1) || (filaAbsoluta==1 && columnaAbsoluta==2);

    return movimientoEnL;
}