// ZONA DE IMPORTACIÓN: FICHEROS NECESARIOS A INCLUIR

#include "mapa.h"



// Definición de las variables globales

int MAPA_NFILS = 0;
int MAPA_NCOLS = 0;

void *MAPA_MATRIZ = NULL;   // Variable para creación dinámica de tabla en memoria.



// ZONA DE CÓDIGO: CUERPOS DE LOS SUBPROGRAMAS DECLARADOS ANTES.

boolean cargarMapa(char nombreArchivo[])
{
  // ¿Había una matriz ya cargada desde el disco?
  if (MAPA_MATRIZ != NULL)
  {
    free(MAPA_MATRIZ);
    MAPA_MATRIZ = NULL;
  }
  
  // Para comprobar si los datos tienen el formato correcto.
  boolean analisisCorrecto;
  
  // Variables para recorrer filas y columnas en la matriz.
  int leido, i, j;
  
  FILE *archivo;

  // 1. Pedimos análisis para ver si el fichero de datos es adecuado.
  
  analisisCorrecto = analizarFicheroMapa(nombreArchivo, &MAPA_NFILS, &MAPA_NCOLS);
  
  if (!analisisCorrecto)
  {
      return FALSE; // Error: fichero inválido o inexistente.
  }

  // 2. Reservamos la memoria exacta (un solo bloque contiguo de memoria).

  // Definimos un nombre para el tipo "puntero a fila de ancho ncols".
  typedef char FilaMapa[MAPA_NCOLS];   // NO PREGUNTES: Usos avanzados.
  
  // Creamos un nombre auxiliar para referirnos al mapa.
  FilaMapa *m_aux;   // NO PREGUNTES: Usos avanzados.
    
  MAPA_MATRIZ = malloc(MAPA_NFILS * MAPA_NCOLS * sizeof(char));

  if (MAPA_MATRIZ == NULL)
  {
    return FALSE;  // Error: problemas con la reserva de memoria.
  }

  // Conectamos el nombre auxiliar con la matriz.
  m_aux = (FilaMapa *) MAPA_MATRIZ;

  // 3. Volvemos a abrir para volcar los datos a la matriz de memoria.
  
  archivo = fopen(nombreArchivo, "r");
  
  if (!archivo)   // Alternativa: archivo == NULL
  {
      free(MAPA_MATRIZ);
      MAPA_MATRIZ = NULL;
      return FALSE;
  }
  
  i = 0;
  
  while(i < MAPA_NFILS)
  {
    j = 0;
    
    while(j < MAPA_NCOLS)
    {
      leido = fgetc(archivo);
      
      if (leido == ASCII_CR)   continue;
      
      if (leido == ASCII_NL)   continue;
      
      m_aux[i][j] = (char)leido;
      
      j++;
    }
    
    i++;
  }

  fclose(archivo);
  
  return TRUE;   // Se cargó sin problemas.
}


void cargarMapaEstatico(char nombreArchivo[], int fils, int cols, char casilla[fils][cols])
{
  int contador = 0;
  int i, j, salida;
  char caracter;
  FILE *archivo;
  
  archivo = fopen(nombreArchivo, "r");
  
  if (!archivo)
  {
    // puts("ERROR 1 DE LECTURA");
    // printf("  Problema con apertura de archivo.\n");
    
    perror("ERROR 1 DE LECTURA");
    exit (1);
  }
    
  for(i=0 ; i<fils ; i++)
  {
    for(j=0 ; j<cols ; j++)
    {
      salida = fscanf(archivo, "%c", &caracter);
      if (salida != 1)
      {
        // puts("ERROR 2 DE LECTURA");
        // printf("  Leídos en total %d caracteres\n", contador);
        
        perror("ERROR 2 DE LECTURA");
        exit(2);
      }
      casilla[i][j] = caracter;
      contador++;
    }

    salida = fscanf(archivo, "%c", &caracter); // INTRO DEL FINAL DE LÍNEA: ASCII 10 ó 13.
    if (salida != 1)
    {
      // puts("ERROR 3 DE LECTURA");
      // printf("  Problema con final de línea (%d)\n", contador);
      
      perror("ERROR 3 DE LECTURA");
      exit(3);
    }
    
    if (caracter == ASCII_CR)
    {
      salida = fscanf(archivo, "%c", &caracter); // INTRO DEL FINAL DE LÍNEA: ASCII 10 después de 13.

      if (salida != 1)
      {
        // puts("ERROR 3 DE LECTURA");
        // printf("  Problema con final de línea (%d)\n", contador);
        
        perror("ERROR 3 DE LECTURA");
        exit(3);
      }
    }
  }
  
  fclose(archivo);
}


void mostrarMapa(int fils, int cols, char casilla[fils][cols])
{
  mostrarMapaXY(fils, cols, casilla, 0, 0);
}


void mostrarMapaXY(int fils, int cols, char casilla[fils][cols], int yinc, int xinc)
{
  saltar(yinc);
  
  for( int i=0 ; i<fils ; i++)
  {
    tabular(xinc);
    
    for( int j=0 ; j<cols ; j++)
    {
      putchar(casilla[i][j]);
    }

    putchar('\n'); // CAMBIO DE LÍNEA.
  }
}


