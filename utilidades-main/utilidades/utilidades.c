////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// ZONA DE IMPORTACIÓN: FICHEROS NECESARIOS A INCLUIR
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "utilidades.h"   // Mi propia colección de subprogramas útiles.



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// ZONA DE MACROS, CONSTANTES Y VARIABLES GLOBALES: PARA USO GLOBAL.
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

char MSJxERROR[] = "¡VALOR NO VÁLIDO!";
char MSJxPAUSA[] = "Pulse INTRO para continuar... ";

int codigoError; // VARIABLE GLOBAL: Visible por todos los subprogramas.



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// ZONA DE CÓDIGO: CUERPOS DE LOS SUBPROGRAMAS DECLARADOS ANTES.
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void esperarINTRO (void);
//
//  USO:
//
//    Programa que produce una espera hasta que se pulse INTRO.
//
//  DETALLES:
//
//    Es un envoltorio de la función vaciarBuffer(), a la cual delega todo el
//    trabajo. Es una manera de crear "sinónimos" de acciones, es decir, de
//    tener disponibles varios nombres para hacer lo mismo.
//
//  PARÁMETROS DE ENTRADA:
//
//    Ninguno
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    vaciarBuffer()
//
//      Se delega toda la carga de trabajo a esta función.
//
////////////////////////////////////////////////////////////////////////////////

void esperarINTRO (void)
{
  vaciarBuffer();
}


