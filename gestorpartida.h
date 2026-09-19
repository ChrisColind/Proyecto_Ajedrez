#ifndef GESTORPARTIDA_H
#define GESTORPARTIDA_H

#include "tablero.h"
#include "jugador.h"
#include "historial.h"
#include "ranking.h"

class GestorPartida{
private:
    Tablero* tablero;
    Jugador* jugadorRojo;
    Jugador* jugadorAzul;
    Historial* historial;
    char turno;

    void cambiarTurno();
    bool esJaquemate(char color);
    Jugador* login(string colorEtiqueta);
    void jugarTurnos();
    void guardarPartida();
    Jugador* crearUsuario(string colorEtiqueta);
    Jugador* obtenerJugador(string colorEtiqueta);
    void mostrarRanking();


public:
    GestorPartida();
    ~GestorPartida();

    void menu();
    void iniciarPartida();
    void cargarPartida();
};

#endif