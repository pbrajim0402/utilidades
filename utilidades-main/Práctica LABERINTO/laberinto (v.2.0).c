#include "../utilidades/utilidades.h"
#include "../utilidades/utilidades.c"

#define MODO_SILENCIOSO
#define MODO_SIN_AYUDA
// #define MODO_INTERACTIVO

#define MAPA_MAPEADO_PROPIO   // Anular esta línea para usar teclas por defecto.

#ifdef MAPA_MAPEADO_PROPIO
  #define MAPA_NORTE 'W'   // O cambiar por 'I'
  #define MAPA_SUR   'S'   // O cambiar por 'K'
  #define MAPA_OESTE 'A'   // O cambiar por 'J'
  #define MAPA_ESTE  'D'   // O cambiar por 'L'
#endif

#define SALIR 'X'

#include "../mapa/mapa.h"
#include "../mapa/mapa.c"



// PREDECLARACIÓN DE FUNCIONES INTERNAS.

#ifdef MODO_INTERACTIVO

static char procesarTecla(char tecla);

#endif



// SUBPROGRAMA PRINCIPAL: EL S.O. PASA EL CONTROL AQUÍ AL PONER EN MARCHA EL EJECUTABLE.

int main (void) // Devuelve int para iNUMFormar al S.O. de cómo fue todo.
{
  const int NUMF = 24;   // Las filas que hemos definido para la matriz y esperamos en el archivo.
  const int NUMC = 25;   // Las columnas que hemos definido para matriz y esperamos en el archivo.
  
  char mapa[NUMF][NUMC]; // Memoria para el mapa.
  
  int tecla; // Para la elección del usuario (UNICODE).
  
  generarCadenaTeclasReconocidas("X");
    // CADENATECLASRECONOCIDAS vale "NSOEX" si usamos teclas por defecto de mapa.h.
    // CADENATECLASRECONOCIDAS vale "WASDX" si redefinimos las teclas.

  cargarMapaEstatico(MAPA_ARCHIVO_DEFECTO, NUMF, NUMC, mapa);
  
    // cargarMapaEstatico("mapa.dat", NUMF, NUMC, mapa);
    // cargarMapaEstatico("mazmorra-1.txt", NUMF, NUMC, mapa);
    // cargarMapaEstatico("mazmorra-2.txt", NUMF, NUMC, mapa);
  
  int YMAX = NUMF-1;
  int XMAX = NUMC-1;
    // CUIDADO: Las posiciones válidas son 0 a 24 en H y 0 a 23 en V, con los valores por defecto.
  
  // POSICIÓN DEL JUGADOR.
  int xjugador = 0, yjugador = 0; // Registro de la posición del muñeco.
    
    // yjugador=0 y xjugador=0 es la esquina superior izquierda.
    //
    //   int xjugador = 10;   // Si queremos fijar nosotros la X.
    //   int yjugador = 10;   // Si queremos fijar nosotros la Y.
  
  // Buscamos '@' en el mapa. Si no lo había, por defecto las coordenadas son (0,0).
  obtenerPosicionJugador(NUMF, NUMC, mapa, &xjugador, &yjugador);
  
  while(TRUE)   // Bucle iNUMFinito. Saldremos mediante uso de BREAK.
  {
    // BORRAMOS FOTOGRAMA
    system(BORRAR);
    fflush(stdout);
    
    // MENSAJE ENUMCIMA DEL LCD
    puts("LABERINTO ...");
    puts("");

    // COLOCAMOS EL MUÑECO EN EL MAPA EN LA POSICIÓN ACTUAL.
    mapa[yjugador][xjugador] = '@'; // Sí, esto es el muñeco.

    // MOSTRAMOS LCD DESDE LOS CONTENIDOS DE LA MEMORIA.
    mostrarMapa(NUMF, NUMC, mapa);
    
    // PEDIMOS ELECCIÓN AL USUARIO.
    
    LINEAENBLANCO;
    
    #ifndef MODO_INTERACTIVO
      tecla = pedirLetraSeleccion("Elige acción", 2, TRUE, CADENATECLASRECONOCIDAS, FALSE);
    #else
      mostrar("Acciones disponibles [");
      mostrar(cadenaOpcionesDisponibles(CADENATECLASRECONOCIDAS));
      mostrar("]");
      tecla = procesarTecla(obtenerTeclaInteractiva());
    #endif
    
    // DECIDIMOS ACCIÓN SEGÚN LA ELECCIÓN DEL USUARIO.
    switch(tecla)
    {
      case MAPA_DIR_ARRIBA: // Norte o arriba (También MAPA_DIR_NORTE, MAPA_NORTE o MAPA_ARRIBA).
      
      if (yjugador > 0) // ¿Nos salimos del mapa por arriba?
      {
        if (mapa[yjugador-1][xjugador] != MAPA_SIMBOLO_PARED) // ¿Hay MURO O HUECO?
        {
          // Limpiamos posición actual del mapa.
          mapa[yjugador][xjugador] = MAPA_SIMBOLO_HUECO;   // Comentar para ver estela.
          
          yjugador = yjugador - 1;
        }
      }

      break;
      
      case MAPA_DIR_ABAJO: // Sur o abajo (También MAPA_DIR_SUR, MAPA_SUR o MAPA_ABAJO).

      if (yjugador < YMAX) // ¿Nos salimos del mapa por abajo?
      {
        if (mapa[yjugador+1][xjugador] != MAPA_SIMBOLO_PARED) // ¿Hay MURO O HUECO?
        {
          // Limpiamos posición actual del mapa.
          mapa[yjugador][xjugador] = MAPA_SIMBOLO_HUECO;   // Comentar para ver estela.

          yjugador = yjugador + 1;
        }
      }

      break;
      
      case MAPA_DIR_IZQUIERDA: // Oeste o izquierda (También MAPA_DIR_OESTE, MAPA_OESTE o MAPA_IZQUIERDA).

      if (xjugador > 0) // ¿Nos salimos del mapa por la izquierda?
      {
        if (mapa[yjugador][xjugador-1] != MAPA_SIMBOLO_PARED) // ¿Hay MURO O HUECO?
        {
          // Limpiamos posición actual del mapa.
          mapa[yjugador][xjugador] = MAPA_SIMBOLO_HUECO;   // Comentar para ver estela.
          
          xjugador = xjugador - 1;
        }
      }

      break;
      
      case MAPA_DIR_DERECHA: // Este o derecha (También MAPA_DIR_ESTE, MAPA_ESTE o MAPA_DERECHA).

      if (xjugador < XMAX) // ¿Nos salimos del mapa por la derecha?
      {
        if (mapa[yjugador][xjugador+1] != MAPA_SIMBOLO_PARED) // ¿Hay MURO O HUECO?
        {
          // Limpiamos posición actual del mapa.
          mapa[yjugador][xjugador] = MAPA_SIMBOLO_HUECO;   // Comentar para ver estela.
          
          xjugador = xjugador + 1;
        }
      }

      break;
      
      // NO HACER NADA, ni mensaje de opción inválida.
      case INTRO:
      case SALIR:   // Tampoco para salir, lo controlamos más adelante.

      break;
      
      // LO SIGUIENTE ESTÁ ANULADO, YA QUE pedirLetraSeleccion() ya lo hace.
      
      // default: // DAR UN MENSAJE DE ERROR.
      //  puts("");
      //  puts("");
      //  printf("  OPCIÓN NO VÁLIDA...\n");
    }

    if (tecla == SALIR) break; // Terminamos bucle y salimos.

    // RETARDO
    retardoMilisegundos(1000);
  }
  
  system(BORRAR);
  puts("Terminó la ejecución del programa.");
  pausa();
  
  codigoError = 0; 
  return codigoError; // Devolvemos 0 (SIN ERRORES) como punto natural de salida.
}

#ifdef MODO_INTERACTIVO

static char procesarTecla(char tecla)
{
  switch(tecla)
  {
    case TECLA_ARRIBA:    return MAPA_NORTE;
    case TECLA_ABAJO:     return MAPA_SUR;
    case TECLA_IZQUIERDA: return MAPA_OESTE;
    case TECLA_DERECHA:   return MAPA_ESTE;
    case TECLA_ESCAPE:    return SALIR;
    
    // Si no es una tecla especial, devolvemos la tecla original.
    default:
      tecla = toupper(tecla);
      return tecla; 
  }
}

#endif
