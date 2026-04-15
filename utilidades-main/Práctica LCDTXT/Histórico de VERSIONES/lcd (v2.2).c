// ZONA DE IMPORTACIÓN: FICHEROS NECESARIOS A INCLUIR

#include <stdio.h>  // Incluye subprogramas para pedir y mostrar datos.
#include <stdlib.h> // Incluye subprogramas de uso común.
#include <string.h> // Incluye subprogramas para manejar cadenas.
#include <time.h>   // Incluye subprogramas para manejar fecha y hora.

#include "utilidades.c" // Algunos programas muy usados.



// ZONA DE MACROS, CONSTANTES Y VARIABLES GLOBALES: PARA USO GLOBAL.

#define ARRIBA     1
#define ABAJO     -1
#define CENTRO     0
#define DERECHA    1
#define IZQUIERDA -1

const int porcentajeCambio = 5; // PROBABILIDAD DE CAMBIO DE DIRECCIÓN.



// ZONA DE PREDECLARACIÓN: CABECERA O PROTOTIPO DE SUBPROGRAMAS

void cargaLCD                (char pixel[25][80]);
void desplaza1PixelAbajo     (char pixel[25][80]);
void desplaza1PixelArriba    (char pixel[25][80]);
void desplaza1PixelDerecha   (char pixel[25][80]);
void desplaza1PixelIzquierda (char pixel[25][80]);
void muestraLCD              (char pixel[25][80]);


// SUBPROGRAMA PRINCIPAL: EL S.O. PASA EL CONTROL AQUÍ AL PONER EN MARCHA EL EJECUTABLE.

int main (void) // Devuelve int para informar al S.O. de cómo fue todo.
{
  int dirHorizontal = IZQUIERDA;
  int dirVertical   = CENTRO;

  int numazar; // Variable para elegir número entre 0 y 99.
  
  // INICIALIZAMOS EL MOTOR DE NÚMEROS ALETATORIOS.
  srand (time(NULL));
  
  char pixel[25][80];
  
  cargaLCD(pixel);
  
  for(;;)
  {
    // BORRAMOS FOTOGRAMA
    system("clear");
    fflush(stdout);
    
    // MENSAJE ENCIMA DEL LCD
    puts("PANEL LCD...");
    puts("");

    // TOMAMOS UN NÚMERO AL AZAR
    numazar = ((int) rand()%101); // Número entre 0 y 100.
    
    // DECIDIMOS SI ES SUFICIENTE PROBABILIDAD PARA CAMBIAR DE DIRECCIÓN.
    if (numazar < porcentajeCambio)
    {
      dirHorizontal = ((int) rand()%3) - 1; // Dirección H también al azar.
      dirVertical   = ((int) rand()%3) - 1; // Dirección V también al azar.
    }

    // HACEMOS SCROLL PARA LAS DIRECCIONES ADECUADAS.
    switch (dirHorizontal)
    {
      case IZQUIERDA:
        // DESPLAZAMOS PÍXELES A LA IZQUIERDA.
        desplaza1PixelIzquierda (pixel);
      break;

      case DERECHA:
        // DESPLAZAMOS PÍXELES A LA IZQUIERDA.
        desplaza1PixelDerecha (pixel);
      break;
    }
      
    switch (dirVertical)
    {
      case ARRIBA:
        // DESPLAZAMOS PÍXELES HACIA ARRIBA.
        desplaza1PixelArriba (pixel);
      break;
      
      case ABAJO:
        // DESPLAZAMOS PÍXELES HACIA ABAJO.
        desplaza1PixelAbajo (pixel);
      break;
    }
    
    // MOSTRAMOS LCD
    muestraLCD(pixel);

    // RETARDO
    retardoMilisegundos(200);
  }
  
  codigoError = 0; 
  return codigoError; // Devolvemos 0 (SIN ERRORES) como punto natural de salida.
}



// ZONA DE CÓDIGO: CUERPOS DE LOS SUBPROGRAMAS DECLARADOS ANTES.

void cargaLCD(char pixel[25][80])
{
  int i, j, salida;
  char caracter;
  FILE *archivo;
  
  archivo = fopen("lcd.data", "r+");
  
  if (!archivo)
    exit (1);
    
  for(i=0; i<25; i++)
  {
    for(j=0; j<80; j++)
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

void desplaza1PixelAbajo (char pixel[25][80])
{
  // Planteamiento trabajando por COLUMNAS en lugar de FILAS para evitar
  // usar un vector de 80 elementos para salvaguardar la última fila.
  
  int i, j;
  char pixelsalvado;
  
  for(i=0; i<80; i++)
  {
    pixelsalvado = pixel[24][i];
    for(j=24; j>0; j--)
      pixel[j][i] = pixel[j-1][i];
    pixel[0][i] = pixelsalvado;
  }
}

void desplaza1PixelArriba (char pixel[25][80])
{
  // Planteamiento trabajando por COLUMNAS en lugar de FILAS para evitar
  // usar un vector de 80 elementos para salvaguardar la primera fila.
  
  int i, j;
  char pixelsalvado;
  
  for(i=0; i<80; i++)
  {
    pixelsalvado = pixel[0][i];
    for(j=1; j<25; j++)
      pixel[j-1][i] = pixel[j][i];
    pixel[24][i] = pixelsalvado;
  }
}

void desplaza1PixelDerecha (char pixel[25][80])
{
  int i, j;
  char pixelsalvado;
  
  for(i=0; i<25; i++)
  {
    pixelsalvado = pixel[i][79];
    for(j=79; j>0; j--)
      pixel[i][j] = pixel[i][j-1];
    pixel[i][0] = pixelsalvado;
  }
}

void desplaza1PixelIzquierda (char pixel[25][80])
{
  int i, j;
  char pixelsalvado;
  
  for(i=0; i<25; i++)
  {
    pixelsalvado = pixel[i][0];
    for(j=1; j<80; j++)
      pixel[i][j-1] = pixel[i][j];
    pixel[i][79] = pixelsalvado;
  }
}

void muestraLCD(char pixel[25][80])
{
  int i, j;
  
  for(i=0; i<25; i++)
  {
    for(j=0; j<80; j++) putchar(pixel[i][j]);

    putchar('\n'); // CAMBIO DE LÍNEA.
  }
}
