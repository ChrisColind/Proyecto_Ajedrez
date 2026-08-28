cmake_minimum_required(VERSION 3.16)

project(Proyecto_Ajedrez LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Proyecto_Ajedrez main.cpp)

include(GNUInstallDirs)
install(TARGETS Proyecto_Ajedrez
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
