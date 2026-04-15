////////////////////////////////////////////////////////////////////////////////
//
// PROTECTOR PARA NO DECLARAR DOS VECES POR ERROR.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UTILIDADES_H
#define UTILIDADES_H



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// ZONA DE IMPORTACIÓN: FICHEROS NECESARIOS A INCLUIR
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// #define SO_WINDOWS
// #define SO_LINUX

#include <stdio.h>        // Incluye subprogramas para pedir y mostrar datos.
#include <stdlib.h>       // Incluye subprogramas de uso común.
#include <string.h>       // Incluye subprogramas para manejar cadenas.
#include <time.h>         // Incluye subprogramas para manejar fecha y hora. nanosleep().
#include <ctype.h>        // Incluye subprogramas para textos: toupper() ó isdigit().
#include <stdbool.h>      // Incluye tipo "bool" y constantes "true" y "false".

#ifdef SO_WINDOWS
  #include <windows.h>    // Biblioteca estándar general de M$ Windows.
#else
  #include <unistd.h>     // Incluye gestión subprocesos/archivos en UN*X/Linux. sleep()/usleep().
#endif



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// ZONA DE MACROS, CONSTANTES Y VARIABLES GLOBALES: PARA USO GLOBAL.
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

typedef enum
{
  TECLA_NULA      = 0,
  TECLA_ARRIBA    = 1,    // Tecla de flecha arriba.
  TECLA_ABAJO     = 2,    // Tecla de flecha abajo.
  TECLA_IZQUIERDA = 3,    // Tecla de flecha izquierda.
  TECLA_DERECHA   = 4,    // Tecla de flecha derecha.
  TECLA_BORRAR    = 8,    // Backspace en Windows
  TECLA_TAB       = 9,    // Tecla de tabulador.
  TECLA_ENTER     = 10,   // Tecla INTRO/ENTER en Windows.
  TECLA_ESCAPE    = 27,   // Tecla de ESCAPE.
  TECLA_ESPACIO   = 32,   // Tecla de barra espaciadora.
  TECLA_RETROCESO = 127  // Backspace en Linux.

} TECLAS_ESPECIALES;

#define TRUE  1 // Cada vez que aparezca TRUE en el código, se sustituye
#define FALSE 0 // por 1, siempre previamente a compilar el ejecutable.

#define LINEAENBLANCO printf("\n")
#define NUEVALINEA printf("\n")

#define SI 'S'
#define NO 'N'

#define ENTER  '\n'     // Código ASCII 10 de NUEVA LÍNEA (NEW LINE).
#define INTRO  '\n'     // Código ASCII 10 de NUEVA LÍNEA (NEW LINE).
#define NULO   '\0'     // Código ASCII  0 de CARACTER NULO.
#define ESCAPE '\x1B'   // Código ASCII 27 de NUEVA LÍNEA (NEW LINE).

#define ASCII_NL '\n'   // Código ASCII 10 de NUEVA LÍNEA (NEW LINE).
#define ASCII_CR '\r'   // Código ASCII 13 de RETORNO DE CARRO (CARRIAGE RETURN)

  // HACER: ENTER EN WINDOWS ES 13 + 10, EN MAC ES 13, EN UN*X/LINUX ES 10.

// #define MSJxERROR "¡VALOR NO VÁLIDO!"

extern char MSJxERROR[];
extern char MSJxPAUSA[];

#ifdef SO_WINDOWS
  #define BORRAR "cls"
#else
  #define BORRAR "clear"
#endif

typedef int boolean; // No existe tipo "boolean" en C. Lo "creamos".

// const float PI = 3.14159; // Así nos creamos una CONSTANTE GLOBAL.

extern int codigoError; // VARIABLE GLOBAL: Visible por todos los subprogramas.



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// ZONA DE PREDECLARACIÓN: CABECERA O PROTOTIPO DE SUBPROGRAMAS
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void    vaciarBuffer              (void);

void    esperarINTRO              (void);
void    descartarEntrada          (void);

void    borrarPantalla            (void);
void    limpiarPantalla           (void);

void    bajar                     (int nlineas);
void    abajo                     (int nfils);
void    saltar                    (int nfils);
void    desplazarFils             (int nfils);
void    desplazarV                (int nfils);
void    desplazarY                (int nfils);

void    indentar                  (int ncolumnas);
void    derecha                   (int ncols);
void    tabular                   (int ncols);
void    desplazarCols             (int ncols);
void    desplazarX                (int ncols);
void    desplazarH                (int ncols);

void    posicionar                (int nfils, int ncols);
void    desplazar                 (int nfils, int ncols);
void    desplazarXY               (int nfils, int ncols);

void    retardoSegundos           (int segundosmax);
void    retardoMilisegundos       (int milisegundosmax);
void    retrasoMilisegundos       (int milisegundos);
void    esperarSegundos           (int segundos);
void    esperarMilisegundos       (int milisegundos);

void    pausa                     (void);
void    pausaEstandar             (int nfils, int ncols);
void    pausaGenerica             (char msjtxt[], int nfils, int ncols, boolean nuevalinea);

void    separar                   (void);
void    nuevaLinea                (void);

void    texto                     (char msjtxt[]);
void    mostrar                   (char msjtxt[]);
void    mostrar_x_y               (char msjtxt[], int nfils, int ncols);
void    escribir                  (char msjtxt[]);
void    escribir_x_y              (char msjtxt[], int nfils, int ncols);
void    imprimir                  (char msjtxt[]);
void    imprimir_x_y              (char msjtxt[], int nfils, int ncols);
void    mensaje                   (char msjtxt[], int nfils, int ncols);
void    mensaje_x_y               (char msjtxt[], int nfils, int ncols, boolean nuevalinea);

void    iniciaAleatorizador       (void);
int     generaAleatorioEntero     (int limite);

int     obtenerEntero             (void);
char    obtenerLetra              (void);   // Sólo ASCII VÁLIDO.
char    obtenerCaracterASCII      (void);
int     obtenerTeclaInteractiva   (void);


int     pedirEntero               (char msjtxt[], int ncols);
int     pedirEnteroPositivo       (char msjtxt[], int ncols, boolean mostrarerror);
int     pedirEnteroIntervalo      (char msjtxt[], int ncols, boolean mostrarerror, int min, int max);
int     pedirLetra                (char msjtxt[], int ncols, boolean mostrarerror, char letra);
int     pedirConfirmacion         (char msjtxt[], int ncols, boolean mostrarerror);
int     pedirLetraSeleccion       (char msjtxt[], int ncols, boolean mostrarerror, char seleccion[], boolean sensibleamayusculas);

boolean validarLetraUnica         (char original, char dada, boolean sensibleamayusculas);
boolean validarLetraConjunto      (char letra, char seleccion[], boolean sensibleamayusculas);
char *  cadenaOpcionesDisponibles (char entrada[]);


#endif   // UTILIDADES_H