void descartarEntrada (void)
{
  vaciarBuffer();
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void vaciarBuffer (void);
//
//  USO:
//
//    Programa que espera que el usuario pulse teclas a la espera de INTRO.
//
//  DETALLES:
//
//    Se basa en un bucle que va pidiendo letras del buffer de teclado y no
//    termina hasta que detecta que ha encontrado un "INTRO" (0x10). Cualquier
//    otro código ASCII introducido por el usuario se descarta. Se produce ECO
//    de cualquier tecla pulsada.
//
//  PARÁMETROS DE ENTRADA:
//
//    Ninguno
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    getchar()
//
//      Es el programa estándar ("prefabricado") que hace la logística de
//      comunicarse con el sistema operativo y con el hardware del teclado.
//
////////////////////////////////////////////////////////////////////////////////

void vaciarBuffer (void)
{
  // ENTER CREADO EN DEFINE = ASCII(10) = 0x0A
  
  // MEDIANTE BUCLE DO-WHILE:
  char letra;
  do
  {
    letra = getchar();
  } while (letra != ENTER);
  
  // MEDIANTE BUBLE WHILE:
  // while (getchar() != '\n')   ; // Bucle vacío
}


void borrarPantalla (void)
{
  limpiarPantalla();
}


void limpiarPantalla (void)
{
  system(BORRAR);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void bajar (int nlineas);
//
//  USO:
//
//    Permite bajar el cursor en la pantalla, tantas líneas como se le indique.
//
//  DETALLES:
//
//    Crea tantas líneas en blanco como se le suministre como dato. No ubica el
//    cursor de texto en ninguna coordenada concreta, sino que genera contenido
//    en blanco en la pantalla, desplazando el punto donde se escribirá texto en
//    acciones posteriores. Utiliza para ello un bucle en cuyo interior se llama
//    a printf() con el código ASCII de salto de línea '\n' ó 0x10.
//
//  PARÁMETROS DE ENTRADA:
//
//    nlineas
//
//      Variable entera que recibirá del exterior el número de líneas en blanco
//      que se va a desplazar el cursor hacia abajo.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    printf()
//
//      Es el programa estándar ("prefabricado") que hace la logística de
//      emitir por pantalla.
//
////////////////////////////////////////////////////////////////////////////////

void bajar (int nlineas)
{
  while(nlineas>0)
  {
    printf("\n");   // No se puede usar "mostrar()" porque crearíamos un bucle de llamadas.
    
    nlineas--;
  }
}


void abajo (int nfils)
{
  bajar(nfils);
}


void saltar (int nfils)
{
  bajar(nfils);
}


void desplazarFils (int nfils)
{
  bajar(nfils);
}


void desplazarV (int nfils)
{
  bajar(nfils);
}


void desplazarY (int nfils)
{
  bajar(nfils);
}


void indentar (int ncolumnas)
{
  for(int i=0; i<ncolumnas; i++)
  {
    printf(" ");   // No se puede usar "mostrar()" porque crearíamos un bucle de llamadas.
  }
}


void derecha (int ncols)
{
  indentar(ncols);
}


void tabular (int ncols)
{
  indentar(ncols);
}


void desplazarCols (int ncols)
{
  indentar(ncols);
}


void desplazarX (int ncols)
{
  indentar(ncols);
}


void desplazarH (int ncols)
{
  indentar(ncols);
}


void posicionar (int nfils, int ncols)
{
  bajar(nfils);
  tabular(ncols);
}


void desplazar (int nfils, int ncols)
{
  posicionar(nfils, ncols);
}


void desplazarXY (int nfils, int ncols)
{
  posicionar(nfils, ncols);
}


void retardoSegundos (int segundosmax)
{
  // POSIBILIDAD: Poner en función de la que usa milisegundos.
  
  // AJUSTAR CEROS DE LOS BUCLES PARA APROXIMAR EL PERIODO.

  for(int nseg=0; nseg < segundosmax ; nseg++)
  {
    for(int j=0; j<100; j++)
      for(int j=0; j<1000; j++)
        for(int k=0; k<1000; k++)   ;
  }
}


void retardoMilisegundos (int milisegundosmax)
{
  int i, j;
  
  // AJUSTAR CEROS DE LOS BUCLES PARA APROXIMAR EL PERIODO.

  for (int nmiliseg=0; nmiliseg<milisegundosmax ; nmiliseg++)
    for (i=0; i<100; i++)
      for (j=0; j<1000; j++)   ;
}


void retrasoMilisegundos (int milisegundos)
{
  double e = 0;

  clock_t t0 = clock();   // clock_t es un tipo interno equivalente a UINT32.
  
  do
  {
    
    e = 1000*(double)(clock()-t0)/CLOCKS_PER_SEC;

  } while (e<milisegundos);
}


void esperarSegundos (int segundos)
{
  #ifdef SO_WINDOWS
    Sleep(segundos*1000);
  #else
    sleep(segundos);
  #endif
}


void esperarMilisegundos (int milisegundos)
{
  #ifdef SO_WINDOWS
    Sleep(milisegundos);
  #else
    usleep(milisegundos*1000);   // Alternativa: nanosleep() de "time.h".
  #endif
}


void pausa (void)
{
  pausaEstandar(1, 2);
}


void pausaEstandar (int nfils, int ncols)
{
  pausaGenerica(MSJxPAUSA, nfils, ncols, FALSE);
}


void pausaGenerica (char msjtxt[], int nfils, int ncols, boolean nuevalinea)
{
  mensaje_x_y(msjtxt, nfils, ncols, nuevalinea);

  esperarINTRO();
}


void texto (char msjtxt[])
{
  puts(msjtxt);
}


void separar()
{
  mostrar("\n");
}


void nuevaLinea (void)
{
  saltar(1);
}


void mostrar (char msjtxt[])
{
  mostrar_x_y (msjtxt, 0, 0);
}


void mostrar_x_y (char msjtxt[], int nfils, int ncols)
{
  mensaje_x_y (msjtxt, nfils, ncols, FALSE);
}


void escribir (char msjtxt[])
{
  escribir_x_y (msjtxt, 0, 0);
}


void escribir_x_y (char msjtxt[], int nfils, int ncols)
{
  mensaje_x_y (msjtxt, nfils, ncols, FALSE);
}


void imprimir (char msjtxt[])
{
  imprimir_x_y (msjtxt, 0, 0);
}


void imprimir_x_y (char msjtxt[], int nfils, int ncols)
{
  mensaje_x_y (msjtxt, nfils, ncols, FALSE);
}


void mensaje (char msjtxt[], int nfils, int ncols)
{
  mensaje_x_y (msjtxt, nfils, ncols, FALSE);
}


void mensaje_x_y (char msjtxt[], int nfils, int ncols, boolean nuevalinea)
{
  saltar(nfils);
  tabular(ncols);
  printf("%s", msjtxt);
  
  if (nuevalinea)   printf("\n");   // ALTERNATIVA: if (nuevalinea)   putchar(ENTER);
}


void iniciaAleatorizador (void)
{
  srand(time(NULL));
}


int generaAleatorioEntero (int limite)
{
  // Generará un número entre 0 y limite - 1, nunca llega a limite.
  return (rand() % limite);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    int obtenerEntero (void);
//
//  USO:
//
//    Sustitución mejorada de scanf() que impide que queden letras almacenadas
//    en el buffer de teclado para posteriores operaciones de entrada de datos.
//
//  DETALLES:
//
//    La función scanf() no retira el código ASCII de la letra INTRO del buffer
//    de teclado ni posibles letras después de un texto que se pueda convertir
//    en una cantidad. Nos ayudamos de otra función creada en esta librería,
//    vaciarBuffer() para ello. No muestra ningún mensaje por pantalla.
//
//  PARÁMETROS DE ENTRADA:
//
//    nlineas
//
//      Variable entera que recibirá del exterior el número de líneas en blanco
//      que se va a desplazar el cursor hacia abajo.
//
//  VALOR DE SALIDA:
//
//    Devuelve al exterior el valor entero que a su vez ha recibido en la
//    variable "valor" de la función scanf(), mediante paso por referencia.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    scanf()
//
//      Es el programa estándar ("prefabricado") que hace la logística de
//      leer caracteres del teclado y convertirlos en la cantidad entera.
//
////////////////////////////////////////////////////////////////////////////////

int obtenerEntero (void)
{
  int valor;
  
  scanf("%d", &valor);
  vaciarBuffer();

  return valor;
}


char obtenerCaracterASCII()
{
  return obtenerLetra();
}


char obtenerLetra (void)   // Sólo ASCII VÁLIDO.
{
  char letra, valida;
  
  letra = getchar();
  
  if (letra < 128)
    valida = letra; // Devolveremos la letra
  else
    valida = '\0';  // Devolveremos la letra nula.
  
  // VACIAMOS POSIBLES CÓDIGOS EN EL BUFFER.
  //   Se incluye el INTRO EXTRA y una posible escritura de múltiples letras.
  if (letra != ENTER)   vaciarBuffer();

  return valida;
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    int pedirEntero (char msjtxt[], int ncols);
//
//  USO:
//
//    Muestra un mensaje en pantalla para pedir un dato entero al usuario. El
//    mensaje es configurable y desplazable un número de caracteres desde la
//    izquierda de la pantalla.
//
//  DETALLES:
//
//    Es como un printf() más un scanf(), mejorados. Puede desplazarse el texto
//    recibido mediante un segundo dato entero. También impide problemas del
//    buffer de teclado con scanf(). Para ello, delega el emitir el mensaje por
//    pantalla a las funciones msj() y mostrar(), y la toma del dato entero a la
//    función obtenerEntero().
//
//  PARÁMETROS DE ENTRADA:
//
//    mensaje
//
//      Variable de tipo vector de caracteres donde se recibirá el texto que se
//      debe mostrar, que debe ser una cadena terminada en '\0'.
//
//    tabs
//
//      Variable entera donde se recibirá del exterior el número de espacios en
//      blanco a añadir antes del mensaje.
//
//  VALOR DE SALIDA:
//
//    Devuelve al programa donde se invoque, un valor entero que a su vez esta
//    función ha recibido desde la función obtenerEntero().
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    msj()
//
//      Se encarga efectivamente de mostrar el mensaje.
//
//    mostrar()
//
//      Usada para añadir en pantalla un texto adicional después del mensaje.
//
//    obtenerEntero()
//
//      Es la función que se encarga en la práctica de obtener la cantidad.
//
////////////////////////////////////////////////////////////////////////////////

int pedirEntero (char msjtxt[], int ncols)
{
  mensaje(msjtxt, 0, ncols);
  mostrar(": ");
  
  return obtenerEntero();
}


int pedirEnteroPositivo (char msjtxt[], int ncols, boolean mostrarerror)
{
  int num;
  
  do
  {
    mensaje(msjtxt, 0, ncols);
    mostrar(": ");
    num = obtenerEntero();
    
    if (mostrarerror)
    {
      if (num < 0)
      {
        nuevaLinea();
        mensaje_x_y(MSJxERROR, 0, ncols+2, TRUE);
        nuevaLinea();
      }
    }
    
  } while (num < 0);
  
  return num;
}


int pedirEnteroIntervalo (char msjtxt[], int ncols, boolean mostrarerror, int min, int max)
{
  int num;
  
  do
  {
    mensaje(msjtxt, 0, ncols);
    printf(" [%d,%d]: ", min, max);
    
    num = obtenerEntero();
    
    if (mostrarerror)
    {
      if (num < min || num > max)
      {
        nuevaLinea();
        mensaje_x_y(MSJxERROR, 0, ncols+2, TRUE);
        nuevaLinea();
      }
    }
    
  } while (num < min || num > max);
  
  return num;
}


int pedirLetra (char msjtxt[], int ncols, boolean mostrarerror, char letra)
{
  char pedida;
  
  letra = toupper(letra);
  
  do
  {
    mensaje(msjtxt, 0, ncols);
    mostrar(": ");
    
    pedida = obtenerLetra();
    pedida = toupper(pedida);   // Convertimos a mayúsculas para simplificar casos.
    
    if (mostrarerror)
    {
      if (letra != pedida)
      {
        nuevaLinea();
        mensaje_x_y(MSJxERROR, 0, ncols+2, TRUE);
        nuevaLinea();
      }
    }
    
  } while (letra != pedida);
  
  return pedida;
}


int pedirConfirmacion (char msjtxt[], int ncols, boolean mostrarerror)
{
  char letra;
  
  do
  {
    mensaje(msjtxt, 0, ncols);
    printf(" [%c/%c]: ", SI, NO);
    
    letra = obtenerLetra();
    letra = toupper(letra);   // Convertimos a mayúsculas para simplificar casos.
    
    if (mostrarerror)
    {
      if (letra != SI && letra != NO)
      {
        nuevaLinea();
        mensaje_x_y(MSJxERROR, 0, ncols+2, TRUE);
        nuevaLinea();
      }
    }
    
  } while (letra != SI && letra != NO);
  
  return letra;
}


boolean validarLetraUnica (char original, char dada, boolean sensibleamayusculas)
{
  if (!sensibleamayusculas)
  {
    original = toupper(original);
      dada   = toupper(dada);
  }
  
  return (original == dada);
}


boolean validarLetraConjunto (char letra, char seleccion[], boolean sensibleamayusculas)
{
  boolean resultado = FALSE;
  int largo = strlen(seleccion);
  
  for(int i = 0; i < largo ; i++)
  {
    if (validarLetraUnica(letra, seleccion[i], sensibleamayusculas))
    {
      resultado = TRUE;
      break;
    }
  }
  
  return resultado;
}


char *cadenaOpcionesDisponibles (char entrada[])
{
  if (entrada == NULL) return NULL;   // Si no dan nada, petas máximus ...
  
  char *textoinicial, *textofinal;
  
  textoinicial = entrada;
  
  int largoinicial, largofinal;
  
  largoinicial = strlen(textoinicial);

  if (largoinicial == 0)
  {
    // Nos dan cadena vacía, así que generamos vacía. Pero consideramos el '\0'.
    largofinal = 1;
    textofinal = (char *) malloc(1*sizeof(char));
    textofinal[0] = '\0';
  }
  else
  {
    // CASO 1: "A" -> "A" => largo 2 = 1 (letra) + 1 ('\0')
    // CASO 2: "ABC" -> "A/B/C" => largo 6 = 3 (letras) + 2 (sepadores) +1 ('\0'); 
    largofinal = 2 * largoinicial;
    textofinal = (char *) malloc(largofinal*sizeof(char));
    
    if (textofinal != NULL)
    {
      int j = 0;
      for (int i = 0; i < largoinicial; i++, j++)
      {
        textofinal[j] = textoinicial[i];
        j++;
        textofinal[j] = '/';
      }
      
      // Sustituimos la última '/' por un ' 0'.
      j--;
      textofinal[j] = '\0';
    }
  }

  return textofinal;
}


int pedirLetraSeleccion (char msjtxt[], int ncols, boolean mostrarerror, char seleccion[], boolean sensibleamayusculas)
{
  // HACER: Evitar que falle con «seleccion» a valor NULL.
  
  // Usar «cadenaOpcionesDisponibles()» implica luego liberar memoria con «free()».
  char *editada = cadenaOpcionesDisponibles(seleccion);
  
  char letra;
  
  boolean validada;
  
  do
  {
    mensaje(msjtxt, 0, ncols);
    mostrar(" [");
    printf("%s", editada);
    mostrar("]: ");
    
    letra = obtenerLetra();

    validada = validarLetraConjunto(letra, seleccion, sensibleamayusculas);
    
    if (mostrarerror)
    {
      if (!validada)
      {
        nuevaLinea();
        mensaje_x_y(MSJxERROR, 0, ncols+2, TRUE);
        nuevaLinea();
      }
    }
  } while (!validada);
  
  // Liberamos la memoria para cadena modificada.
  free(editada);
  
  // Si no era sensible a mayúsculas, siempre la devolvemos mayúscula.
  if (!sensibleamayusculas)   letra = toupper(letra);
  
  return letra;
}



#ifdef SO_WINDOWS

#include <conio.h>

char obtenerTeclaInteractiva(void)
{
  int caracter = _getch();   // En Windows, getch() ya es bloqueante por defecto.

  if (caracter == 0 || caracter == 224)
  {
    // Tecla especial, depende de un segundo código. Lo leemos.
    caracter = _getch();
    
    switch(caracter)
    {
      case 72: caracter = TECLA_ARRIBA;    break;   // Flecha Arriba
      case 80: caracter = TECLA_ABAJO;     break;   // Flecha Abajo
      case 75: caracter = TECLA_IZQUIERDA; break;   // Flecha Izquierda
      case 77: caracter = TECLA_DERECHA;   break;   // Flecha Derecha
      default: caracter = TECLA_NULA;               // Tecla nula.
    }
    else
    {
      // Normalización de teclas conflictivas no estándar.
      switch(caracter)
      {
        case 13: caracter = TECLA_ENTER;
        case 8:  caracter = TECLA_RETROCESO;
      }
    }
    
    return (char)caracter;
}

#else

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int obtenerTeclaInteractiva(void)
{
  struct termios terminaloriginal, terminalnueva;
  int caracter;

  // 1. Obtenemos la configuración actual de la terminal.
  tcgetattr(STDIN_FILENO, &terminaloriginal);
  terminalnueva = terminaloriginal;

  // 2. Desactivamos el modo canónico (espera de INTRO) y el ECO (ver la tecla al pulsar).
  terminalnueva.c_lflag &= ~(ICANON | ECHO); // Quitamos espera de INTRO y eco
  tcsetattr(STDIN_FILENO, TCSANOW, &terminalnueva);
  
  // 3. El programa se detiene aquí hasta recibir un carácter.
  // Las flechas envían una secuencia de escape: 27 (ESC), 91 ('['), y una letra.
  caracter = getchar();
  
  if (caracter == ESCAPE)
  {
    // Cambiamos a NO BLOQUEANTE un instante para ver si hay bytes extra
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    
    // Pedimos a ver si hay otro caracter.
    int siguiente = getchar();
    
    // ¿Es '[' (91)?
    if (siguiente == '[')
    {
      // Lo desechamos simplemente no usando "siguiente".

      // Pedimos el tercer código de caracter generado.
      caracter = getchar();
      
      while ((siguiente = getchar()) != EOF && siguiente != -1);

      switch(caracter)
      {
        case 'A': caracter = TECLA_ARRIBA;    break;   // Flecha Arriba
        case 'B': caracter = TECLA_ABAJO;     break;   // Flecha Abajo
        case 'D': caracter = TECLA_IZQUIERDA; break;   // Flecha Izquierda
        case 'C': caracter = TECLA_DERECHA;   break;   // Flecha Derecha
        default:  caracter = TECLA_NULA;      break;
      }
    }
    else
    {
      if (siguiente == EOF || siguiente == -1)
      {
        // Era sólo la tecla ESCAPE.
        caracter = TECLA_ESCAPE;
      }
      else
      {
        // Era una secuencia no contemplada.
        caracter = TECLA_NULA;
      }
    }

    // Restauramos el modo BLOQUEANTE de la terminal.
    fcntl(STDIN_FILENO, F_SETFL, flags);
  }

  // 4. Restauramos la configuración original antes de salir.
  tcsetattr(STDIN_FILENO, TCSANOW, &terminaloriginal);
  
  return caracter;
}

#endif
