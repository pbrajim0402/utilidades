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


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void descartarEntrada (void);
//
//  USO:
//
//    Limpia cualquier contenido pendiente en el flujo de entrada.
//
//  DETALLES:
//
//    Funciona como un alias de vaciarBuffer(). Su objetivo es asegurar que
//    no queden caracteres residuales en el buffer que puedan afectar a
//    lecturas de datos posteriores.
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
//      Realiza la limpieza efectiva del flujo de entrada.
//
////////////////////////////////////////////////////////////////////////////////

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


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void borrarPantalla (void);
//
//  USO:
//
//    Elimina todo el texto visible de la ventana de la consola.
//
//  DETALLES:
//
//    Actúa como un sinónimo de limpiarPantalla(). Permite tener una
//    nomenclatura más intuitiva para la acción de refrescar el terminal.
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
//    limpiarPantalla()
//
//      Ejecuta la instrucción de limpieza del sistema.
//
////////////////////////////////////////////////////////////////////////////////

void borrarPantalla (void)
{
  limpiarPantalla();
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void limpiarPantalla (void);
//
//  USO:
//
//    Realiza la limpieza física de la consola utilizando comandos del sistema.
//
//  DETALLES:
//
//    Invoca la función estándar system() pasando como argumento la macro
//    BORRAR, la cual debe estar definida con el comando específico del
//    sistema operativo (como "cls" o "clear").
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
//    system()
//
//      Función estándar de C para ejecutar comandos en el intérprete del SO.
//
////////////////////////////////////////////////////////////////////////////////

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


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void abajo (int nfils);
//
//  USO:
//
//    Desplaza el cursor verticalmente hacia abajo el número de filas indicado.
//
//  DETALLES:
//
//    Es una función de alias que redirige la llamada a bajar(). Se utiliza
//    para facilitar la legibilidad del código fuente según el contexto.
//
//  PARÁMETROS DE ENTRADA:
//
//    nfils
//
//      Entero que indica la cantidad de filas a descender.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    bajar()
//
//      Función base que realiza el salto de líneas.
//
////////////////////////////////////////////////////////////////////////////////

void abajo (int nfils)
{
  bajar(nfils);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void saltar (int nfils);
//
//  USO:
//
//    Genera saltos de línea en la salida estándar.
//
//  DETALLES:
//
//    Funciona como un envoltorio de la función bajar(). Permite al programador
//    expresar la intención de "saltar" un bloque de texto en la pantalla.
//
//  PARÁMETROS DE ENTRADA:
//
//    nfils
//
//      Entero que especifica cuántos saltos de línea realizar.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    bajar()
//
//      Procesa la lógica de los saltos mediante bucle y printf.
//
////////////////////////////////////////////////////////////////////////////////

void saltar (int nfils)
{
  bajar(nfils);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void desplazarFils (int nfils);
//
//  USO:
//
//    Realiza un desplazamiento vertical del cursor de escritura.
//
//  DETALLES:
//
//    Delega la ejecución a bajar(). Se emplea habitualmente en contextos de
//    formateo de tablas o menús para ajustar la posición en filas.
//
//  PARÁMETROS DE ENTRADA:
//
//    nfils
//
//      Número de filas a desplazar hacia abajo.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    bajar()
//
//      Encargada de imprimir los caracteres de nueva línea.
//
////////////////////////////////////////////////////////////////////////////////

void desplazarFils (int nfils)
{
  bajar(nfils);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void desplazarV (int nfils);
//
//  USO:
//
//    Desplaza la posición de escritura en el eje vertical.
//
//  DETALLES:
//
//    Alias de la función bajar(). El nombre "desplazarV" hace referencia
//    explícita a la dirección vertical del movimiento.
//
//  PARÁMETROS DE ENTRADA:
//
//    nfils
//
//      Cantidad de posiciones verticales a descender.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    bajar()
//
//      Implementa la lógica de desplazamiento.
//
////////////////////////////////////////////////////////////////////////////////

void desplazarV (int nfils)
{
  bajar(nfils);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void desplazarY (int nfils);
//
//  USO:
//
//    Mueve el cursor hacia abajo basándose en la coordenada Y.
//
//  DETALLES:
//
//    Llamada alternativa a bajar(). Se utiliza para integrarse con esquemas
//    de coordenadas (X, Y) donde Y representa las filas.
//
//  PARÁMETROS DE ENTRADA:
//
//    nfils
//
//      Coordenada relativa de filas a desplazar.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    bajar()
//
//      Realiza la impresión de los saltos.
//
////////////////////////////////////////////////////////////////////////////////

void desplazarY (int nfils)
{
  bajar(nfils);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void indentar (int ncolumnas);
//
//  USO:
//
//    Desplaza el cursor hacia la derecha mediante espacios en blanco.
//
//  DETALLES:
//
//    Utiliza un bucle for que se repite tantas veces como indique ncolumnas.
//    En cada iteración, imprime un carácter de espacio " " usando printf().
//    No mueve el cursor de forma absoluta, sino relativa a la posición actual.
//
//  PARÁMETROS DE ENTRADA:
//
//    ncolumnas
//
//      Variable entera que define cuántos espacios de indentación aplicar.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    printf()
//
//      Función estándar para imprimir los espacios.
//
////////////////////////////////////////////////////////////////////////////////

void indentar (int ncolumnas)
{
  for(int i=0; i<ncolumnas; i++)
  {
    printf(" ");   // No se puede usar "mostrar()" porque crearíamos un bucle de llamadas.
  }
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void derecha (int ncols);
//
//  USO:
//
//    Mueve el punto de inserción de texto hacia la derecha de la pantalla.
//
//  DETALLES:
//
//    Alias de indentar(). Se prefiere este nombre cuando la intención es
//    posicionar un elemento a una distancia horizontal concreta.
//
//  PARÁMETROS DE ENTRADA:
//
//    ncols
//
//      Número de columnas o espacios a avanzar hacia la derecha.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    indentar()
//
//      Ejecuta el bucle de impresión de espacios.
//
////////////////////////////////////////////////////////////////////////////////

void derecha (int ncols)
{
  indentar(ncols);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void tabular (int ncols);
//
//  USO:
//
//    Simula una tabulación horizontal personalizada.
//
//  DETALLES:
//
//    Llama a indentar() para imprimir espacios. A diferencia de un '\t'
//    estándar, permite definir con precisión cuántos espacios se avanzan.
//
//  PARÁMETROS DE ENTRADA:
//
//    ncols
//
//      Número de espacios que componen la tabulación.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    indentar()
//
//      Procesa la salida de espacios.
//
////////////////////////////////////////////////////////////////////////////////

void tabular (int ncols)
{
  indentar(ncols);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void desplazarCols (int ncols);
//
//  USO:
//
//    Desplaza el cursor horizontalmente el número de columnas indicado.
//
//  DETALLES:
//
//    Redirige la ejecución a indentar(). Se utiliza para el ajuste fino de
//    columnas en la interfaz de texto.
//
//  PARÁMETROS DE ENTRADA:
//
//    ncols
//
//      Cantidad de columnas a desplazar.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    indentar()
//
//      Genera el desplazamiento mediante espacios.
//
////////////////////////////////////////////////////////////////////////////////

void desplazarCols (int ncols)
{
  indentar(ncols);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void desplazarX (int ncols);
//
//  USO:
//
//    Desplaza la posición de escritura en el eje horizontal.
//
//  DETALLES:
//
//    Variante de indentar() orientada a sistemas de coordenadas donde X
//    representa la posición lateral (columnas).
//
//  PARÁMETROS DE ENTRADA:
//
//    ncols
//
//      Coordenada X relativa a la posición actual.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    indentar()
//
//      Encargada de la salida física de caracteres.
//
////////////////////////////////////////////////////////////////////////////////

void desplazarX (int ncols)
{
  indentar(ncols);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void desplazarH (int ncols);
//
//  USO:
//
//    Realiza un desplazamiento horizontal (H) del cursor.
//
//  DETALLES:
//
//    Función de alias para indentar(). Útil para documentar desplazamientos
//    en el plano horizontal.
//
//  PARÁMETROS DE ENTRADA:
//
//    ncols
//
//      Entero que indica los espacios horizontales a añadir.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    indentar()
//
//      Realiza la tarea de impresión.
//
////////////////////////////////////////////////////////////////////////////////

void desplazarH (int ncols)
{
  indentar(ncols);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void posicionar (int nfils, int ncols);
//
//  USO:
//
//    Sitúa el cursor en una ubicación relativa de filas y columnas.
//
//  DETALLES:
//
//    Combina las funciones bajar() y tabular() para mover el punto de
//    escritura. Primero genera los saltos de línea necesarios y luego
//    los espacios laterales.
//
//  PARÁMETROS DE ENTRADA:
//
//    nfils
//
//      Número de filas a bajar.
//
//    ncols
//
//      Número de columnas a tabular hacia la derecha.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    bajar()
//
//      Mueve el cursor verticalmente.
//
//    tabular()
//
//      Mueve el cursor horizontalmente.
//
////////////////////////////////////////////////////////////////////////////////

void posicionar (int nfils, int ncols)
{
  bajar(nfils);
  tabular(ncols);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void desplazar (int nfils, int ncols);
//
//  USO:
//
//    Efectúa un desplazamiento mixto (vertical y horizontal) del cursor.
//
//  DETALLES:
//
//    Alias de posicionar(). Se emplea para ajustar la ubicación del texto
//    antes de imprimir un mensaje o elemento gráfico.
//
//  PARÁMETROS DE ENTRADA:
//
//    nfils
//
//      Filas a descender.
//
//    ncols
//
//      Columnas a avanzar.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    posicionar()
//
//      Lleva a cabo la coordinación del movimiento.
//
////////////////////////////////////////////////////////////////////////////////

void desplazar (int nfils, int ncols)
{
  posicionar(nfils, ncols);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void desplazarXY (int nfils, int ncols);
//
//  USO:
//
//    Mueve el cursor a una posición definida por coordenadas relativas.
//
//  DETALLES:
//
//    Delega en posicionar(). El nombre enfatiza el uso de un plano de
//    dos dimensiones para ubicar el texto.
//
//  PARÁMETROS DE ENTRADA:
//
//    nfils
//
//      Referente a la coordenada Y (filas).
//
//    ncols
//
//      Referente a la coordenada X (columnas).
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    posicionar()
//
//      Efectúa los saltos y espacios.
//
////////////////////////////////////////////////////////////////////////////////

void desplazarXY (int nfils, int ncols)
{
  posicionar(nfils, ncols);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void retardoSegundos (int segundosmax);
//
//  USO:
//
//    Detiene la ejecución del programa durante un tiempo aproximado en segundos.
//
//  DETALLES:
//
//    Implementa la espera mediante bucles anidados de proceso (espera activa).
//    Es un método dependiente de la velocidad de la CPU y menos preciso que las
//    funciones de sistema, diseñado para entornos donde no se disponga de
//    librerías de tiempo estándar.
//
//  PARÁMETROS DE ENTRADA:
//
//    segundosmax
//
//      Cantidad de segundos (estimados) que durará la pausa.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    Ninguna.
//
////////////////////////////////////////////////////////////////////////////////

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


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void retardoMilisegundos (int milisegundosmax);
//
//  USO:
//
//    Pausa el programa durante un intervalo breve basado en milisegundos.
//
//  DETALLES:
//
//    Al igual que retardoSegundos, utiliza bucles de relleno para consumir
//    ciclos de reloj. La precisión depende totalmente del hardware.
//
//  PARÁMETROS DE ENTRADA:
//
//    milisegundosmax
//
//      Número de milisegundos (estimados) a esperar.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    Ninguna.
//
////////////////////////////////////////////////////////////////////////////////

void retardoMilisegundos (int milisegundosmax)
{
  int i, j;
  
  // AJUSTAR CEROS DE LOS BUCLES PARA APROXIMAR EL PERIODO.

  for (int nmiliseg=0; nmiliseg<milisegundosmax ; nmiliseg++)
    for (i=0; i<100; i++)
      for (j=0; j<1000; j++)   ;
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void retrasoMilisegundos (int milisegundos);
//
//  USO:
//
//    Genera una pausa precisa utilizando el reloj interno del sistema.
//
//  DETALLES:
//
//    Obtiene el tiempo inicial mediante clock() y entra en un bucle do-while
//    hasta que la diferencia de tiempo transcurrido (calculada en milisegundos)
//    alcanza el valor solicitado. Es mucho más preciso que los retardos por
//    bucle simple.
//
//  PARÁMETROS DE ENTRADA:
//
//    milisegundos
//
//      Tiempo de espera real en milisegundos.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    clock()
//
//      Función de "time.h" que devuelve los pulsos de reloj del procesador.
//
////////////////////////////////////////////////////////////////////////////////

void retrasoMilisegundos (int milisegundos)
{
  double e = 0;

  clock_t t0 = clock();   // clock_t es un tipo interno equivalente a UINT32.
  
  do
  {
    
    e = 1000*(double)(clock()-t0)/CLOCKS_PER_SEC;

  } while (e<milisegundos);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void esperarSegundos (int segundos);
//
//  USO:
//
//    Pausa la ejecución del hilo actual durante un tiempo determinado.
//
//  DETALLES:
//
//    Es una función multiplataforma que utiliza directivas de compilación.
//    En Windows invoca Sleep() (que usa milisegundos), y en otros sistemas
//    (como Linux/Unix) invoca sleep().
//
//  PARÁMETROS DE ENTRADA:
//
//    segundos
//
//      Entero que indica los segundos de pausa.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    Sleep() [Windows] / sleep() [Otros]
//
//      Funciones nativas del sistema operativo para gestionar el tiempo.
//
////////////////////////////////////////////////////////////////////////////////

void esperarSegundos (int segundos)
{
  #ifdef SO_WINDOWS
    Sleep(segundos*1000);
  #else
    sleep(segundos);
  #endif
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void esperarMilisegundos (int milisegundos);
//
//  USO:
//
//    Pausa la ejecución del programa durante los milisegundos indicados.
//
//  DETALLES:
//
//    Utiliza Sleep() en entornos Windows y usleep() en entornos POSIX. En
//    el caso de usleep(), se multiplica por 1000 ya que dicha función
//    trabaja con microsegundos.
//
//  PARÁMETROS DE ENTRADA:
//
//    milisegundos
//
//      Tiempo de pausa en milésimas de segundo.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    Sleep() / usleep()
//
//      Llamadas al sistema para suspender el proceso.
//
////////////////////////////////////////////////////////////////////////////////

void esperarMilisegundos (int milisegundos)
{
  #ifdef SO_WINDOWS
    Sleep(milisegundos);
  #else
    usleep(milisegundos*1000);   // Alternativa: nanosleep() de "time.h".
  #endif
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void pausa (void);
//
//  USO:
//
//    Detiene el flujo del programa en una posición estándar de la pantalla.
//
//  DETALLES:
//
//    Configura una pausa llamando a pausaEstandar() con coordenadas fijas (1, 2).
//    Es la forma más rápida de añadir un "Pulse INTRO" común.
//
//  PARÁMETROS DE ENTRADA:
//
//    Ninguno.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    pausaEstandar()
//
//      Gestiona la visualización del mensaje en la posición definida.
//
////////////////////////////////////////////////////////////////////////////////

void pausa (void)
{
  pausaEstandar(1, 2);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void pausaEstandar (int nfils, int ncols);
//
//  USO:
//
//    Muestra el mensaje de pausa por defecto en las coordenadas dadas.
//
//  DETALLES:
//
//    Delega el trabajo a pausaGenerica() enviando la macro MSJxPAUSA.
//    No añade una línea nueva automáticamente al final.
//
//  PARÁMETROS DE ENTRADA:
//
//    nfils
//
//      Filas de desplazamiento antes del mensaje.
//
//    ncols
//
//      Columnas de desplazamiento (indentación).
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    pausaGenerica()
//
//      Encargada de imprimir y esperar la entrada del usuario.
//
////////////////////////////////////////////////////////////////////////////////

void pausaEstandar (int nfils, int ncols)
{
  pausaGenerica(MSJxPAUSA, nfils, ncols, FALSE);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void pausaGenerica (char msjtxt[], int nfils, int ncols, boolean nuevalinea);
//
//  USO:
//
//    Crea una pausa personalizada con un mensaje y posición específicos.
//
//  DETALLES:
//
//    Combina la impresión de un mensaje formateado (usando mensaje_x_y)
//    y la detención del programa hasta que se pulsa una tecla (usando
//    esperarINTRO).
//
//  PARÁMETROS DE ENTRADA:
//
//    msjtxt
//
//      Cadena de texto con el mensaje de pausa.
//
//    nfils / ncols
//
//      Coordenadas de ubicación del mensaje.
//
//    nuevalinea
//
//      Booleano que indica si se debe saltar de línea tras el mensaje.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    mensaje_x_y()
//
//      Muestra el texto en pantalla.
//
//    esperarINTRO()
//
//      Detiene el programa hasta la pulsación de INTRO.
//
////////////////////////////////////////////////////////////////////////////////

void pausaGenerica (char msjtxt[], int nfils, int ncols, boolean nuevalinea)
{
  mensaje_x_y(msjtxt, nfils, ncols, nuevalinea);

  esperarINTRO();
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void texto (char msjtxt[]);
//
//  USO:
//
//    Imprime una cadena de texto seguida de un salto de línea.
//
//  DETALLES:
//
//    Encapsula la función puts(). Es útil para simplificar la sintaxis
//    de salida de cadenas de caracteres simples.
//
//  PARÁMETROS DE ENTRADA:
//
//    msjtxt
//
//      Cadena de caracteres a mostrar.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    puts()
//
//      Función estándar para imprimir cadenas con salto de línea.
//
////////////////////////////////////////////////////////////////////////////////

void texto (char msjtxt[])
{
  puts(msjtxt);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void separar();
//
//  USO:
//
//    Introduce un salto de línea visual en la salida.
//
//  DETALLES:
//
//    Llama a mostrar() enviando el carácter especial '\n'. Sirve para
//    dar aire o espacio entre diferentes bloques de texto.
//
//  PARÁMETROS DE ENTRADA:
//
//    Ninguno.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    mostrar()
//
//      Efectúa la salida del carácter de salto de línea.
//
////////////////////////////////////////////////////////////////////////////////

void separar()
{
  mostrar("\n");
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void nuevaLinea (void);
//
//  USO:
//
//    Genera un único salto de línea.
//
//  DETALLES:
//
//    Alias de saltar(1). Proporciona una forma semántica de indicar que
//    se desea pasar a la siguiente línea de escritura.
//
//  PARÁMETROS DE ENTRADA:
//
//    Ninguno.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    saltar()
//
//      Ejecuta el desplazamiento vertical.
//
////////////////////////////////////////////////////////////////////////////////

void nuevaLinea (void)
{
  saltar(1);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void mostrar (char msjtxt[]);
//
//  USO:
//
//    Imprime un mensaje en la posición actual del cursor.
//
//  DETALLES:
//
//    Delega en mostrar_x_y() enviando coordenadas 0, 0. Es la función base
//    para imprimir texto sin desplazamientos adicionales.
//
//  PARÁMETROS DE ENTRADA:
//
//    msjtxt
//
//      Texto que se desea visualizar.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    mostrar_x_y()
//
//      Gestiona la impresión con parámetros de posición.
//
////////////////////////////////////////////////////////////////////////////////

void mostrar (char msjtxt[])
{
  mostrar_x_y (msjtxt, 0, 0);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void mostrar_x_y (char msjtxt[], int nfils, int ncols);
//
//  USO:
//
//    Muestra un texto tras desplazar el cursor a las coordenadas indicadas.
//
//  DETALLES:
//
//    Encapsula a mensaje_x_y() con el parámetro nuevalinea desactivado.
//    Permite ubicar texto en cualquier punto relativo de la pantalla.
//
//  PARÁMETROS DE ENTRADA:
//
//    msjtxt
//
//      Cadena a mostrar.
//
//    nfils / ncols
//
//      Desplazamiento vertical y horizontal.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    mensaje_x_y()
//
//      Realiza la logística de posicionamiento e impresión.
//
////////////////////////////////////////////////////////////////////////////////

void mostrar_x_y (char msjtxt[], int nfils, int ncols)
{
  mensaje_x_y (msjtxt, nfils, ncols, FALSE);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void escribir (char msjtxt[]);
//
//  USO:
//
//    Alias para la impresión simple de texto.
//
//  DETALLES:
//
//    Llama a escribir_x_y() con origen 0, 0. Se provee para compatibilidad
//    con diferentes estilos de programación.
//
//  PARÁMETROS DE ENTRADA:
//
//    msjtxt
//
//      Cadena de caracteres.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    escribir_x_y()
//
//      Procesa la salida de datos.
//
////////////////////////////////////////////////////////////////////////////////

void escribir (char msjtxt[])
{
  escribir_x_y (msjtxt, 0, 0);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void escribir_x_y (char msjtxt[], int nfils, int ncols);
//
//  USO:
//
//    Escribe texto en coordenadas relativas específicas.
//
//  DETALLES:
//
//    Alias de mostrar_x_y(). Utiliza mensaje_x_y() para realizar la
//    tarea efectiva de dibujo en la consola.
//
//  PARÁMETROS DE ENTRADA:
//
//    msjtxt / nfils / ncols
//
//      Texto y coordenadas de destino.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    mensaje_x_y()
//
//      Función central de salida de texto formateado.
//
////////////////////////////////////////////////////////////////////////////////

void escribir_x_y (char msjtxt[], int nfils, int ncols)
{
  mensaje_x_y (msjtxt, nfils, ncols, FALSE);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void imprimir (char msjtxt[]);
//
//  USO:
//
//    Salida de texto por pantalla.
//
//  DETALLES:
//
//    Nueva variante de alias que llama a imprimir_x_y(0,0).
//
//  PARÁMETROS DE ENTRADA:
//
//    msjtxt
//
//      Texto a imprimir.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    imprimir_x_y()
//
//      Delega la impresión.
//
////////////////////////////////////////////////////////////////////////////////

void imprimir (char msjtxt[])
{
  imprimir_x_y (msjtxt, 0, 0);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void imprimir_x_y (char msjtxt[], int nfils, int ncols);
//
//  USO:
//
//    Imprime texto con control de posición.
//
//  DETALLES:
//
//    Alias de mostrar_x_y(). Se integra con mensaje_x_y() para la salida.
//
//  PARÁMETROS DE ENTRADA:
//
//    msjtxt / nfils / ncols
//
//      Datos de mensaje y posición.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    mensaje_x_y()
//
//      Gestión de salida por pantalla.
//
////////////////////////////////////////////////////////////////////////////////

void imprimir_x_y (char msjtxt[], int nfils, int ncols)
{
  mensaje_x_y (msjtxt, nfils, ncols, FALSE);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void mensaje (char msjtxt[], int nfils, int ncols);
//
//  USO:
//
//    Muestra un mensaje informativo en pantalla.
//
//  DETALLES:
//
//    Alias de mostrar_x_y(). Muy utilizado para clarificar que el texto
//    impreso es un aviso o notificación para el usuario.
//
//  PARÁMETROS DE ENTRADA:
//
//    msjtxt / nfils / ncols
//
//      Contenido y ubicación.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    mensaje_x_y()
//
//      Ejecuta la acción de impresión.
//
////////////////////////////////////////////////////////////////////////////////

void mensaje (char msjtxt[], int nfils, int ncols)
{
  mensaje_x_y (msjtxt, nfils, ncols, FALSE);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void mensaje_x_y (char msjtxt[], int nfils, int ncols, boolean nuevalinea);
//
//  USO:
//
//    Función integral para imprimir texto con formato de posición y fin de línea.
//
//  DETALLES:
//
//    Es la función maestra de salida. Primero invoca saltar() y tabular()
//    para posicionar el cursor. Luego imprime la cadena mediante printf().
//    Finalmente, si nuevalinea es TRUE, imprime un salto de línea adicional.
//
//  PARÁMETROS DE ENTRADA:
//
//    msjtxt
//
//      Cadena a visualizar.
//
//    nfils / ncols
//
//      Parámetros de desplazamiento vertical y horizontal.
//
//    nuevalinea
//
//      Controla si se añade '\n' al final de la cadena.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    saltar(), tabular(), printf()
//
//      Coordinan el posicionamiento y la salida de datos.
//
////////////////////////////////////////////////////////////////////////////////

void mensaje_x_y (char msjtxt[], int nfils, int ncols, boolean nuevalinea)
{
  saltar(nfils);
  tabular(ncols);
  printf("%s", msjtxt);
  
  if (nuevalinea)   printf("\n");   // ALTERNATIVA: if (nuevalinea)   putchar(ENTER);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    void iniciaAleatorizador (void);
//
//  USO:
//
//    Inicializa la semilla para la generación de números aleatorios.
//
//  DETALLES:
//
//    Utiliza srand() pasando como semilla el tiempo actual del sistema
//    obtenido mediante time(NULL). Esto garantiza que la secuencia de
//    números sea diferente en cada ejecución del programa.
//
//  PARÁMETROS DE ENTRADA:
//
//    Ninguno.
//
//  VALOR DE SALIDA:
//
//    No devuelve ningún valor.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    srand(), time()
//
//      Funciones estándar para gestión de azar y tiempo.
//
////////////////////////////////////////////////////////////////////////////////

void iniciaAleatorizador (void)
{
  srand(time(NULL));
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    int generaAleatorioEntero (int limite);
//
//  USO:
//
//    Genera un número entero al azar dentro de un rango.
//
//  DETALLES:
//
//    Utiliza rand() y el operador módulo para obtener un valor entre 0
//    y (limite - 1). Requiere que el aleatorizador haya sido inicializado
//    previamente para ser efectivo.
//
//  PARÁMETROS DE ENTRADA:
//
//    limite
//
//      Valor entero que define el techo (excluido) del rango aleatorio.
//
//  VALOR DE SALIDA:
//
//    Devuelve el entero generado.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    rand()
//
//      Función estándar que devuelve un número pseudoaleatorio.
//
////////////////////////////////////////////////////////////////////////////////

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
//    NINGUNO
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


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    char obtenerCaracterASCII();
//
//  USO:
//
//    Captura un carácter desde el teclado.
//
//  DETALLES:
//
//    Alias de obtenerLetra(). Se utiliza cuando el contexto del programa
//    requiere explícitamente trabajar con códigos ASCII.
//
//  PARÁMETROS DE ENTRADA:
//
//    Ninguno.
//
//  VALOR DE SALIDA:
//
//    Devuelve el carácter capturado.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    obtenerLetra()
//
//      Realiza la lectura y validación del carácter.
//
////////////////////////////////////////////////////////////////////////////////

char obtenerCaracterASCII()
{
  return obtenerLetra();
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    char obtenerLetra (void);
//
//  USO:
//
//    Lee una única letra del teclado asegurando que sea un código ASCII estándar.
//
//  DETALLES:
//
//    Utiliza getchar() para leer. Si el código es superior a 127, lo descarta
//    devolviendo un carácter nulo. Además, limpia el buffer de teclado si el
//    carácter leído no fue un INTRO, evitando acumulaciones de basura.
//
//  PARÁMETROS DE ENTRADA:
//
//    Ninguno.
//
//  VALOR DE SALIDA:
//
//    La letra capturada o '\0' si no es ASCII válido.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    getchar(), vaciarBuffer()
//
//      Lectura de caracteres y limpieza de flujos respectivamente.
//
////////////////////////////////////////////////////////////////////////////////

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


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    int pedirEnteroPositivo (char msjtxt[], int ncols, boolean mostrarerror);
//
//  USO:
//
//    Solicita un número entero por teclado, obligando a que sea mayor o igual a 0.
//
//  DETALLES:
//
//    Implementa un bucle do-while que no finaliza hasta que el valor sea válido.
//    Si el usuario introduce un número negativo y mostrarerror es TRUE, se
//    visualiza el mensaje de error global MSJxERROR. Utiliza obtenerEntero()
//    para garantizar un buffer limpio.
//
//  PARÁMETROS DE ENTRADA:
//
//    msjtxt / ncols
//
//      Mensaje descriptivo y su indentación.
//
//    mostrarerror
//
//      Indicador booleano para activar o desactivar avisos de error visuales.
//
//  VALOR DE SALIDA:
//
//    El número entero positivo validado.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    mensaje(), mostrar(), obtenerEntero(), nuevaLinea(), mensaje_x_y()
//
//      Coordinan la interfaz de usuario y la entrada de datos.
//
////////////////////////////////////////////////////////////////////////////////

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


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    int pedirEnteroIntervalo (char msjtxt[], int ncols, boolean mostrarerror, int min, int max);
//
//  USO:
//
//    Solicita un entero asegurando que se encuentre entre dos valores límites.
//
//  DETALLES:
//
//    Repite la petición del dato mientras el valor introducido esté fuera del
//    rango [min, max]. Muestra los límites al usuario en el mensaje de
//    petición y opcionalmente gestiona avisos de error.
//
//  PARÁMETROS DE ENTRADA:
//
//    msjtxt / ncols / mostrarerror
//
//      Parámetros de mensaje, posición y gestión de errores.
//
//    min / max
//
//      Valores entero que definen el intervalo de aceptación (ambos incluidos).
//
//  VALOR DE SALIDA:
//
//    Entero validado dentro del intervalo.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    mensaje(), printf(), obtenerEntero(), mensaje_x_y()
//
//      Gestionan la interacción con el usuario.
//
////////////////////////////////////////////////////////////////////////////////

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


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    int pedirLetra (char msjtxt[], int ncols, boolean mostrarerror, char letra);
//
//  USO:
//
//    Fuerza al usuario a pulsar una tecla específica para continuar.
//
//  DETALLES:
//
//    Convierte tanto la letra esperada como la pulsada a mayúsculas para evitar
//    problemas de sensibilidad. Útil para controles de flujo donde solo se
//    permite una acción concreta.
//
//  PARÁMETROS DE ENTRADA:
//
//    msjtxt / ncols / mostrarerror
//
//      Configuración del mensaje y error.
//
//    letra
//
//      El carácter exacto que se espera recibir.
//
//  VALOR DE SALIDA:
//
//    El carácter validado (en mayúsculas).
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    toupper(), obtenerLetra(), mensaje_x_y()
//
//      Normalización y toma de datos.
//
////////////////////////////////////////////////////////////////////////////////

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


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    int pedirConfirmacion (char msjtxt[], int ncols, boolean mostrarerror);
//
//  USO:
//
//    Realiza una pregunta de tipo SÍ o NO al usuario.
//
//  DETALLES:
//
//    Muestra las opciones SI/NO configuradas globalmente. No permite salir del
//    bucle hasta que se reciba una de estas dos letras. Normaliza la entrada
//    a mayúsculas.
//
//  PARÁMETROS DE ENTRADA:
//
//    msjtxt / ncols / mostrarerror
//
//      Mensaje, posición y control de errores.
//
//  VALOR DE SALIDA:
//
//    El carácter correspondiente a la elección (SI o NO).
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    obtenerLetra(), toupper(), mensaje_x_y()
//
//      Lógica de captura y validación.
//
////////////////////////////////////////////////////////////////////////////////

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


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    boolean validarLetraUnica (char original, char dada, boolean sensibleamayusculas);
//
//  USO:
//
//    Compara dos caracteres para verificar si son idénticos.
//
//  DETALLES:
//
//    Permite decidir mediante un booleano si la comparación debe ignorar o no
//    la diferencia entre mayúsculas y minúsculas (sensibleamayusculas). Si es
//    FALSE, ambos caracteres se normalizan con toupper() antes de comparar.
//
//  PARÁMETROS DE ENTRADA:
//
//    original / dada
//
//      Los dos caracteres a contrastar.
//
//    sensibleamayusculas
//
//      Flag para activar/desactivar la distinción de caja.
//
//  VALOR DE SALIDA:
//
//    TRUE si son iguales, FALSE en caso contrario.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    toupper()
//
//      Para la normalización de caracteres.
//
////////////////////////////////////////////////////////////////////////////////

boolean validarLetraUnica (char original, char dada, boolean sensibleamayusculas)
{
  if (!sensibleamayusculas)
  {
    original = toupper(original);
      dada   = toupper(dada);
  }
  
  return (original == dada);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    boolean validarLetraConjunto (char letra, char seleccion[], boolean sensibleamayusculas);
//
//  USO:
//
//    Comprueba si un carácter pertenece a un grupo de caracteres válidos.
//
//  DETALLES:
//
//    Recorre la cadena seleccion[] y utiliza validarLetraUnica() para cada
//    elemento. Si encuentra una coincidencia, detiene la búsqueda y confirma
//    la validez.
//
//  PARÁMETROS DE ENTRADA:
//
//    letra
//
//      Carácter a validar.
//
//    seleccion[]
//
//      Cadena que contiene todos los caracteres aceptados.
//
//    sensibleamayusculas
//
//      Control de distinción de mayúsculas.
//
//  VALOR DE SALIDA:
//
//    TRUE si la letra está en el conjunto, FALSE si no.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    strlen(), validarLetraUnica()
//
//      Cálculo de longitud y comparación individual.
//
////////////////////////////////////////////////////////////////////////////////

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


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    char *cadenaOpcionesDisponibles (char entrada[]);
//
//  USO:
//
//    Formatea una cadena de opciones separándolas por barras laterales.
//
//  DETALLES:
//
//    Toma una cadena como "ABC" y genera dinámicamente una nueva cadena como
//    "A/B/C". Reserva memoria mediante malloc(), por lo que el llamador es
//    responsable de liberar dicha memoria con free() posteriormente.
//
//  PARÁMETROS DE ENTRADA:
//
//    entrada[]
//
//      Cadena original con las opciones compactas.
//
//  VALOR DE SALIDA:
//
//    Puntero a la nueva cadena formateada o NULL si hay error.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    strlen(), malloc()
//
//      Gestión de cadenas y memoria dinámica.
//
////////////////////////////////////////////////////////////////////////////////

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


////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    int pedirLetraSeleccion (char msjtxt[], int ncols, boolean mostrarerror, char seleccion[], boolean sensibleamayusculas);
//
//  USO:
//
//    Solicita al usuario una letra que debe pertenecer a un conjunto dado.
//
//  DETALLES:
//
//    Muestra el mensaje junto con las opciones válidas formateadas (ej: [A/B/C]).
//    Utiliza cadenaOpcionesDisponibles para el formato visual y
//    validarLetraConjunto para la lógica de aceptación. Se encarga de liberar
//    la memoria dinámica utilizada para el mensaje de opciones.
//
//  PARÁMETROS DE ENTRADA:
//
//    msjtxt / ncols / mostrarerror
//
//      Configuración estándar de interfaz.
//
//    seleccion[]
//
//      Cadena con los caracteres permitidos.
//
//    sensibleamayusculas
//
//      Determina si discrimina entre 'a' y 'A'.
//
//  VALOR DE SALIDA:
//
//    La letra elegida y validada.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    cadenaOpcionesDisponibles(), mensaje(), mostrar(), obtenerLetra(),
//    validarLetraConjunto(), free()
//
//      Coordinan el flujo completo de petición y validación.
//
////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    char obtenerTeclaInteractiva(void); [WINDOWS]
//
//  USO:
//
//    Detecta pulsaciones de teclado en tiempo real sin esperar a pulsar INTRO.
//
//  DETALLES:
//
//    Específica para Windows. Utiliza _getch() de conio.h. Gestiona teclas
//    especiales (flechas) que devuelven secuencias de dos códigos (0 o 224),
//    traduciéndolas a macros constantes como TECLA_ARRIBA.
//
//  PARÁMETROS DE ENTRADA:
//
//    Ninguno.
//
//  VALOR DE SALIDA:
//
//    El código de la tecla pulsada o una macro representativa.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    _getch()
//
//      Función de sistema para lectura de teclado sin buffer.
//
////////////////////////////////////////////////////////////////////////////////

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
  }
  else
  {
    // Normalización de teclas conflictivas no estándar.
    switch(caracter)
    {
      case 13: caracter = TECLA_ENTER;     break;
      case 8:  caracter = TECLA_RETROCESO; break;
    }
  }
    
  return (char)caracter;
}

#else

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
//
//  FUNCIÓN:
//
//    int obtenerTeclaInteractiva(void);
//
//  USO:
//
//    Captura teclas de forma inmediata en entornos Unix/Linux.
//
//  DETALLES:
//
//    Modifica temporalmente la configuración de la terminal (termios) para
//    desactivar el modo canónico y el eco. Gestiona secuencias de escape de
//    flechas (ESC + '[' + código) y restaura la terminal al finalizar.
//
//  PARÁMETROS DE ENTRADA:
//
//    Ninguno.
//
//  VALOR DE SALIDA:
//
//    Código de tecla o macro de dirección/especial.
//
//  FUNCIONES DE LAS QUE DEPENDE:
//
//    tcgetattr(), tcsetattr(), getchar(), fcntl()
//
//      Control de hardware de terminal y lectura de descriptores de archivo.
//
////////////////////////////////////////////////////////////////////////////////

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
    fcntl(STDIN_FILENO, fSETFL, flags);
  }

  // 4. Restauramos la configuración original antes de salir.
  tcsetattr(STDIN_FILENO, TCSANOW, &terminaloriginal);
  
  return caracter;
}

#endif

// He tenido que buscar mucho en internet para averiguar como hacer estos programas, aunque creo que algunas cosas son un poco inventadas