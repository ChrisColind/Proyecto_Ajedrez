#ifndef TABLERO_H
#define TABLERO_H

#include <string>
#include "pieza.h"
#include <fstream>
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
    bool esPromocion(int fila, int columna);
    void promocionarPeon(int fila, int columna);
    bool enroqueValido(char color, bool esCorto);
    void hacerEnroque(char color, bool esCorto);
    void imprimir() const;
    void guardarEnArchivo(ofstream &archivo);
    void cargarDesdeArchivo(ifstream &archivo);
    bool estaEnJaque(char color);
    bool dejaEnJaquePropio(int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino);
};

#endif