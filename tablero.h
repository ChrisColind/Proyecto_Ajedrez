#ifndef TABLERO_H
#define TABLERO_H

#include <string>
#include "pieza.h"

using namespace std;

class Tablero{
private:
    Pieza* casillas[8][8];

    void vaciarCasillas();
    void inicializarPosicionInicial();
    void liberarMemoria();
    bool hayObstaculoEnTrayectoria(int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino);

public:
    Tablero();
    ~Tablero();

    bool convertirCoordenada(string texto, int &fila, int &columna);
    bool hayPiezaEn(int fila, int columna);
    char colorEnCasilla(int fila, int columna);
    char simboloEnCasilla(int fila, int columna);
    bool movimientoValido(int filaOrigen, int columnaOrigen,int filaDestino, int columnaDestino);
    void moverPieza(int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino);
    void imprimir() const;
};

#endif