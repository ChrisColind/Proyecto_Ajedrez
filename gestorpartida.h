#ifndef GESTORPARTIDA_H
#define GESTORPARTIDA_H

#include "tablero.h"

class GestorPartida{
private:
    Tablero* tablero;
    char turno;

    void cambiarTurno();
    bool verificarGanador(char color);

public:
    GestorPartida();
    ~GestorPartida();

    void menu();
    void iniciarPartida();
};

#endif