#include "jugador.h"
#include <fstream>
Jugador::Jugador(string nombre){
    this->nombre=nombre;
    partidasJugadas=0;
    partidasGanadas=0;
    puntaje=0;
}

Jugador::Jugador(string nombre, string contrasena){
    this->nombre=nombre;
    this->contrasena=contrasena;
    partidasJugadas=0;
    partidasGanadas=0;
    puntaje=0;
}

Jugador::Jugador(string nombre, string contrasena, int partidasJugadas, int partidasGanadas, int puntaje){
    this->nombre=nombre;
    this->contrasena=contrasena;
    this->partidasJugadas=partidasJugadas;
    this->partidasGanadas=partidasGanadas;
    this->puntaje=puntaje;
}

bool Jugador::existeArchivo(string nombre){
    ifstream archivo("Jugadores/"+nombre+".txt");
    return archivo.good();
}

string Jugador::getNombre() const{
    return nombre;
}

void Jugador::guardarEnArchivo() const{
    ofstream archivo("Jugadores/"+nombre+".txt");

    archivo<<nombre<<endl;
    archivo<<contrasena<<endl;
    archivo<<partidasJugadas<<endl;
    archivo<<partidasGanadas<<endl;
    archivo<<puntaje<<endl;

    archivo.close();
}

Jugador* Jugador::cargarDesdeArchivo(string nombre){
    ifstream archivo("Jugadores/"+nombre+".txt");

    if(!archivo.good()){
        return nullptr;
    }

    string nombreGuardado;
    string contrasenaGuardada;
    int partidasJugadasGuardadas;
    int partidasGanadasGuardadas;
    int puntajeGuardado;

    getline(archivo,nombreGuardado);
    getline(archivo,contrasenaGuardada);
    archivo>>partidasJugadasGuardadas;
    archivo>>partidasGanadasGuardadas;
    archivo>>puntajeGuardado;

    archivo.close();

    Jugador* jugador=new Jugador(nombreGuardado,contrasenaGuardada,partidasJugadasGuardadas,partidasGanadasGuardadas,puntajeGuardado);

    return jugador;
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

string Jugador::getContrasena() const{
    return contrasena;
}

void Jugador::registrarVictoria(){
    partidasJugadas++;
    partidasGanadas++;
    puntaje=puntaje+10;
}

void Jugador::registrarDerrota(){
    partidasJugadas++;
}