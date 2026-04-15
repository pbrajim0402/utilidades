// ZONA DE MACROS, CONSTANTES Y VARIABLES GLOBALES: PARA USO GLOBAL.

#define TRUE  1 // Cada vez que aparezca TRUE en el código, se sustituye
#define FALSE 0 // por 1, siempre previamente a generar el ejecutable.

typedef int boolean; // No existe tipo "boolean" en C. Lo "creamos".

const float PI = 3.14159; // Así nos creamos una CONSTANTE GLOBAL.

int codigoError; // VARIABLE GLOBAL: Visible por todos los subprogramas.

#define INTRO 10 // Código ASCII de NUEVA LÍNEA (NEW LINE).

  // INTRO EN WINDOWS ES 13 + 10, EN MAC ES 13, EN UN*X/LINUX ES 10.



// ZONA DE PREDECLARACIÓN: CABECERA O PROTOTIPO DE SUBPROGRAMAS

char obtenerCaracterASCII (void);
void pausa                (void);
void retardoMilisegundos  (int milisegundos);
void retardoSegundos      (int segundos);
