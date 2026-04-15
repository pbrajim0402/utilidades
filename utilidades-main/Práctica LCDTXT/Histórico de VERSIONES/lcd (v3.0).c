// ZONA DE IMPORTACIÓN: FICHEROS NECESARIOS A INCLUIR

#include <stdio.h>  // Incluye subprogramas para pedir y mostrar datos.
#include <stdlib.h> // Incluye subprogramas de uso común.
#include <string.h> // Incluye subprogramas para manejar cadenas.
#include <time.h>   // Incluye subprogramas para manejar fecha y hora.

#include "utilidades.c" // Algunos programas muy usados.



// ZONA DE MACROS, CONSTANTES Y VARIABLES GLOBALES: PARA USO GLOBAL.

#define ALTO_LCD   25
#define ANCHO_LCD  80

#define ARRIBA     1
#define ABAJO     -1
#define CENTRO     0
#define DERECHA    1
#define IZQUIERDA -1

const int porcentajeCambio = 5; // PROBABILIDAD DE CAMBIO DE DIRECCIÓN.



// ZONA DE PREDECLARACIÓN: CABECERA O PROTOTIPO DE SUBPROGRAMAS

void cargaLCD                (char pixel[ALTO_LCD][ANCHO_LCD]);
void desplaza1PixelAbajo     (char pixel[ALTO_LCD][ANCHO_LCD]);
void desplaza1PixelArriba    (char pixel[ALTO_LCD][ANCHO_LCD]);
void desplaza1PixelDerecha   (char pixel[ALTO_LCD][ANCHO_LCD]);
void desplaza1PixelIzquierda (char pixel[ALTO_LCD][ANCHO_LCD]);
void muestraLCD              (char pixel[ALTO_LCD][ANCHO_LCD]);


// SUBPROGRAMA PRINCIPAL: EL S.O. PASA EL CONTROL AQUÍ AL PONER EN MARCHA EL EJECUTABLE.

int main (void) // Devuelve int para informar al S.O. de cómo fue todo.
{
  int dirHorizontal = IZQUIERDA;
  int dirVertical   = CENTRO;

  int numazar; // Variable para elegir número entre 0 y 99.
  
  // INICIALIZAMOS EL MOTOR DE NÚMEROS ALETATORIOS.
  srand (time(NULL));
  
  char pixel[ALTO_LCD][ANCHO_LCD];
  
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

void cargaLCD(char pixel[ALTO_LCD][ANCHO_LCD])
{
  int i, j, salida;
  char caracter;
  FILE *archivo; // Puntero, apuntador, manejador o conexión a ficheros.
  
  archivo = fopen("lcd.data", "r+"); // Pedimos abrir fichero para lectura.
  
  if (!archivo) // No se pudo abrir por algún motivo y "archivo" vale NULL.
    exit (1);
    
  for(i=0; i<ALTO_LCD; i++)
  {
    for(j=0; j<ANCHO_LCD; j++)
    {
      salida = fscanf(archivo, "%c", &caracter); // Leemos 1 caracter.
      if (salida == -1) exit(2); // Fichero sin todos los caracteres.
      pixel[i][j] = caracter;
    }
    salida = fscanf(archivo, "%c", &caracter); // INTRO DEL FINAL DE LÍNEA.
    if (salida == -1) exit(3); // Fichero sin todos los INTRO's.
  }
  
  fclose(archivo); // Desconectamos del archivo en disco.
}

void desplaza1PixelAbajo (char pixel[ALTO_LCD][ANCHO_LCD])
{
  // Planteamiento trabajando por COLUMNAS en lugar de FILAS para evitar
  // usar un vector de 80 elementos para salvaguardar la última fila.
  
  int i, j, ultimo;  // Ojo, aquí es "ultimo" en VERTICALES.
  char pixelsalvado;
  
  ultimo = ALTO_LCD - 1; // Ahorramos así algunas restas en el bucle.
  
  for(i=0; i<ANCHO_LCD; i++)
  {
    pixelsalvado = pixel[ultimo][i];
    for(j=ultimo; j>0; j--)  pixel[j][i] = pixel[j-1][i];
    pixel[0][i] = pixelsalvado;
  }
}

void desplaza1PixelArriba (char pixel[ALTO_LCD][ANCHO_LCD])
{
  // Planteamiento trabajando por COLUMNAS en lugar de FILAS para evitar
  // usar un vector de 80 elementos para salvaguardar la primera fila.
  
  int i, j, ultimo;  // Ojo, aquí es "ultimo" en VERTICALES.
  char pixelsalvado;
  
  ultimo = ALTO_LCD - 1; // Ahorramos así algunas restas en el bucle.
  
  for(i=0; i<ANCHO_LCD; i++)
  {
    pixelsalvado = pixel[0][i];
    for(j=1; j<ALTO_LCD; j++)  pixel[j-1][i] = pixel[j][i];
    pixel[ultimo][i] = pixelsalvado;
  }
}

void desplaza1PixelDerecha (char pixel[ALTO_LCD][ANCHO_LCD])
{
  int i, j, ultimo;  // Ojo, aquí es "ultimo" en HORIZONTALES.
  char pixelsalvado;
  
  ultimo = ANCHO_LCD - 1; // Ahorramos así algunas restas en el bucle.
  
  for(i=0; i<ALTO_LCD; i++)
  {
    pixelsalvado = pixel[i][ultimo];
    for(j=ultimo; j>0; j--)  pixel[i][j] = pixel[i][j-1];
    pixel[i][0] = pixelsalvado;
  }
}

void desplaza1PixelIzquierda (char pixel[ALTO_LCD][ANCHO_LCD])
{
  int i, j, ultimo;  // Ojo, aquí es "ultimo" en HORIZONTALES.
  char pixelsalvado;
  
  ultimo = ANCHO_LCD - 1; // Ahorramos así algunas restas en el bucle.
  
  for(i=0; i<ALTO_LCD; i++)
  {
    pixelsalvado = pixel[i][0];
    for(j=1; j<ANCHO_LCD; j++)  pixel[i][j-1] = pixel[i][j];
    pixel[i][ultimo] = pixelsalvado;
  }
}

void muestraLCD(char pixel[ALTO_LCD][ANCHO_LCD])
{
  int i, j;
  
  for(i=0; i<ALTO_LCD; i++)
  {
    for(j=0; j<ANCHO_LCD; j++)
      putchar(pixel[i][j]);

    putchar('\n'); // CAMBIO DE LÍNEA.
  }
}
