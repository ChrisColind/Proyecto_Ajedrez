cmake_minimum_required(VERSION 3.16)

project(Proyecto_Ajedrez LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Proyecto_Ajedrez main.cpp
    pieza.h pieza.cpp
    rey.h rey.cpp
    torre.h torre.cpp
    peon.h peon.cpp
    caballo.h caballo.cpp
    tablero.h tablero.cpp
    jugador.h jugador.cpp
    movimiento.h movimiento.cpp
    historial.h historial.cpp
    gestorpartida.h gestorpartida.cpp
    ranking.h ranking.cpp
    alfil.h alfil.cpp
    reina.h reina.cpp
    jugador.h jugador.cpp)

include(GNUInstallDirs)
install(TARGETS Proyecto_Ajedrez
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
