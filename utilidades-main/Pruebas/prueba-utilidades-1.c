#include "utilidades/utilidades.h"
#include "utilidades/utilidades.c"



int main(int argc, char **argv)
{
  limpiarPantalla();

  for(int i=0; i<24; i++)
  {
    mostrar("123456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789|");
  }
  
  NL;
  
  pausa();
  
  return 0;
  
  posicionar(0,8);
  escribir("Hola");
  fflush(stdout);
  
  esperarSegundos(1);
  
  pausaEstandar(0, 7);
  
  // saltar(4);
  tabular(4);
  printf("Hola\n");
  
  nuevaLinea();
  
  char letra = pedirLetraSeleccion("¿Desea continuar?", 10, TRUE, "abc", TRUE);
  
  retrasoMilisegundos(2000);
  // esperarSegundos(2);
  
  NL;
  
  printf("  Te confirmo, has dado la letra '%c'.\n", letra);

  codigoError = 0;
  return codigoError;
}
