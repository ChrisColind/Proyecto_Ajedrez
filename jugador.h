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
    string contrasena;
public:
    Jugador(string nombre, string contrasena, int partidasJugadas, int partidasGanadas, int puntaje);
    Jugador(string nombre, string contrasena);
    Jugador(string nombre);
    string getContrasena() const;
    string getNombre() const;
    int getPartidasJugadas() const;
    int getPartidasGanadas() const;
    int getPuntaje() const;
    void guardarEnArchivo() const;
    void registrarVictoria();
    void registrarDerrota();
    static Jugador* cargarDesdeArchivo(string nombre);
    static bool existeArchivo(string nombre);
};

#endif // JUGADOR_H