#ifndef REY_H
#define REY_H

#include "pieza.h"

class Rey : public Pieza{
public:
    Rey(char color, int fila, int columna);
    bool esMovimientoValido(int filaDestino, int columnaDestino, bool hayPiezaDestino, bool hayPiezaIntermedia) override;
};

#endif