#include "gestorpartida.h"

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

int main(){

#ifdef _WIN32
    _mkdir("Jugadores");
    _mkdir("Partidas");
#else
    mkdir("Jugadores", 0777);
    mkdir("Partidas", 0777);
#endif

    GestorPartida partida;
    partida.menu();

    return 0;
}