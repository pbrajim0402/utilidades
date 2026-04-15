#include "../utilidades/utilidades.h"
#include "../utilidades/utilidades.c"

// #define MODO_SILENCIOSO
// #define MODO_SIN_AYUDA

#include "../mapa/mapa.h"
#include "../mapa/mapa.c"

int main(int argc, char **argv)
{
  int f, c;
  
  boolean resAnalisis = analizarFicheroMapa("prueba.dat", &f, &c);
  
  printf("El resultado es: ");
  
  if (resAnalisis)
    printf("OK\n");
  else
    printf("ERROR\n");
  
  NUEVALINEA;
  
  printf("Leídas %d filas con un máximo de %d columnas\n", f, c);

  return 0;
}

