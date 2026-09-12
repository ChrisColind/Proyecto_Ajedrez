#include "jugador.h"

Jugador::Jugador(string nombre){
    this->nombre=nombre;
    partidasJugadas=0;
    partidasGanadas=0;
    puntaje=0;
}

string Jugador::getNombre() const{
    return nombre;
}

int Jugador::getPartidasJugadas() const{
    return partidasJugadas;
}

int Jugador::getPartidasGanadas() const{
    return partidasGanadas;
}

int Jugador::getPuntaje() const{
    return puntaje;
}

void Jugador::registrarVictoria(){
    partidasJugadas++;
    partidasGanadas++;
    puntaje=puntaje+10;
}

void Jugador::registrarDerrota(){
    partidasJugadas++;
}