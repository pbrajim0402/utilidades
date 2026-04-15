// ZONA DE IMPORTACIÓN: FICHEROS NECESARIOS A INCLUIR

#include <stdio.h>  // Incluye subprogramas para pedir y mostrar datos.
#include <stdlib.h> // Incluye subprogramas de uso común.
#include <string.h> // Incluye subprogramas para manejar cadenas.
#include <time.h>   // Incluye subprogramas para manejar fecha y hora.

#include "utilidades.c" // Algunos programas muy usados.



// ZONA DE MACROS, CONSTANTES Y VARIABLES GLOBALES: PARA USO GLOBAL.




// ZONA DE PREDECLARACIÓN: CABECERA O PROTOTIPO DE SUBPROGRAMAS

void cargaLCD                (char pixel[25][80]);
void muestraLCD              (char pixel[25][80]);


// SUBPROGRAMA PRINCIPAL: EL S.O. PASA EL CONTROL AQUÍ AL PONER EN MARCHA EL EJECUTABLE.

int main (void) // Devuelve int para informar al S.O. de cómo fue todo.
{
  char pixel[25][80];
  
  // CARGAMOS DATOS DESDE FICHERO.
  cargaLCD(pixel);
  
  // BORRAMOS PANTALLA
  system("clear");
  fflush(stdout);
  
  // PAUSA Y RETARDO ANTES DE MOSTRAR NADA.
  pausa();
  retardoMilisegundos(3000);
  
  // BORRAMOS PANTALLA
  system("clear");
  fflush(stdout);
  
  // MENSAJE ENCIMA DEL LCD
  puts("PANEL LCD...");
  puts("");

  // MOSTRAMOS LCD DESDE LOS CONTENIDOS DE LA MEMORIA.
  muestraLCD(pixel);
  puts("");

  // PAUSA Y RETARDO ANTES DE MOSTRAR NADA.
  pausa();
  retardoMilisegundos(3000);
  
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

void muestraLCD(char pixel[25][80])
{
  int i, j;
  
  for(i=0; i<25; i++)
  {
    for(j=0; j<80; j++) putchar(pixel[i][j]);

    putchar('\n'); // CAMBIO DE LÍNEA.
  }
}
