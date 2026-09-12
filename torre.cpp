#include "torre.h"

Torre::Torre(char color, int fila, int columna)
    : Pieza(color, 'T', fila, columna){
}

bool Torre::esMovimientoValido(int filaDestino, int columnaDestino, bool hayPiezaDestino, bool hayPiezaIntermedia){
    int diferenciaFila=filaDestino-getFila();
    int diferenciaColumna=columnaDestino-getColumna();

    //no puede "moverse" a la misma casilla
    if(diferenciaFila==0 && diferenciaColumna==0){
        return false;
    }

    //la torre solo se mueve en linea recta: misma fila o misma columna
    bool esHorizontal=(diferenciaFila==0);
    bool esVertical=(diferenciaColumna==0);

    if(!esHorizontal && !esVertical){
        return false;
    }

    //no puede saltar sobre otras piezas en el camino
    if(hayPiezaIntermedia){
        return false;
    }

    return true;
}
