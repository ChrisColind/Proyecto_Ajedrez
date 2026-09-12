#ifndef CABALLO_H
#define CABALLO_H

#include "pieza.h"

class Caballo : public Pieza{
public:
    Caballo(char color, int fila, int columna);

    bool esMovimientoValido(int filaDestino, int columnaDestino, bool hayPiezaDestino, bool hayPiezaIntermedia) override;
};

#endif