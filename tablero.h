#ifndef TABLERO_H
#define TABLERO_H

#include "pieza.h"
/*#include "Rey.h"
#include "Torre.h"
#include "Caballo.h"
#include "Peon.h"
*/

class Tablero{
private:
    Pieza* casillas[8][8];

    //Deja todas las casillas en nullptr antes de colocar las piezas
    void vaciarCasillas();

    //Crea con new las 16 piezas de cada color en su posicion inicial
    void inicializarPosicionInicial();

    //Recorre las 64 casillas y hace delete de cada Pieza que no sea nullptr
    void liberarMemoria();

public:
    Tablero(); //constructor
    ~Tablero(); //destructor

    //Dibuja el tablero en consola
    void imprimir() const;
};

#endif // TABLERO_H