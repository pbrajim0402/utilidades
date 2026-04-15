// ZONA DE IMPORTACIÓN: FICHEROS NECESARIOS A INCLUIR

#include <stdio.h>  // Incluye subprogramas para pedir y mostrar datos.
#include <stdlib.h> // Incluye subprogramas de uso común.
#include <string.h> // Incluye subprogramas para manejar cadenas.
#include <time.h>   // Incluye subprogramas para manejar fecha y hora.

#include "utilidades.h"



// ZONA DE CÓDIGO: CUERPOS DE LOS SUBPROGRAMAS DECLARADOS ANTES.

void retardoSegundos (int segundos)
{
  int i, j, k;
  
  for (i=0; i<segundos; i++)
    for (j=0; j<10000; j++)
      for (k=0; k<10000; k++)  ;
}



void retardoMilisegundos (int milisegundos)
{
  int i, j, k;
  
  for (i=0; i<milisegundos; i++)
    for (j=0; j<100; j++)
      for (k=0; k<1000; k++)  ;
}



void pausa (void)
{
  char tecla;
  
  printf("Pulse INTRO para continuar...");
  fflush(stdout);
  
  tecla = getchar();
  
  while (tecla != INTRO)
  {
    tecla = getchar();
  }
}



char obtenerCaracterASCII(void)
{
  char letra, valida;
  
  letra = getchar();
  
  if (letra < 128)
    valida = letra; // Devolveremos la letra
  else
    valida = '\0';  // Devolveremos la letra nula.
  
  // VACIAMOS POSIBLES CÓDIGOS EN EL BUFFER.
  //   Se incluye el INTRO EXTRA y una posible escritura de múltiples letras.
  if (letra != INTRO)
  {
    do
    {
      letra = getchar();
    } while (letra != INTRO);
  }

  return valida;
}
