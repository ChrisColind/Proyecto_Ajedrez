#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>

using namespace std;

class Jugador{
private:
    string nombre;
    int partidasJugadas;
    int partidasGanadas;
    int puntaje;

public:
    Jugador(string nombre);

    string getNombre() const;
    int getPartidasJugadas() const;
    int getPartidasGanadas() const;
    int getPuntaje() const;

    void registrarVictoria();
    void registrarDerrota();
};

#endif // JUGADOR_H