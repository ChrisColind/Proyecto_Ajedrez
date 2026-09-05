#include "movimiento.h"

Movimiento::Movimiento(int filaOrigen,int columnaOrigen,int filaDestino,int columnaDestino){
    this->filaOrigen=filaOrigen;
    this->columnaOrigen=columnaOrigen;
    this->filaDestino=filaDestino;
    this->columnaDestino=columnaDestino;
}

int Movimiento::getFilaOrigen(){
    return filaOrigen;
}

int Movimiento::getColumnaOrigen(){
    return columnaOrigen;
}

int Movimiento::getFilaDestino(){
    return filaDestino;
}

int Movimiento::getColumnaDestino(){
    return columnaDestino;
}