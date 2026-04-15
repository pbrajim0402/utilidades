#include "../utilidades/utilidades.h"
#include "../utilidades/utilidades.c"

// #define MODO_SILENCIOSO
// #define MODO_SIN_AYUDA

#include "../mapa/mapa.h"
#include "../mapa/mapa.c"



int main(int argc, char **argv)
{
  int filas = 10, columnas = 20;
  
  // Declaramos una matriz bidimensional.
  char tablero[filas][columnas];

  // Carga el fichero en su matriz fija
  cargarMapaEstatico("mapa-estatico.dat", filas, columnas, tablero);
  
    // cargarMapaEstatico(MAPA_ARCHIVO_DEFECTO, MAPA_FILS, MAPA_COLS, tablero);

  // Mostramos el mapa usando la función de la misma librería.
  mostrarMapa(filas, columnas, tablero);

  return 0;
}
