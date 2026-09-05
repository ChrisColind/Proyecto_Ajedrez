#include "pieza.h"

Pieza::Pieza(char color, char simbolo, int fila, int columna){
    this->color=color;
    this->simbolo=simbolo;
    this->fila=fila;
    this->columna=columna;
}

Pieza::~Pieza(){

}

char Pieza::getColor() const{
    return color;
}

char Pieza::getSimbolo() const{
    return simbolo;
}

int Pieza::getFila() const{
    return fila;
}

int Pieza::getColumna() const{
    return columna;
}

void Pieza::setPosicion(int fila, int columna){
    this->fila=fila;
    this->columna=columna;
}

bool Pieza::esMovimientoValido(int filaDestino, int columnaDestino, bool hayPiezaDestino, bool hayPiezaIntermedia){
    return false;
}