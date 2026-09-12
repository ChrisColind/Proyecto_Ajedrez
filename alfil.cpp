#include "alfil.h"

Alfil::Alfil(char color, int fila, int columna)
    : Pieza(color, 'A', fila, columna){
}

bool Alfil::esMovimientoValido(int filaDestino, int columnaDestino, bool hayPiezaDestino, bool hayPiezaIntermedia){
    int diferenciaFila=filaDestino-getFila();
    int diferenciaColumna=columnaDestino-getColumna();

    if(diferenciaFila==0 && diferenciaColumna==0){
        return false;
    }

    int filaAbsoluta=(diferenciaFila<0) ? -diferenciaFila : diferenciaFila;
    int columnaAbsoluta=(diferenciaColumna<0) ? -diferenciaColumna : diferenciaColumna;

    if(filaAbsoluta!=columnaAbsoluta){
        return false;
    }

    if(hayPiezaIntermedia){
        return false;
    }

    return true;
}
