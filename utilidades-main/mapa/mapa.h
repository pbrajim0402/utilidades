#ifndef MAPA_H
#define MAPA_H

/**
 * @file mapa.h
 * @author Profesor PRYC (¿o era CDPC2?)
 * @date 2026-03-10
 * @version 91.3.4
 * @brief Librería para la gestión dinámica de mapas de caracteres desde fichero.
 * 
 * @details Esta versión permite el uso indistinto de matrices estáticas 
 * (creadas por el alumno) o dinámicas (gestionadas por la librería).
 * Utiliza variables globales MAPA_NFILS y MAPA_NCOLS para las matrices dinamicas.
 */

// ZONA DE MACROS, CONSTANTES Y VARIABLES GLOBALES: PARA USO GLOBAL.

#if !defined(MODO_SILENCIOSO) || !defined(MODO_SIN_AYUDA)

#ifndef MODO_SILENCIOSO
  #warning "Esta librería permite usar TAMBIÉN matrices cargadas automáticamente desde un fichero."
  #warning "Para ello tendrás que crear la matriz con la macro GENERAR_MAPA(nombre) y usar las"
  #warning "variables globales MAPA_NFILS y MAPA_NCOLS, que se actualizarán mediante cargarMapa()."
  // #undef MODO_SILENCIOSO
#endif

#ifndef MODO_SIN_AYUDA
  #warning "Para desactivar estos avisos, ANTES de incluir mapa.h:"
  #warning "1. Añade a tu código: #define MODO_SILENCIOSO"
  #warning "2. Añade a tu código: #define MODO_SIN_AYUDA"
  // #undef MODO_SIN_AYUDA
#endif

#endif



#include "../utilidades/utilidades.h"

// Variables para forzar a usar en otros archivos.
extern int   MAPA_NFILS;
extern int   MAPA_NCOLS;
extern void *MAPA_MATRIZ;   // La matriz en sí, aunque se podrá elegir el nombre con la macro.



// Macro para que el alumno declare su matriz local sin recurrir a punteros.
#define GENERAR_MAPA(nombre) char (*nombre)[MAPA_NCOLS] = (char (*)[MAPA_NCOLS]) MAPA_MATRIZ

#define MAPA_ARCHIVO_DEFECTO "mapa.dat"

#define MAPA_SIMBOLO_JUGADOR '@'
#define MAPA_SIMBOLO_PARED   '#'
#define MAPA_SIMBOLO_HUECO   ' '

// Símbolos para las direcciones si no se definen aparte.

  #ifndef MAPA_MAPEADO_PROPIO
    #ifndef MODO_SIN_AYUDA
      #warning "Teclas de dirección por defecto N/S/E/O."
    #endif
    #define MAPA_NORTE 'N'
    #define MAPA_SUR 'S'
    #define MAPA_OESTE 'O'
    #define MAPA_ESTE 'E'

    #define MAPA_ARRIBA    MAPA_NORTE
    #define MAPA_ABAJO     MAPA_SUR
    #define MAPA_IZQUIERDA MAPA_OESTE
    #define MAPA_DERECHA   MAPA_ESTE
  #endif

typedef enum
{
  MAPA_DIR_NORTE     = MAPA_NORTE,
  MAPA_DIR_SUR       = MAPA_SUR,
  MAPA_DIR_OESTE     = MAPA_OESTE,
  MAPA_DIR_ESTE      = MAPA_ESTE,
  MAPA_DIR_ARRIBA    = MAPA_DIR_NORTE,
  MAPA_DIR_ABAJO     = MAPA_DIR_SUR,
  MAPA_DIR_IZQUIERDA = MAPA_DIR_OESTE,
  MAPA_DIR_DERECHA   = MAPA_DIR_ESTE
} MAPA_DIRECCIONES;

char *CADENATECLASRECONOCIDAS = NULL;   // Declaramos la cadena como puntero para poder iniciarla a NULL.

// ZONA DE PREDECLARACIÓN: CABECERA O PROTOTIPO DE SUBPROGRAMAS

/**
 * @brief Carga una matriz 2D de forma dinámica analizando un fichero automáticamente.
 * 
 * Reserva memoria en la variable global 'matriz' y actualiza NFILS y NCOLS.
 * 
 * @param nombreArchivo Cadena con la ruta del fichero a leer (.dat, .txt o el que sea).
 * @return boolean TRUE si la carga fue exitosa, FALSE si hubo error de lectura o memoria.
 * @note Requiere llamar a GENERAR_MAPA(nombre) tras el éxito de esta función.
 * @note Tambien debera liberarse implicitamente la memoria creada para la matriz con liberarMapa().
 */

boolean cargarMapa(char nombreArchivo[]);   // La única función que el alumno llamará en dinámico.

/**
 * @brief Carga un mapa desde un archivo en una matriz estática proporcionada por el usuario.
 * 
 * @param nombreArchivo Ruta del fichero de datos.
 * @param fils Número de filas que el alumno ha reservado para su matriz.
 * @param cols Número de columnas que el alumno ha reservado para su matriz.
 * @param mapa Referencia a la matriz bidimensional donde se volcarán los datos.
 * @pre El fichero debe tener exactamente las dimensiones fils x cols.
 */

void cargarMapaEstatico(char nombreArchivo[], int fils, int cols, char casilla[fils][cols]);

void mostrarMapa(int fils, int cols, char casilla[fils][cols]);
void mostrarMapaXY(int fils, int cols, char cailla[fils][cols], int yinc, int xinc);
void obtenerPosicionJugador(int fils, int cols, char casilla[fils][cols], int *xJugador, int *yJugador);
boolean analizarFicheroMapa(char nombreArchivo[], int *fils, int *cols);
void liberarMapa(void);

#endif
