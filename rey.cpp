#include "rey.h"

Rey::Rey(char color, int fila, int columna): Pieza(color, 'K', fila, columna){
}

bool Rey::esMovimientoValido(int filaDestino, int columnaDestino,bool hayPiezaDestino, bool hayPiezaIntermedia){

    int diferenciaFila=filaDestino-getFila();
    int diferenciaColumna=columnaDestino-getColumna();

    if(diferenciaFila==0 && diferenciaColumna==0){
        return false;
    }

    bool filaValida=(diferenciaFila>=-1 && diferenciaFila<=1);
    bool columnaValida=(diferenciaColumna>=-1 && diferenciaColumna<=1);

    return filaValida && columnaValida;
}