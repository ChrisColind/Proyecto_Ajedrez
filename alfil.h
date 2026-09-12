#ifndef ALFIL_H
#define ALFIL_H

#include "pieza.h"

class Alfil : public Pieza{
public:
    Alfil(char color, int fila, int columna);

    bool esMovimientoValido(int filaDestino, int columnaDestino, bool hayPiezaDestino, bool hayPiezaIntermedia) override;
};

#endif
