#ifndef RANKING_H
#define RANKING_H

#include "jugador.h"

class Ranking{
private:
    Jugador** jugadores;
    int cantidad;
    int capacidad;

public:
    Ranking();
    ~Ranking();

    void agregarJugador(Jugador* jugador);
    void ordenarPorPuntaje();
    void mostrarRanking();
};

#endif // RANKING_H