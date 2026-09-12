#ifndef GESTORPARTIDA_H
#define GESTORPARTIDA_H

#include "tablero.h"
#include "jugador.h"

class GestorPartida{
private:
    Tablero* tablero;
    Jugador* jugadorRojo;
    Jugador* jugadorAzul;
    char turno;

    void cambiarTurno();
    bool verificarGanador(char color);

public:
    GestorPartida();
    ~GestorPartida();

    void menu();
    void iniciarPartida();
    void mostrarAyuda();
};

#endif