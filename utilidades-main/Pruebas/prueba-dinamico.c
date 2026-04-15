#include "../utilidades/utilidades.c"
#include "../utilidades/utilidades.h"

#define MODO_SILENCIOSO
#define MODO_SIN_AYUDA

#include "../mapa/mapa.c"
#include "../mapa/mapa.h"



int main(int argc, char **argv)
{
  boolean cargaCorrecta;

  // Cargamos el mapa (la librería analiza, mide y reserva memoria).
  
  cargaCorrecta = cargarMapa("mapa-dinamico.dat");
  
  if (!cargaCorrecta)
  {
      printf("ERROR: El mapa no es válido o no existe.\n");
      exit(1);
  }
  else
  {
    printf("Se ha cargado un mapa de %d filas x %d columnas.\n", MAPA_NFILS, MAPA_NCOLS);
    
    // Generamos mediante MACRO la matriz.
    GENERAR_MAPA(tablero);

    // Mostramos el mapa con la función proporcionada por la librería.
    mostrarMapa(MAPA_NFILS, MAPA_NCOLS, tablero);
    
    // Habiendo usado el mapa, liberamos su memoria.
    liberarMapa();
  }

  return 0;
}
