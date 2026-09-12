#include "reina.h"

Reina::Reina(char color, int fila, int columna)
    : Pieza(color, 'R', fila, columna){
}

bool Reina::esMovimientoValido(int filaDestino, int columnaDestino, bool hayPiezaDestino, bool hayPiezaIntermedia){
    int diferenciaFila=filaDestino-getFila();
    int diferenciaColumna=columnaDestino-getColumna();
    if(diferenciaFila==0 && diferenciaColumna==0){
        return false;
    }

    int filaAbsoluta=(diferenciaFila<0) ? -diferenciaFila : diferenciaFila;
    int columnaAbsoluta=(diferenciaColumna<0) ? -diferenciaColumna : diferenciaColumna;
    bool esLineaRecta=(diferenciaFila==0 || diferenciaColumna==0);
    bool esDiagonal=(filaAbsoluta==columnaAbsoluta);

    if(!esLineaRecta && !esDiagonal){
        return false;
    }

    if(hayPiezaIntermedia){
        return false;
    }

    return true;
}
