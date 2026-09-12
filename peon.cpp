#include "peon.h"

Peon::Peon(char color, int fila, int columna)
    : Pieza(color, 'P', fila, columna){
}

bool Peon::esMovimientoValido(int filaDestino, int columnaDestino, bool hayPiezaDestino, bool hayPiezaIntermedia){
    int direccion=(getColor()=='R') ? -1 : 1;
    int filaInicial=(getColor()=='R') ? 6 : 1;
    int diferenciaFila=filaDestino-getFila();
    int diferenciaColumna=columnaDestino-getColumna();
    if(diferenciaColumna==0 && diferenciaFila==direccion && !hayPiezaDestino){
        return true;
    }

    if(diferenciaColumna==0 && getFila()==filaInicial && diferenciaFila==2*direccion && !hayPiezaIntermedia && !hayPiezaDestino){
        return true;
    }

    if((diferenciaColumna==1 || diferenciaColumna==-1) && diferenciaFila==direccion && hayPiezaDestino){
        return true;
    }
    return false;
}