void obtenerPosicionJugador(int fils, int cols, char casilla[fils][cols], int *xJugador, int *yJugador)
{
  for(int i=0 ; i<fils ; i++)
  {
    for(int j=0 ; j<cols ; j++)
    {
      if (casilla[i][j] == MAPA_SIMBOLO_JUGADOR)
      {
        (*yJugador) = i;
        (*xJugador) = j;
        
        return;   // Si hay varios símbolos de jugador, terminará cuando encuentre el primero.
      }
    }
  }
  
  // Si termina el programa aquí, no hemos detectado posición del jugador. ¿Devolver false?
}


boolean analizarFicheroMapa(char nombreArchivo[], int *fils, int *cols)
{
  int leido, nfilas, ncolumnas, colsanteriores;
  
  boolean esvalido;
  
  FILE *archivo;
      
  archivo = fopen(nombreArchivo, "r");
  
  // ¿Ha habido un error de apertura del archivo?
  if (!archivo)   // archivo == NULL
  {
    // puts("ERROR 1 DE LECTURA");
    // printf("  Problema con apertura de archivo.\n");
    
    perror("ERROR 1 EN LECTURA");
    exit (1);
  }

  colsanteriores = -1;
  ncolumnas = 0;
  nfilas = 0;
  esvalido = TRUE;

  // Bucle de lectura carácter a carácter hasta el final.
  while(TRUE)
  {
    leido = fgetc(archivo);
    
    // Verificamos si hemos alcanzado el final del fichero y ya no lee más caracteres.
    if (leido == EOF)   break;   // No podemos decir si es válido o no todavía.
    
    // Ignoramos el retorno de carro adicional de Windows (\r\n).
    if (leido == ASCII_CR)   continue;
    
    // Si el carácter no es un salto de línea, es contenido de la fila.
    if (leido != ASCII_NL)
    {
      // Carácter convencional, la fila sigue y contamos una más para columnas.
      
      ncolumnas++;
    }
    else
    {
      // Hemos llegado al final de una fila.
      
      nfilas++;   //  La contabilizamos.
      
      // Si es la primera fila del fichero, establecemos el ancho mínimo.
      if (colsanteriores == -1)
      {
        // Primera fila... Fijamos el número de columnas estimado.
        colsanteriores = ncolumnas;
      }

      // No es la primera fila.
      
      // ¿La fila actual coincide con el ancho de las anteriores?
      if (ncolumnas != colsanteriores)
      {
        // No es igual a las anteriores, pero no abortamos, para contabilizarla.
        esvalido = FALSE;
      }
      
      // Tenemos una fila completa igual a las anteriores.

      ncolumnas = 0; // Reiniciamos las columnas para siguiente fila.
    }
  }
  
  // ¿Salimos por EOF en última fila?
  // ¿Salimos por columnas diferentes?

  // Validación concreta para la última fila sin salto de línea.
  if (ncolumnas > 0)
  {
    // Había caracteres en fila sin final de línea.
    
    nfilas++;
    
    // Caso especial: el fichero solo tenía una línea y sin salto final.
    if (colsanteriores == -1)
    {
      // Era la única línea del fichero, sin final de línea.
      colsanteriores = ncolumnas;
    }

    // Validamos la longitud de esta última fila contra el patrón.
    // Comparamos con otras filas que ya se hayan contabilizado.
    if (ncolumnas != colsanteriores)
    {
      esvalido = FALSE;
    }
  }
  else
  {
    // Caso: terminó en \n o el fichero estaba vacío
    if (colsanteriores == -1)
    {
        // Fichero 0 bytes: normalizamos a 0
        colsanteriores = 0;
        esvalido = FALSE;
    }
    
    // ncolumnas era 0, así que toma el valor del patrón detectado
    ncolumnas = colsanteriores;
  }
  
  // Validación final de mapas sin contenido real (0 columnas).
  if (ncolumnas == 0)
  {
      esvalido = FALSE;
  }

  fclose(archivo);
   
  *fils = nfilas;
  *cols = ncolumnas;

  return esvalido;
}


void liberarMapa(void)
{
  if (MAPA_MATRIZ != NULL)
  {
    free(MAPA_MATRIZ);    // Liberamos el bloque de memoria reservado.
    MAPA_MATRIZ = NULL;   // Evitamos que el puntero apunte a una dirección inválida.
    MAPA_NFILS = 0;       // Reseteamos dimensiones.
    MAPA_NCOLS = 0;
  }
}


void generarCadenaTeclasReconocidas(char teclasAdicionales[])
{
  if (CADENATECLASRECONOCIDAS != NULL)
  {
    perror("CADENATECLASRECONOCIDAS está diseñada para generarla sólo una vez.");
    exit(1);
  }
  
  int longitud = strlen(teclasAdicionales) + 4 + 1;
    // +4 por las cuatro teclas de dirección.
    // +1 porque es cadena de C terminada en \0.
    
  CADENATECLASRECONOCIDAS = (char *) malloc(longitud * sizeof(char));
  
  // Suponemos que no hay problema de reserva de memoria.
  
  sprintf(CADENATECLASRECONOCIDAS, "%c%c%c%c%s",
          MAPA_NORTE, MAPA_SUR, MAPA_OESTE, MAPA_ESTE, teclasAdicionales);
}
