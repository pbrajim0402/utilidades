// ZONA DE IMPORTACIÓN: FICHEROS NECESARIOS A INCLUIR

#include "../utilidades/utilidades.h"
#include "../utilidades/utilidades.c"

#define MODO_SILENCIOSO
#define MODO_SIN_AYUDA

// Comentar la siguiente línea si queremos rotación variable de imagen.
#define MODO_FIJO

#include "../mapa/mapa.h"
#include "../mapa/mapa.c"



// ZONA DE MACROS, CONSTANTES Y VARIABLES GLOBALES: PARA USO GLOBAL.

#define LCD_NFILS   24
#define LCD_NCOLS   80

#define ARCHIVO_PANTALLA_DEFECTO  "lcd.data"
#define ARCHIVO_PANTALLA_EJEMPLO1 "MAPAS/lcd.dat1"
#define ARCHIVO_PANTALLA_EJEMPLO2 "MAPAS/lcd.dat2"
#define ARCHIVO_PANTALLA_EJEMPLO3 "MAPAS/lcd.dat3"
#define ARCHIVO_PANTALLA_EJEMPLO4 "MAPAS/lcd.dat4"

#define ARCHIVO_PANTALLA_TILE1 "MAPAS/ALTERNATIVOS/tile-cebra.txt"
#define ARCHIVO_PANTALLA_TILE2 "MAPAS/ALTERNATIVOS/tile-hojas.txt"
#define ARCHIVO_PANTALLA_TILE3 "MAPAS/ALTERNATIVOS/tile-jirafa.txt"
#define ARCHIVO_PANTALLA_TILE4 "MAPAS/ALTERNATIVOS/tile-ladrillos.txt"
#define ARCHIVO_PANTALLA_TILE5 "MAPAS/ALTERNATIVOS/tile-piscina.txt"
#define ARCHIVO_PANTALLA_TILE6 "MAPAS/ALTERNATIVOS/tile-space.txt"

typedef enum
{
  DIR_H_IZQUIERDA = -1,
  DIR_H_CENTRO    =  0,
  DIR_H_DERECHA   =  1,
  
  DIR_H_TOTAL     =  3
  
} TDIRH;

typedef enum
{
  DIR_V_ARRIBA    = -1,
  DIR_V_CENTRO    =  0,
  DIR_V_ABAJO     =  1,

  DIR_V_TOTAL     =  3
  
} TDIRV;

const int porMilDeCambio = 250; // PROBABILIDAD DE CAMBIO DE DIRECCIÓN RESPECTO A 100.



// ZONA DE PREDECLARACIÓN: CABECERA O PROTOTIPO DE SUBPROGRAMAS

void desplazarUnPixelAbajo     (int alto, int ancho, char pixel[alto][ancho]);
void desplazarUnPixelArriba    (int alto, int ancho, char pixel[alto][ancho]);
void desplazarUnPixelDerecha   (int alto, int ancho, char pixel[alto][ancho]);
void desplazarUnPixelIzquierda (int alto, int ancho, char pixel[alto][ancho]);



// SUBPROGRAMA PRINCIPAL: EL S.O. PASA EL CONTROL AQUÍ AL PONER EN MARCHA EL EJECUTABLE.

int main (void) // Devuelve int para informar al S.O. de cómo fue todo.
{
  const int LCD_ALTO  = LCD_NFILS;
  const int LCD_ANCHO = LCD_NCOLS;
  
  int dirHorizontal;   // Valores: -1, 0, 1.
  int dirVertical  ;   // Valores: -1, 0, 1.

  // FIJAMOS EL DESPLAZAMIENTO QUE QUERAMOS USAR EN HORIZONTAL (MODO FIJO).
  dirHorizontal = DIR_H_IZQUIERDA;

    // dirHorizontal = DIR_H_IZQUIERDA;
    // dirHorizontal = DIR_H_CENTRO;
    // dirHorizontal = DIR_H_DERECHA;

  // FIJAMOS EL DESPLAZAMIENTO QUE QUERAMOS USAR EN VERTICAL (MODO FIJO).
  dirVertical   = DIR_V_CENTRO;
  
    // dirVertical   = DIR_V_ARRIBA;
    // dirVertical   = DIR_V_CENTRO;
    // dirVertical   = DIR_V_ABAJO;

  // Creamos la zona de memoria para la matriz de píxeles.
  char pixel[LCD_ALTO][LCD_ANCHO];
  
  // Cargamos la pantalla desde el disco, haciendo uso de la librería "mapa.c".
  cargarMapaEstatico(ARCHIVO_PANTALLA_DEFECTO, LCD_ALTO, LCD_ANCHO, pixel);
  
    // cargarMapaEstatico(ARCHIVO_PANTALLA_DEFECTO, LCD_ALTO, LCD_ANCHO, pixel);
    // cargarMapaEstatico(ARCHIVO_PANTALLA_EJEMPLO3, LCD_ALTO, LCD_ANCHO, pixel);
    // cargarMapaEstatico(ARCHIVO_PANTALLA_TILE3, LCD_ALTO, LCD_ANCHO, pixel);
  
  // INICIALIZAMOS EL MOTOR DE NÚMEROS ALETATORIOS.
  iniciaAleatorizador();
  
  for(;;)
  {
    // BORRAMOS FOTOGRAMA
    system(BORRAR);
      // fflush(stdout);
    
    // MENSAJE ENCIMA DEL LCD
    mostrar("PANEL LCD...\n");
    LINEAENBLANCO;

    #ifndef MODO_FIJO

    // TOMAMOS UN NÚMERO AL AZAR ENTRE 0 Y 100.
    int numazar = generaAleatorioEntero(1001);
    
    // DECIDIMOS SI ES SUFICIENTE PROBABILIDAD PARA CAMBIAR DE DIRECCIÓN.
    if (numazar < porMilDeCambio)
    {
      // Dirección H al azar.
      dirHorizontal = generaAleatorioEntero(DIR_H_TOTAL) - 1;
      
      // Dirección V al azar.
      dirVertical   = generaAleatorioEntero(DIR_V_TOTAL) - 1;
      
      // Combinaciones: 8 direcciones + SIN MOVIMIENTO.
    }
    
    #endif

    // HACEMOS SCROLL PARA LAS DIRECCIONES ADECUADAS.
    switch (dirHorizontal)
    {
      case DIR_H_IZQUIERDA:
        // DESPLAZAMOS "PÍXELES" A LA IZQUIERDA.
        desplazarUnPixelIzquierda (LCD_ALTO, LCD_ANCHO, pixel);
      break;

      case DIR_H_DERECHA:
        // DESPLAZAMOS "PÍXELES" A LA IZQUIERDA.
        desplazarUnPixelDerecha (LCD_ALTO, LCD_ANCHO, pixel);
      break;
    }
      
    switch (dirVertical)
    {
      case DIR_V_ARRIBA:
        // DESPLAZAMOS "PÍXELES" HACIA ARRIBA.
        desplazarUnPixelArriba (LCD_ALTO, LCD_ANCHO, pixel);
      break;
      
      case DIR_V_ABAJO:
        // DESPLAZAMOS "PÍXELES" HACIA ABAJO.
        desplazarUnPixelAbajo (LCD_ALTO, LCD_ANCHO, pixel);
      break;
    }
    
    // MOSTRAMOS el LCD
    mostrarMapa(LCD_ALTO, LCD_ANCHO, pixel);

    // RETARDO
    retrasoMilisegundos(100);
  }
  
  codigoError = 0; 
  return codigoError; // Devolvemos 0 (SIN ERRORES) como punto natural de salida.
}



