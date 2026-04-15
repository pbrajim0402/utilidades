#include "../utilidades/utilidades.h"
#include "../utilidades/utilidades.c"

int main(int argc, char **argv)
{
  borrarPantalla();
  
  bajar(3);
  int a = pedirEntero("Dame un entero", 8);
  
  bajar(3);
  indentar(3);
  
  mostrar("Has dado el valor ");
  printf("%d", a);
  mostrar(".\n");

  return 0;
}
