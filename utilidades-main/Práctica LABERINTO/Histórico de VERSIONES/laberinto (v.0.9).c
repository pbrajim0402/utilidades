// ZONA DE IMPORTACIÓN: FICHEROS NECESARIOS A INCLUIR

#include <stdio.h>  // Incluye subprogramas para pedir y mostrar datos.
#include <stdlib.h> // Incluye subprogramas de uso común.
#include <string.h> // Incluye subprogramas para manejar cadenas.
#include <time.h>   // Incluye subprogramas para manejar fecha y hora.

#include "utilidades.c" // Algunos programas y datos muy usados.



// ZONA DE MACROS, CONSTANTES Y VARIABLES GLOBALES: PARA USO GLOBAL.

#define ALTO_MAPA 25
#define ANCHO_MAPA 80



// ZONA DE PREDECLARACIÓN: CABECERA O PROTOTIPO DE SUBPROGRAMAS

void cargaMAPA   (char pixel[ALTO_MAPA][ANCHO_MAPA]);
void muestraMAPA (char pixel[ALTO_MAPA][ANCHO_MAPA]);



// SUBPROGRAMA PRINCIPAL: EL S.O. PASA EL CONTROL AQUÍ AL PONER EN MARCHA EL EJECUTABLE.

int main (void) // Devuelve int para informar al S.O. de cómo fue todo.
{
  char mapa[25][80]; // Memoria para el mapa.
  
  int tecla; // Para la elección del usuario (UNICODE).
  
  int posx = 10, posy = 10; // Registro de la posición del muñeco.
    
  // POSY=0 y POSX=0 es la esquina superior izquierda.
  
  int ultimay = ALTO_MAPA-1, ultimax = ANCHO_MAPA-1;

  // CUIDADO: Las posiciones válidas son 0 a 79 en H y 0 a 24 en V.
  
  cargaMAPA(mapa);
  
  while(TRUE)
  {
    // BORRAMOS FOTOGRAMA
    system("clear");
    fflush(stdout);
    
    // MENSAJE ENCIMA DEL LCD
    puts("LABERINTO ...");
    puts("");

    // COLOCAMOS EL MUÑECO EN EL MAPA EN LA POSICIÓN ACTUAL.
    mapa[posy][posx] = '@'; // Sí, esto es el muñeco.

    // MOSTRAMOS LCD DESDE LOS CONTENIDOS DE LA MEMORIA.
    muestraMAPA(mapa);
    
    // PEDIMOS ELECCIÓN AL USUARIO.
    
    puts("");
    printf("  Elige acción (N/S/E/O/Q): ");
    fflush(stdout);
    
    tecla = obtenerCaracterASCII();
    
    tecla = toupper(tecla); // Convertimos a mayúsculas.
    
    // DECIDIMOS ACCIÓN SEGÚN LA ELECCIÓN DEL USUARIO.
    switch(tecla)
    {
      case 'N': // NORTE, arriba.
      if (posy > 0)
      {
        mapa[posy][posx] = ' '; // Limpiamos posición actual del mapa.
        posy = posy - 1;
      }
      break;
      
      case 'S': // SUR, abajo.
      if (posy < ultimay)
      {
        mapa[posy][posx] = ' '; // Limpiamos posición actual del mapa.
        posy = posy + 1;
      }
      break;
      
      case 'E': // ESTE, a la derecha.
      if (posx < ultimax)
      {
        mapa[posy][posx] = ' '; // Limpiamos posición actual del mapa.
        posx = posx + 1;
      }
      break;
      
      case 'O': // OESTE, a la izquierda.
      if (posx > 0)
      {
        mapa[posy][posx] = ' '; // Limpiamos posición actual del mapa.
        posx = posx - 1;
      }
      break;
      
      // NO HACER NADA, ni mensaje de opción inválida.
      case INTRO:
      case 'Q':   // Tampoco para salir, lo controlamos más adelante.
      break;
      
      default: // DAR UN MENSAJE DE ERROR.
        puts("");
        puts("");
        printf("  OPCIÓN NO VÁLIDA...\n");
    }

    if (tecla == 'Q') break; // Terminamos bucle y salimos.

    // RETARDO
    retardoMilisegundos(1000);
  }
  
  puts("");
  puts("Terminó la ejecución del programa.");
  puts("");
  pausa();
  
  codigoError = 0; 
  return codigoError; // Devolvemos 0 (SIN ERRORES) como punto natural de salida.
}



// ZONA DE CÓDIGO: CUERPOS DE LOS SUBPROGRAMAS DECLARADOS ANTES.

void cargaMAPA(char pixel[ALTO_MAPA][ANCHO_MAPA])
{
  int i, j, salida;
  char caracter;
  FILE *archivo;
  
  archivo = fopen("mapa.dat", "r+");
  
  if (!archivo)
    exit (1);
    
  for(i=0; i<ALTO_MAPA; i++)
  {
    for(j=0; j<ANCHO_MAPA; j++)
    {
      salida = fscanf(archivo, "%c", &caracter);
      if (salida == -1) exit(2);
      pixel[i][j] = caracter;
    }
    salida = fscanf(archivo, "%c", &caracter); // INTRO DEL FINAL DE LÍNEA.
    if (salida == -1) exit(3);
  }
  
  fclose(archivo);
}

void muestraMAPA(char pixel[ALTO_MAPA][ANCHO_MAPA])
{
  int i, j;
  
  for(i=0; i<ALTO_MAPA; i++)
  {
    for(j=0; j<ANCHO_MAPA; j++) putchar(pixel[i][j]);

    putchar('\n'); // CAMBIO DE LÍNEA.
  }
}
