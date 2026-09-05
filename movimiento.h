#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

class Movimiento{
private:
    int filaOrigen;
    int columnaOrigen;
    int filaDestino;
    int columnaDestino;

public:
    Movimiento(int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino);
    int getFilaOrigen();
    int getColumnaOrigen();
    int getFilaDestino();
    int getColumnaDestino();
};

#endif