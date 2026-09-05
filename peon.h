#ifndef PEON_H
#define PEON_H

#include "pieza.h"

class Peon : public Pieza{
public:
    Peon(char color, int fila, int columna);

    bool esMovimientoValido(int filaDestino, int columnaDestino, bool hayPiezaDestino, bool hayPiezaIntermedia) override;
};

#endif