#ifndef REINA_H
#define REINA_H

#include "pieza.h"

class Reina : public Pieza{
public:
    Reina(char color, int fila, int columna);

    bool esMovimientoValido(int filaDestino, int columnaDestino, bool hayPiezaDestino, bool hayPiezaIntermedia) override;
};

#endif
