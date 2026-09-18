#ifndef HISTORIAL_H
#define HISTORIAL_H

#include "movimiento.h"

class Historial{
private:
    Movimiento** movimientos;
    int cantidad;
    int capacidad;

public:
    Historial();
    ~Historial();

    void agregarMovimiento(Movimiento* movimiento);
    void mostrarHistorial();
};

#endif // HISTORIAL_H