// ZONA DE CÓDIGO: CUERPOS DE LOS SUBPROGRAMAS DECLARADOS ANTES.

void desplazarUnPixelAbajo (int alto, int ancho, char pixel[alto][ancho])
{
  // RESÚMEN:
  //   El de abajo de cada columna se salva.
  //   Todos los demás en la columna (menos el último) pasan uno abajo.
  //   Se coloca el dato salvado en el primer elemento de la columna.
  
  // Funcionamos recorriendo columnas en lugar de filas, para evitar tener
  // que usar un vector (una fila más) para salvar la fila que sale.
  
  int i, j, ultimo;  // Ojo, aquí es "ultimo" en VERTICALES.
  char pixelsalvado;
  
  ultimo = alto - 1; // Ahorramos así algunas restas en el bucle.
  
  for(i=0; i<ancho ; i++)
  {
    pixelsalvado = pixel[ultimo][i];
    
    for(j=ultimo; j>0 ; j--)
      pixel[j][i] = pixel[j-1][i];

    pixel[0][i] = pixelsalvado;
  }
}


void desplazarUnPixelArriba (int alto, int ancho, char pixel[alto][ancho])
{
  // RESÚMEN:
  //   El de arriba de cada columna se salva.
  //   Todos los demás en la fila pasan uno arriba.
  //   Se coloca el dato salvado en el último elemento de la columna.
  
  // Funcionamos recorriendo columnas en lugar de filas, para evitar tener
  // que usar un vector (una fila más) para salvar la fila que sale.
  
  int i, j, ultimo;  // Ojo, aquí es "ultimo" en VERTICALES.
  char pixelsalvado;
  
  ultimo = alto - 1; // Ahorramos así algunas restas en el bucle.
  
  for(i=0; i<ancho ; i++)
  {
    pixelsalvado = pixel[0][i];
    
    for(j=1; j<alto ; j++)
      pixel[j-1][i] = pixel[j][i];
    
    pixel[ultimo][i] = pixelsalvado;
  }
}


void desplazarUnPixelDerecha (int alto, int ancho, char pixel[alto][ancho])
{
  // RESÚMEN:
  //   El de la derecha de cada fila se salva.
  //   Todos los demás en la fila (menos el último) pasan uno a la derecha.
  //   Se coloca el dato salvado en el primer elemento de la fila.
  
  int i, j, ultimo;  // Ojo, aquí es "ultimo" en HORIZONTALES.
  char pixelsalvado;
  
  ultimo = ancho - 1; // Ahorramos así algunas restas en el bucle.
  
  for(i=0; i<alto ; i++)
  {
    pixelsalvado = pixel[i][ultimo];
    
    for(j=ultimo; j>0 ; j--)
      pixel[i][j] = pixel[i][j-1];
      
    pixel[i][0] = pixelsalvado;
  }
}


void desplazarUnPixelIzquierda (int alto, int ancho, char pixel[alto][ancho])
{
  // RESÚMEN:
  //   El de la izquierda de cada fila se salva.
  //   Todos los demás en la fila pasan uno a la izquierda.
  //   Se coloca el dato salvado en el último elemento de la fila.
  
  int i, j, ultimo;  // Ojo, aquí es "ultimo" en HORIZONTALES.
  char pixelsalvado;
  
  ultimo = ancho - 1; // Ahorramos así algunas restas en el bucle.
  
  for(i=0; i<alto; i++)
  {
    pixelsalvado = pixel[i][0];
    
    for(j=1; j<ancho ; j++)
      pixel[i][j-1] = pixel[i][j];
    
    pixel[i][ultimo] = pixelsalvado;
  }
}
