! Mensajes de librer�a.
!
! N�mero de Serie: 080625
!
! A partir de la revisi�n [001115], los mensajes de librer�a van en
! fichero aparte para hacer m�s f�cil su redefinici�n.
!
! Recuerda hacer una copia de este fichero, con el nombre
! Mensajes_originales.h por ejemplo, antes de modificarlo.
!
! Puedes tener diferentes ficheros de mensajes (Mensajes_graciosos.h,
! Mensajes_primera_persona.h, etc.) pero el que ser� incluido en el
! juego por defecto ser� el llamado Mensajes.h (si quieres usar otro,
! incl�yelo en tu c�digo antes de incluir Gramatica.h)
!
! --------IMPORTANTE--------------------
! Recuerda que si s�lo vas a redefinir unos pocos mensajes y no todos,
! es mejor usar el mecanismo de "MensajesLibreria". Este mecanismo
! consiste en escribir un objeto llamado MensajesLibreria antes de
! Include "Acciones", y en la rutina antes de ese objeto capturar las
! acciones para las cuales quieres cambiar el mensaje. Por ejemplo,
! para cambiar el mensaje "Cantas fatal", que se genera por defecto
! ante la acci�n cantar, pondr�as:
!
!  Object MensajesLibreria
!  with antes [;
!           Cantar:  "T�o, la m�sica no es lo tuyo.";
!       ];
!
!  Algunas acciones generan diferentes mensajes seg�n el caso. Por
!  ejemplo, la acci�n Coger puede generar:
!   - Cogido (en caso de �xito)
!   - Siempre te tienes a ti mismo (en caso de COGETE)
!   - No creo que Pepe le gustara (en caso de COGE PEPE)
!   - Ya tienes el hacha (en caso de que ya tenga el objeto)
!  etc...
!
!  En la variable ml_n se guarda un numero que indica cu�l de los
!  mensajes anteriores debe ser mostrado. Por otra parte, en la
!  variable ml_o se guarda el objeto que debe ser nombrado en el
!  mensaje. As�, para cambiar los cuatro mensajes anteriores desde
!  MensajesLibreria deber�amos hacer un switch sobre la variable ml_n
!  para elegir el mensaje adecuado, y usar el objeto ml_o como parte
!  del mensaje. Por ejemplo:
!
!   Object MensajesLibreria
!   with  antes [;
!           Cantar: "T�o, lo tuyo no es la m�sica.";
!           Coger: switch (ml_n)
!                  {
!                    1: print_ret "Vale, pillad", (o) ml_o, ".";
!                    2: print_ret "�Pero c�mo vas a ", (coge) "rte a ti mismo,
!                       mel�n!";
!                    3: print_ret (_El) ml_o, " no se deja", (n) ml_o,
!                       ".";
!                    5: print_ret "�Pero si ya ", (lo) ml_o, "
!                       tienes!";
!                  }
!          ];
!
! Observa como se usa (o) ml_o para imprimir "o", "a", "os" o "as"
! seg�n el g�nero y n�mero del objeto. (n) ml_o imprime una "n" o
! nada, seg�n el n�mero del objeto (por ejemplo: El perro no se deja,
! y Las abejas no se dejan). (lo) ml_o imprime "lo" "la" "los" o
! "las".
!
! Si vas a cambiar muchos mensajes, el sistema de MensajesLibreria
! sigue siendo v�lido, pero consume m�s memoria. Puedes entrar a
! modificar directamente este fichero Mensajes.h
!
! Tambi�n puedes usar este fichero como fuente de informaci�n para
! saber los diferentes valores de ml_n asociados con cada acci�n y el
! mensaje m�s apropiado para cada caso.
!
! La funci�n se halla profusamente comentada para ayudarte a saber
! cu�ndo se genera cada mensaje.

! Movido aqu� en [020415]

Constant HAY__TX      = " ves";
Constant HAYP__TX     = " ves";
Constant HAY2__TX     = "ves ";
Constant HAYP2__TX    = "ves ";

! A�adido en [020804]

Constant PARTICULA_TE = "te";

!****************************************************************
! DEFINICI�N DE MENSAJES DE LIBRER�A
!****************************************************************
! Esta rutina engloba todas las respuestas por defecto a todas las
! acciones de librer�a, as� como los mensajes de error del parser y
! otras cadenas de texto que el parser necesita mostrar a veces.
!
! Sus contenidos pueden agruparse en cuatro grandes categor�as:
!
!  1) Mensajes de las acciones que no hacen nada. Son meros mensajes
!  del estilo de "no ocurre nada", pero adaptados para cada posible
!  acci�n. Son muy f�ciles de redefinir.
!
!  2) Mensajes de las acciones que hacen cosas. En este caso hay
!  mensajes de �xito o de error, seg�n la acci�n haya podido
!  realizarse o no. Ten en cuenta que el mensaje de �xito no se
!  imprimir� si el objeto lo impide en su rutina "despues".
!  Son bastante f�ciles de modificar, gui�ndote por los comentarios.
!
!  3) Mensajes de los metacomandos (como SAVE, LOAD...) No creo que
!  merezca la pena cambiarlos.
!
!  4) Mensajes "Miscelanea", donde est�n todos los errores de parsing
!  y otros. Algunos son f�ciles de cambiar, otros son m�s complejos.

[ MLIdioma ml_n ml_o;
  Prompt:
    print "^>";
    ! El prompt aparece justo antes de pedir una nueva l�nea al
    ! jugador. Puede definirse para que sea una frase, o se genere una
    ! frase aleatoria en cada turno.


!====================================================
! ACCIONES QUE NO HACEN NADA
!====================================================
! Las siguientes acciones generan un texto como respuesta, pero no
! cambian el estado del juego. No mueven objetos.

  Quemar:        "Con esa peligrosa acci�n no lograr�as nada.";
  Rezar:         "No obtienes nada pr�ctico de tus oraciones.";
  Despertarse:   "La cruda realidad es que esto no es un sue�o.";
  DespertarOtro: "No parece necesario hacer eso.";
  Besar:         "No creo que debas.";
  Pensar:        "Vaya. Qu� buena idea.";
  Oler:          "No hueles nada extra�o.";
  Escuchar:      "No escuchas nada fuera de lo com�n.";
  Probar:        "No saboreas nada inesperado.";
  Tocar:
    ! Tocar genera tres mensajes diferentes
    !  1: Si se intenta tocar a un ser animado
    !  2: Tocar un objeto normal del juego
    !  3: Tocarse a si mismo
    switch(ml_n)
    {
      1: "�Las manos quietas!";
      2: "No notas nada extra�o al tacto.";
      3: "Si crees que eso servir� de algo...";
    }
  Excavar:     "Excavar no servir� de nada aqu�.";
  Cortar:      "Cort�ndo", (lo) ml_o, " no lograr�s gran cosa.";
  Saltar:      "Saltas en el sitio, sin ning�n resultado.";
  SaltarSobre, ! SaltarSobre y Atar generan el mismo mensaje
  Atar:        "No lograr�s nada as�.";
  Beber:       "Eso no parece potable.";
  Llenar:      "No puedes llenar", (lo) ml_o, ".";

  LoSiento:    "Oh, no es necesario que te disculpes.";
  ! Esta acci�n se genera si el jugador pone "LO SIENTO",
  ! "PERDONA" o cosas similares.

  Tacos:       "Los verdaderos aventureros no usan ese vocabulario.";
  ! Y esta si usa como primera palabra (verbo) un taco.

  Soso:        "Bastante.";
  ! Y esta si usa como primera palabra alg�n insulto m�s suave

  Si, No:      "S�lo era una pregunta ret�rica.";
  ! Cuando el jugador pone SI o NO, a secas, se genera esta
  ! acci�n. Est� pensado por si el juego suelta una frase del estilo
  ! de "�Pero t� eres tonto?" y el jugador responde NO.
  ! De todas formas, hay un problema, y es que NO es normalmente la
  ! acci�n Ir al noroeste. Si queremos que NO sea provisionalmente
  ! la acci�n No, entonces el juego debe poner un 1 en la variable
  ! PreguntaSiNo, antes de escribir el texto "�Pero t� eres tonto?".
  ! En este caso, el parser interpretar� "NO" como la acci�n No,
  ! pero s�lo en el siguiente turno. Despu�s recuperar� su antiguo
  ! significado de Ir al Noroeste.

  Atacar:      "La violencia no es la soluci�n.";
  ! La acci�n atacar se genera tambi�n al intentar "romper" objetos

  Nadar:       "No hay agua suficiente en la que nadar.";
  Columpiar:   "No es adecuad", (o) ml_o, " para columpiarse.";
  Soplar:      "Tu soplido no produce ning�n efecto.";
  Frotar:      "Ya ", (esta) ml_o, " bastante limpi", (o) ml_o, ".";

  Fijar:       "No, no puedes.";
  ! Fijar sale ante la frase FIJA OBJETO o AJUSTA OBJETO

  PonerA:      "Eso no puede regularse a ning�n valor.";
  ! PonerA sale ante la frase AJUSTA DIAL A 23 o FIJA CONTROL EN
  ! ACTIVADO, o PON REGULADOR A 30

  Gesticular:  "Te ves rid�cul", (o) jugador, " gesticulando as�.";
  ! La acci�n Gesticular sale ante las frases "gesticula", "agita la
  ! mano", "sacude la mano", "saluda con la mano"...

  Agitar:
  ! Agitar genera dos mensajes diferentes:
  !  1: Si se intenta agitar un objeto que no est� en el inventario
  !  2: Si se agita un objeto que s� est� en el inventario
    switch (ml_n)
    {
      1: "No l",(o) ml_o, " tienes.";
      2: "Te sientes rid�cul", (o) jugador, " agitando ", (el) ml_o, ".";
    }

  Tirar, Empujar, Girar:
  ! Las acciones Tirar, Empujar y Girar generan todas ellas los
  ! mismos mensajes, pero pueden darse 4 casos:
  !   1: Que el objeto tenga el atributo 'estatico'
  !   2: Que el objeto tenga el atributo 'escenario'
  !   3: El objeto no tiene 'estatico' ni 'escenario'
  !   4: El objeto es un ser animado
  ! [Nota, si el objeto tiene ambos 'estatico' y 'escenario' se
  ! est� tambi�n en el caso 1]
    switch(ml_n)
    {
      1: "Est�", (n)ml_o, " firmemente sujet", (o)ml_o, ".";
      2: "No eres capaz.";
      3: "No ocurre nada, aparentemente.";
      4: "Eso ser�a, como poco, maleducado.";
    }

  EmpujarDir:
  ! La acci�n EmpujarDir se genera ante frases como EMPUJA EL COCHE
  ! HACIA EL NORTE. Hay 3 casos posibles:
  !   1: Si el juego no ha previsto la posibilidad de empujar ese
  !      objeto hacia una direcci�n (o sea, no llama a la rutina
  !      PermitirEmujarDir). Esta es la respuesta por defecto m�s
  !      habitual.
  !   2: Si el jugador pone tras HACIA algo que no es una direcci�n.
  !      (respuesta por defecto en este caso)
  !   3: Si intenta empujar hacia arriba o hacia abajo
    switch(ml_n)
    {
     1: "No creo que empujar ", (el) ml_o, " sirva para nada.";
     2: "Eso no es una direcci�n.";
     3: "No, no puedes en esa direcci�n.";
    }

 Retorcer:
    ! Dos casos:
    !  1: Tratar de retorcer un ser animado
    !  2: Cualquier otro objeto
    switch(ml_n)
    {
     1: "�Las manos quietas!";
     2: "No consigues nada haciendo eso.";
    }
 Lanzar:
    ! Dos casos:
    !  1: Lanzar cosas a objetos inanimados
    !  2: Lanzar cosas a objetos animados
    switch(ml_n)
    {
     1: "No servir�a de nada.";
     2: "En el �ltimo momento te echas atr�s.";
    }

 MirarDebajo:
    ! Dos casos:
    !  1: Error, estamos a oscuras
    !  2: �xito, mensaje por defecto.
    switch(ml_n)
    {
     1: "Est� muy oscuro.";
     2: "No ves nada interesante.";
    }

! A�adido en la versi�n [020423]. Es utilizado por DireccionBrujula.
 MirarHacia:
   "No observas nada digno de menci�n al mirar hacia ", (el) ml_o, ".";

 Hablar:
    ! Dos casos:
    !  1: El jugador habla consigo mismo
    !  2: Hablar con cualquier otro ser animado
    ! [Nota: Hablar con un objeto inanimado no est� permitido por el
    ! parser, que da un error y no llega a generar la acci�n]
    ! [Los errores de parser se tratan en la secci�n "Miscelanea" de
    ! esta rutina, al final]
    switch(ml_n)
    {
     1: "Hablas sol", (o) jugador, " durante un rato.";
     2: "No has provocado ninguna reacci�n.";
    }
 Responder,
 Preguntar:      "No hay respuesta.";
 Orden:
    print_ret (_El) ml_o, " tiene", (n) ml_o, " mejores cosas que hacer.";
 Comprar:        "No hay nada en venta.";
 Cantar:         "Cantas fatal.";
 Trepar:         "No creo que vayas a lograr nada as�.";
 Esperar:        "Pasa el tiempo...";
 Dormir:         "No est�s especialmente somnolient", (o) jugador, ".";
 Consultar:      "No descubres nada interesante en ", (el) ml_o,
     " sobre ese tema.";

!==================================================================
! ACCIONES QUE HACEN ALGO
!==================================================================
! Las siguientes acciones pueden fracasar (dando un mensaje
! apropiado) o tener �xito. Si fracasan, se imprime un mensaje de error
! por defecto y no llega a modificarse el estado del juego
!
! Si tienen �xito, modificar�n el estado del juego de alg�n modo
! (activando alg�n atributo de alg�n objeto, o moviendo un objeto de
! una parte a otra). Tras el �xito, se llamar� a la rutina "despues"
! del objeto, y si �ste no imprime nada, entonces se imprimir� un
! mensaje de �xito de librer�a.
!
! Aqu� se definen tanto los mensajes de fracaso como los de �xito,
! pero no las acciones concretas que modifican el estado del juego
!

 Coger:
    ! Hay 13 casos diferentes. Se trata de 1 mensaje de �xito y 11
    ! mensajes de error y un aviso
    !  1: �xito
    !  2: Error, el objeto cogido es el propio jugador
    !  3: Error, el objeto cogido es animado
    !  4: Error, el jugador est� subido o metido en el objeto que
    !     intenta coger
    !  5: Error, el jugador ya ten�a ese objeto
    !  6: Error, el objeto est� en poder de un ser animado [ml_o
    !     apunta al ser, no al objeto, el cual puede obtenerse en la
    !     variable "uno"]
    !  7: Error, el objeto es un sub-objeto de otro (est� dentro de un
    !     objeto que tiene el atributo "transparente", pero no tiene el
    !     atributo "recipiente" ni "soporte")
    !  8: Error, el objeto est� dentro de otro, pero este otro no es
    !     recipiente ni soporte ni transparente (probablemente un error
    !     de programaci�n)
    !  9: Error, el objeto est� dentro de un recipiente cerrado.
    ! 10: Error, el objeto es escenario
    ! 11: Error, el objeto es estatico (no puede ser llevado de la
    !     localidad en que se halla)
    ! 12: Error, el jugador lleva demasiados objetos
    ! 13: Mensaje de aviso, la librer�a ha decidido mover objetos del
    !     inventario al "objeto saco" para hacer sitio y que el jugador
    !     pueda coger el objeto. [El objeto saco es uno que puede
    !     declarar el programador. Si el jugador lo coge y lo lleva
    !     consigo, la librer�a lo usar� autom�ticamente como mochila
    !     para descargar al jugador cuando sea necesario]
    switch(ml_n)
    {
     1: if (dialecto_sudamericano) print "Tomad";
     	else print "Cogid";
	print_ret (o) ml_o, ".";
     2: "Siempre te tienes a ti mism", (o) jugador, ".";
     3: "No creo que ", (al) ml_o, " le", (s) ml_o, " gustara.";
     4: print "Tienes que ";
	if (ml_o has soporte) print "bajarte "; else print "salirte ";
	print_ret (del) ml_o, " antes.";
     5: "Ya tienes ", (el) ml_o, ".";
     6:	"Parece que pertenece", (n) uno, " ", (al) ml_o, ".";
     7: "Parece", (n) ml_o, " formar parte ", (del) ml_o, ".";
     8: "No ", (esta) ml_o, " disponible", (s)ml_o, ".";
     9: print_ret (_El) ml_o, " no ", (esta) ml_o, " abiert", (o) ml_o, ".";
     10: "Dif�cilmente podr�as llevarte eso.";
     11: print_ret (_El) ml_o, " est� fij", (o) ml_o, " en el sitio.";
     12: "Ya llevas demasiadas cosas.";
     13: "(colocas ", (el) ml_o, " en ", (el) OBJETO_SACO,
	 " para hacer sitio)";
    }

 Dejar:
    ! 2 mensajes de error, 1 aviso y 1 de �xito:
    !   1: Error, el objeto dejado no est� en poder del jugador, pero
    !      est� en la localidad.
    !   2: Error, el objeto dejado no est� en poder del jugador ni en
    !      la localidad.
    !   3: Aviso, el objeto era una prenda que el jugador llevaba
    !      puesta y la librer�a va a quit�rsela autom�ticamente para
    !      poder dejarla.
    !   4: �xito
    switch(ml_n)
    {
     1: "Para dejar ", (el)ml_o, " deber�as tener", (lo) ml_o, ".";
     2: "No ", (lo) ml_o, " tienes.";
     3: "(primero te quitas ", (el) ml_o, ")";
     4: "Dejad", (o) ml_o, ".";
    }

 Sacar:
    ! 2 mensajes de error y 1 de �xito
    !   1: El recipiente que contiene el objeto que el jugador quiere
    !      sacar, est� cerrado. (ml_o apunta al objeto, no al
    !      recipiente, el cual puede obtenerse con parent(ml_o))
    !   2: El objeto no est� dentro del recipiente que el jugador ha
    !     dicho.
    !   3: �xito
    switch(ml_n)
    {
     1: "Por desgracia ", (el) parent(ml_o), " ",(esta) parent(ml_o),
	 " cerrad", (o) parent(ml_o), ".";
     2: if (otro has animado)
	 "�Pero si no ", (lo) ml_o, " tiene", (n) otro, "!";
	"�Pero si no ", (esta) ml_o, " ah� ahora!";
     3: if (palabra_verbo=='quita') "Quitad", (o)ml_o, ".";
	"Sacad", (o) ml_o, ".";
    }

 PonerSobre:
    ! 1: Error, el objeto no est� en poder del jugador. [Nota,
    !    conviene mirar en este caso si el objeto es animado o no,
    !    para generar un mensaje m�s adecuado]
    ! 2: Error, el jugador intenta poner un objeto sobre s� mismo
    ! 3: Error, el jugador intenta poner el objeto sobre otro que no
    !    tiene el atributo "soporte"
    ! 4: Error, el jugador intenta poner un objeto sobre el propio
    !    jugador.
    ! 5: Aviso, el objeto es una prenda puesta. La librer�a va a
    !    quit�rselo autom�ticamente antes de reintentar la acci�n
    !    PonerSobre
    ! 6: Error, se intenta poner el objeto sobre otro en el que ya no
    !    queda sitio (el n�mero de objetos que caben en el soporte se
    !    indica en su propiedad "capacidad")
    ! 7: �xito. Mensaje a mostrar para cada objeto puesto cuando se
    !    ponen muchos (ej: PON TODO SOBRE LA MESA)
    ! 8: �xito. Mensaje a mostrar cuando se pone un solo objeto sobre
    !    otro.
    switch(ml_n)
    {
     1: if (ml_o has animado)
	 "Antes tendr�as que ", (coge) "rl", (o) ml_o, ", y no s� si se dejar�",
	     (n) ml_o, ".";
	else
   	    "Necesitas tener ", (el) ml_o,
	 	" para poder poner", (lo) ml_o,
	 	" donde sea.";
     2: "No puedes poner un objeto sobre s� mismo.";
     3: "Poner cosas sobre ", (el) ml_o, " no servir� de nada.";
     4: "Te falta destreza.";
     5: "(primero te ", (lo) ml_o, " quitas)^";
     6: "No queda sitio en ", (el) ml_o, " para poner nada m�s.";
     7: "Hecho.";
     8: "Colocas ", (el) ml_o, " sobre ", (el) otro, ".";
    }

  Meter:
    ! 1: Error, el objeto no est� en poder del jugador. [Nota,
    !    conviene mirar en este caso si el objeto es animado o no,
    !    para generar un mensaje m�s adecuado]
    ! 2: Error, el jugador intenta meter el objeto en otro que no
    !    tiene el atributo "recipiente"
    ! 3: Error, el jugador intenta meter el objeto en un recipiente
    !    cerrado.
    ! 4: Error, el objeto es una prenda que el jugador lleva puesta.
    !    [ESTE MENSAJE NO SE GENERA NUNCA, PARECE UN BUG DE LA
    !    LIBRER�A. V�ase en su lugar el mensaje 6]
    ! 5: Error, se intenta poner un objeto dentro de s� mismo
    ! 6: Aviso, el objeto es una prenda puesta, la librer�a va a
    !    quit�rsela de forma autom�tica antes de reintentar Meter.
    ! 7: Error, no queda sitio en el recipiente (el n�mero de objetos
    !    que un recipiente puede contener se indica en su propiedad
    !    "capacidad").
    ! 8: �xito. Mensaje a mostrar para cada objeto metido cuando se
    !    meten muchos (ej: METE TODO EN LA BOLSA)
    ! 9: �xito. Mensaje a mostrar cuando se mete un solo objeto dentro
    !    de otro
    switch(ml_n)
    {
     1: if (ml_o has animado) "Antes tendr�as que ", (coge)"rl", (o) ml_o,
	 " y no s� si se dejar�",(n)ml_o,".";
	else
	"Necesitas tener ", (el) ml_o,
	 " para poder meter", (lo) ml_o,
	 " donde sea.";
     2: "No se pueden meter cosas dentro ", (del) ml_o, ".";
     3: print_ret (_El) ml_o, " ", (esta) ml_o, " cerrad", (o) ml_o, ".";
     4: "Tienes que quitarte", (lo) ml_o, " antes.";
     5: "No puedes poner un objeto dentro de s� mismo.";
     6: "(primero te ", (lo) ml_o, " quitas)^";
     7: "No queda sitio en ", (el) ml_o, ".";
     8: "Hecho.";
     9: "Metes ", (el) ml_o, " dentro ", (del) otro, ".";
    }

 Transferir:
    ! ESTOS MENSAJES NUNCA SON GENERADOS POR LA
    ! LIBRER�A. Probablemente se mantienen para compatibilidad.
    !  1: El objeto que el jugador menciona no est� en la localidad
    !  2: El objeto que el jugador menciona no est� en su poder (pero
    !     est� en la localidad)
    ! En lugar de estos mensajes, la librer�a intentar� una acci�n
    ! Coger, por lo que los mensajes generados est�n agrupados en la
    ! secci�n dedicada a Coger.
    switch(ml_n)
    {
     1: print_ret (_El) ml_o, "no est�",(n) ml_o, " a mano.";
     2: "Debes ", (coge)"r", " antes ", (el) ml_o, ".";
    }

  VaciarEn:
    ! 1: Error, el jugador intenta vaciar un objeto en otro que no es
    !    un recipiente.
    ! 2: Error, el jugador intenta vaciar un objeto sobre un
    !    recipiente cerrado.
    ! 3: Error, el jugador intenta vaciar un objeto que no tiene nada
    !    dentro.
    ! 4: Error, el jugador intenta vaciar un objeto sobre s� mismo.
    ! [NOTA: No hay mensajes de �xito para esta acci�n, ya que en caso
    ! de haber superado los test anteriores, la librer�a genera
    ! finalmente la acci�n Transferir, la cual a su vez, generar� la
    ! acci�n PonerSobre o Meter, seg�n el segundo objeto sea soporte o
    ! recipiente. Por tanto los mensajes de �xito ser�n los de las
    ! acciones PonerSobre o Meter.
    switch(ml_n)
    {
      1:
        print_ret (_El) ml_o, " no puede tener cosas dentro.";
      2:
        print_ret (_El) ml_o, " ", (esta) ml_o, " cerrad", (o) ml_o, ".";
      3:
        print_ret (_El) ml_o, " ya ", (esta) ml_o, " vac�", (o)ml_o, ".";
      4:
        "No puedes vaciar ", (el) ml_o, "sobre s�.";
    }

  Dar:
    ! 1: Error, el jugador intenta dar un objeto que no tiene
    ! 2: Error, el jugador se da el objeto a s� mismo
    ! 3: Aviso, se ha enviado la acci�n Dar al PNJ, pero este no ha
    !    respondido. En este caso ml_o apunta al PNJ y no al objeto
    !    que le hemos dado.
    ! [Observar que por defecto el objeto sigue en poder del
    ! jugador. Si queremos que el PNJ lo acepte, hay que programarlo
    ! como parte de su rutina Vida]
    switch(ml_n)
    {
     1: "No tienes ", (el) ml_o, ".";
     2: "Manoseas ", (el) ml_o,
	 " un ratito, pero no consigues gran cosa.";
     3: print_ret (_El) ml_o, " no parece", (n) ml_o, " interesad", (o)ml_o,
 ".";
    }

  Mostrar:
    ! 1: Error, el jugador intenta mostrar un objeto que no tiene.
    ! 2: Aviso, se ha enviado la acci�n Mostrar al PNJ, pero este no
    !    ha respondido. En este caso ml_n apunta al PNJ y no al objeto
    !    que le hemos mostrado.
    switch(ml_n)
    {
     1: "No tienes ", (el)ml_o, ".";
     2: print_ret (_El) ml_o, " no muestra", (n) ml_o, " inter�s.";
    }

  Meterse:
    ! CUIDADO. La acci�n Meterse se genera en muy diversas
    ! circunstancias: VETE HACIA EL PUENTE, VETE AL PUENTE, VETE POR
    ! EL PUENTE, PASA POR EL PUENTE, ENTRA EN EL PUENTE, ENTRA AL
    ! PUENTE, CRUZA EL PUENTE, CRUZA POR EL PUENTE, METETE EN EL
    ! PUENTE, METETE POR EL PUENTE, ATRAVIESA EL PUENTE, BAJA POR EL
    ! PUENTE.  Todas ellas generar�an la acci�n <Meterse Puente>
    !
    ! Adem�s, los intentos de entrar en un "entrable", tambi�n, como
    ! por ejemplo: SIENTATE EN EL BANCO, ECHATE EN EL BANCO, SUBETE AL
    ! BANCO, SUBETE EN EL BANCO, SUBE AL BANCO, SUBE POR EL BANCO,
    ! SALTA AL BANCO. Todas ellas generar�an <Meterse Banco>
    !
    ! Puesto que hay muchos verbos diferentes que dan lugar a la misma
    ! acci�n, es necesaria alguna forma de imprimir qu� verbo concreto
    ! ha sido el que la ha desencadenado, para poder generar mensajes
    ! como "No puedes entrar ah�", "No puedes sentarte ah�", "No
    ! puedes subirte ah�", etc.. seg�n el verbo usado. Para esto puede
    ! usarse una llamada a IdiomaVerbo(palabra_verbo). palabra_verbo
    ! contiene el verbo usado por el jugador (convertido en forma
    ! imperativa), y IdiomaVerbo lo que hace es imprimir la forma
    ! infinitiva.
    !
    ! Mensajes que puede generar esta acci�n:
    !  1: Error, el jugador ya est� en/sobre el objeto en cuesti�n
    !  2: Error, el objeto al que intenta entrar/subirse/meterse no
    !     tiene el atributo "entrable"
    !  3: Error, el objeto en que intenta entrar/meterse/subirse, es
    !     un entrable y recipiente, pero est� cerrado.
    !  4: Error, el objeto en que intenta entrar/meterse/subirse, est�
    !     en poder del jugador
    !  5: �xito, el jugador sube/entra en el objeto
    !  6: Aviso, el jugador estaba en otro objeto, la librer�a
    !     intentar� una acci�n <Salir> autom�tica, antes de reintentar lo
    !     que el jugador le ha ordenado.
    !  7: Aviso, el objeto en que el jugador intenta meterse, est�
    !     dentro de otros objetos. La librer�a intentar� de forma
    !     autom�tica meter al jugador en el objeto desde el cual pueda
    !     acceder al que el jugador ha indicado.
    switch(ml_n)
    {
     1: print "Pero si ya est�s ";
	if (ml_o has soporte) print "sobre "; else print "en ";
	print_ret (el) ml_o, ".";
     2: print "No es algo donde puedas "; IdiomaVerbo(palabra_verbo); ".";
     3: "No puedes entrar en ", (el) ml_o, " porque est�", (n) ml_o,
        " cerrad", (o) ml_o, ".";
     4: print "No puedes "; IdiomaVerbo(palabra_verbo);
        " ah� mientras no lo sueltes.";
     5:
	if (ml_o has soporte) print "Subes ", (al) ml_o;
	else print "Entras en ", (el) ml_o;
	print_ret ".";
     6:
	if (ml_o has soporte) print "(te bajas "; else print "(sales ";
	print (del) ml_o; ")";
     7: if (ml_o has soporte) "(te subes ", (al) ml_o, ")^";
	if (ml_o has recipiente) "(te metes en ", (el) ml_o, ")^";
	"(entras en ", (el) ml_o, ")^";
    }

 Salirse:
    ! Esta acci�n se genera ante la frase SAL DEL ARMARIO o
    ! similares. Ante SAL a secas la acci�n es Salir.
    ! Si el jugador no est� en el objeto indicado, se genera el
    ! siguiente mensaje de error. Si est�, la librer�a generar� una
    ! acci�n Salir, por lo que el mensaje de �xito ser� el de Salir.
    "Pero si no est�s en ", (el) ml_o, ".";

 Salir:
    ! 1: Error, el jugador no est� subido/sentado/metido en ning�n
    !    objeto. [Nota, si la localidad tiene la propiedad "afuera",
    !    entonces la acci�n Salir lo sacar� de la localidad. En caso
    !    contrario es cuando se genera este error]
    ! 2: Error, el jugador est� dentro de un recipiente cerrado.
    ! 3: �xito, el jugador sale/baja del objeto
    switch(ml_n)
    {
     1: print "No est�s en ning�n sitio del que debas ";
	IdiomaVerbo(palabra_verbo); ".";
     2: "No puedes salir ", (del) ml_o, " porque est� cerrad", (o)ml_o, ".";
     3: if (ml_o has soporte) print "Bajas ";
	else print "Sales ";
	print_ret (del) ml_o, ".";
    }

 IrAmbiguo: ! El jugador ha dicho IR sin especificar a d�nde
    "Tienes que especificar en qu� direcci�n ir.";

 Ir:
    ! La acci�n Ir se genera si el jugador pone IR NORTE, o si pone
    ! simplemente NORTE.
    !   1: Error, el jugador est� dentro/subido en un objeto del que
    !      tiene que salir antes
    !   2: Error, la localidad no tiene salida en esa direcci�n (y
    !      tampoco tiene la propiedad no_puedes_ir, ya que en este caso
    !      se habr�a impreso el valor de esa propiedad
    !   3: Error, el jugador ha intentado ir hacia arriba, pero all�
    !      hay una puerta cerrada
    !   4: Error, el jugador ha intentado ir hacia abajo, pero all�
    !      hay una puerta cerrada.
    !   5: Error, en la direcci�n que ha dicho el jugador hay una
    !      puerta cerrada
    !   6: Error, en la direcci�n que ha dicho el jugador hay una
    !      puerta, pero �sta no tiene una propiedad puerta_a
    !      (probablemente un error de programaci�n del juego)
    switch(ml_n)
    {
     1: print "Tienes que ";
     	if (ml_o has soporte) print "bajarte "; else print "salir ";
     	print_ret (del) ml_o, " antes.";
     2: "No puedes ir por ah�.";
     3: "Eres incapaz de trepar por ", (el) ml_o, ".";
     4: "Eres incapaz de bajar por ", (el) ml_o, ".";
     5: "No puedes pasar a trav�s ", (del) ml_o, ".";
     6: "No puedes ir porque ", (el) ml_o, " no lleva", (n) ml_o, " a ning�n sitio.";
    }

 Mirar:
    ! La acci�n Mirar se genera cuando el jugador pone MIRAR, pero
    ! tambi�n de forma autom�tica al entrar en una localidad nueva, o
    ! cuando el jugador sale/se baja de un objeto en el que estaba.
    !
    ! Algunos de los mensajes que se definen aqu� aparecen en el
    ! "t�tulo" de la localidad (lo que aparece en negrita antes de la
    ! descripci�n de la localidad)
    !
    !  1: aclaraci�n a a�adir tras el t�tulo si el jugador est� subido
    !     en un objeto
    !  2: aclaraci�n a a�adir tras el t�tulo si el jugador est� dentro
    !     de un objeto
    !  3: aclaraci�n a a�adir tras el t�tulo si el jugador ha sido
    !     transformado en otro personaje, mediante una llamada a
    !     CambiarJugador(nuevo, 1); (si el 1, la librer�a no intentar�
    !     mostrar este mensaje)
    !  4: Una vez que la librer�a ha mostrado la descripci�n de la
    !     localidad, si el jugador estaba encima de un soporte, la
    !     librer�a generar� este mensaje 4 para mostrar qu� m�s cosas
    !     hay sobre el soporte
    !  Restantes:
    !     Son usados por la librer�a para listar los objetos "simples"
    !     que hay en la localidad. Son objetos "simples" los que no
    !     dan su propia auto-descripci�n a trav�s de la propiedad
    !     "describir" o "inicial".
    switch(ml_n)
    {
     1: print " (sobre ", (el) ml_o, ")";
     2: print " (en ", (el) ml_o, ")";
     3: print " (como ", (object) ml_o,")";
     4: print "^Sobre ", (el) ml_o;
	EscribirListaDesde(child(ml_o),
                      ESPANOL_BIT + RECURSIVO_BIT + INFOPARCIAL_BIT
                      + BREVE_BIT + HAY_BIT + OCULTAR_BIT);
	".";
     default:
	if (ml_o~=localizacion)
     	{   if (ml_o has soporte) print "^Sobre "; else print "^En ";
	    print (el) ml_o;
	    print " puedes ver ";
	}
	else print "^Puedes ver ";
	if (n==5) print "tambi�n ";
	EscribirListaDesde(child(ml_o),
                      ESPANOL_BIT + BANDERAUX_BIT + RECURSIVO_BIT
                      + INFOPARCIAL_BIT + BREVE_BIT + OCULTAR_BIT);
	if (ml_o~=localizacion) ".";
	".";
    }

  Examinar:
    !  1: Error, el jugador intenta examinar un objeto, pero est� a
    !     oscuras.
    !  2: �xito, pero el objeto examinado no tiene descripcion
    !  3: �xito, pero el objeto examinado no tiene descripcion, aunque
    !     tiene el atributo conmutable, por lo que la librer�a genera
    !     este mensaje para indicar si est� apagado o encendido.
    switch(ml_n)
    {
     1: "Est� demasiado oscuro, no puedes ver nada.";
     2: "No observas nada especial en ", (el) ml_o, ".";
     3: print (_El) ml_o, " ", (esta) ml_o;
	if (ml_o has encendido) " encendid", (o)ml_o, ".";
	else " apagad", (o)ml_o,".";
    }

  BuscarEn:
    ! La acci�n BuscarEn se genera ante la frase MIRA EN RECIPIENTE,
    ! MIRA EN SOPORTE, REGISTRA OBJETO.
    !
    !  1: Error, estamos a oscuras.
    !  2: �xito examinando soporte, pero no hay nada sobre �l.
    !  3: �xito examinando soporte, listar lo que hay.
    !  4: El objeto examinado no es soporte ni recipiente, mensaje
    !     est�ndar indicando que no se encuentra nada.
    !  5: Error, El objeto examinado es recipiente, pero est� cerrado.
    !  6: �xito, el objeto examinado es recipiente abierto, pero no
    !     tiene nada dentro.
    !  7: �xito, el objeto examinado es recipiente abierto y tiene
    !     cosas dentro. Listarlas.
    switch(ml_n)
    {
     1: "Est� muy oscuro.";
     2: "No hay nada sobre ", (el) ml_o, ".";
     3: print "Sobre ", (el) ml_o;
	EscribirListaDesde(child(ml_o),
                      BREVE_BIT + ESPANOL_BIT + HAY_BIT + OCULTAR_BIT);
	".";
     4: "No encuentras nada interesante.";
     5: "No puedes ver lo que hay dentro ", (del) ml_o, " porque ",
	 (esta) ml_o, " cerrad", (o)ml_o, ".";
     6: print_ret (_El) ml_o, " ", (esta) ml_o, " vac�", (o)ml_o,".";
     7: print "En ", (el) ml_o;
	EscribirListaDesde(child(ml_o),
                      BREVE_BIT + ESPANOL_BIT + HAY_BIT + OCULTAR_BIT);
	".";
    }

  QuitarCerrojo:
    ! QuitarCerrojo se genera ante ABRE <objeto> CON <objeto2>, o tambi�n
    ! ante QUITA CERROJO A <objeto> (en este segundo caso no se
    ! especifica la "llave" que abre la puerta).
    !
    !  1: Error, el objeto que se intenta abrir, no tiene el atributo
    !    cerrojo.
    !  2: Error, el objeto que se intenta abrir tiene atributo
    !     "cerrojo", pero no tiene atributo "cerrojoechado"
    !  3: Error, el <objeto2> que se intenta usar como llave, no
    !     coincide con la propiedad "con_llave" del <objeto> que
    !     intenta ser abierto.
    !  4: �xito. El <objeto> se abre (con <objeto2> si �ste ha sido
    !     especificado, el cual podemos encontrarlo en la variable "otro"
    switch(ml_n)
    {
     1: "No parece", (n) ml_o," tener ning�n tipo de cerrojo.";
     2:	print_ret (_El) ml_o, " ya ten�a", (n) ml_o, " abierto el cerrojo.";
     3: if (otro) "No parece", (n) ml_o, " encajar en la cerradura.";
	"Necesitas alg�n tipo de llave.";
     4: if (otro) "Quitas el cerrojo ", (al) ml_o, " con ", (el) otro, ".";
	"Quitas el cerrojo ", (al) ml_o, ".";
    }

 EcharCerrojo:
    ! EcharCerrojo se genera con CIERRA <objeto> CON <objeto2>, o
    ! tambi�n ante ECHA CERROJO A <objeto>. (sin especificar un
    ! segundo objeto en este caso)
    !
    !  1: Error, el objeto que se intenta cerrar no tiene la propiedad
    !     "cerrojo".
    !  2: Error, el objeto que se intenta cerrar tiene la propiedad
    !     "cerrojo", pero ya tiene tambi�n "cerrojoechado
    !  3: Error, el objeto tiene "cerrojo", pero est� "abierto". No se
    !     le puede echar el cerrojo hasta que no se cierre.
    !  4: Error, el <objeto2> especificado no coincide con el que el
    !     <objeto> indica en su propiedad "con_llave".
    !  5: �xito, el <objeto> es cerrado (con <objeto2> si este es
    !     especificado, el cual puede encontrarse en la variable
    !     "otro")
    switch(ml_n)
    {
      1: "No parece", (n) ml_o, " tener ning�n tipo de cerrojo.";
      2: if (ml_o provides con_llave)
	  print_ret (_El) ml_o, " ya estaba", (n) ml_o, " cerrad", (o) ml_o,
	  " con llave.";
	else
	  print_ret (_El) ml_o, " ya tiene", (n) ml_o, " echado el cerrojo.";
      3: "Primero tendr�s que cerrar ", (el) ml_o, ".";
      4: if (otro) "No parece", (n) ml_o, " encajar en la cerradura.";
	"Necesitas alg�n tipo de llave.";
      5: if (otro) "Cierras ", (el) ml_o," con ", (el) otro, ".";
	"Echas el cerrojo ", (al) ml_o, ".";
    }

 Encender:
    ! Generada al intentar ENCIENDE OBJETO si el objeto tiene el
    ! atributo "conmutable". Observar que si no lo tiene, la acci�n
    ! que se genera ser� sin embargo Quemar.
    !
    !   1: Error, el objeto no es conmutable (este error no aparecer�
    !      si el jugador pone ENCIENDE OBJETO, ya que en este caso la
    !      acci�n generada ser� Quemar objeto, pero puede aparecer si
    !      pone CONECTA OBJETO)
    !   2: Error, el objeto ya ten�a el atributo "encendido"
    !   3: �xito, el objeto tiene ahora activado "encendido".
    switch(ml_n)
    {
     1: print_ret "No es algo que pueda encenderse.";
     2: print_ret "Ya estaba", (n) ml_o, " encendid", (o) ml_o, ".";
     3: "Enciendes ", (el) ml_o, ".";
    }

 Apagar:
    !  1: Error, el objeto no tiene el atributo "conmutable"
    !  2: Error, el objeto ya tenia desactivado el atributo
    !    "encendido"
    !  3: �xito, el objeto tiene ahora desactivado "encendido"
    switch(ml_n)
    {
     1: print_ret "No es algo que pueda apagarse.";
     2: print_ret "Ya estaba", (n) ml_o, " apagad", (o) ml_o, ".";
     3: "Apagas ", (el) ml_o, ".";
    }

  Abrir:
    !  1: Error, el objeto no tiene el atributo "abrible"
    !  2: Error, el objeto es abrible, pero tiene "cerrojoechado"
    !  3: Error, el objeto es abrible, pero ya tiene el atributo
    !     "abierto"
    !  4: �xito, el objeto se abre, y adem�s era recipiente y ten�a
    !     cosas dentro. Se muestra entonces la lista de objetos que
    !     hab�a en su interior (si hab�a algo)
    !  5: �xito, el objeto se abre (pero no tiene nada en su
    !     interior, o no era recipiente).
    switch(ml_n)
    {
     1: print_ret "No es algo que pueda abrirse.";
     2: "Est�", (n) ml_o, " cerrad", (o) ml_o, " con llave.";
     3: "Ya estaba", (n) ml_o, " abiert", (o) ml_o, ".";
     4: print "Abres ", (el) ml_o, ", descubriendo ";
	if (EscribirListaDesde(child(ml_o),
                      	  ESPANOL_BIT + BREVE_BIT + OCULTAR_BIT)==0) "nada.";
	".";
     5: "Abres ", (el) ml_o, ".";
    }

  Cerrar:
    !  1: Error, el objeto no tiene el atributo "abrible"
    !  2: Error, el objeto es "abrible" pero ya estaba quitado su
    !     atributo "abierto" (o sea, estaba ya cerrado)
    !  3: �xito.
    switch(ml_n)
    {
     1: print_ret "No es algo que pueda cerrarse.";
     2: "Ya estaba", (n) ml_o, " cerrad", (o)ml_o, ".";
     3: "Cierras ", (el) ml_o, ".";
    }

  Desvestir:
    !  1: Error, el objeto no tenia el atributo "puesto"
    !  2: �xito.
    switch(ml_n)
    {
     1: "No llevas puesto eso.";
     2: "Te quitas ", (el) ml_o, ".";
    }

  Vestir:
    !  1: Error, el objeto no tiene el atributo "prenda"
    !  2: Error, el jugador no tiene el objeto
    !  3: Error, el objeto ya tiene el atributo "puesto"
    !  4: �xito.
    switch(ml_n)
    {
     1: "�No puedes ponerte eso!";
     2: "No ", (lo) ml_o, " tienes.";
     3: "�Ya ", (lo) ml_o, " llevas puest", (o) ml_o, "!.";
     4: "Te pones ", (el) ml_o, ".";
    }

  Comer:
    !  1: Error, el objeto no tiene el atributo "comestible"
    !  2: �xito. [NOTA: la librer�a permite por defecto comerse
    !    cualquier cosa que tenga el atributo "comestible", pero la
    !    �nica acci�n que causa esto es que el objeto en cuesti�n
    !    desaparece del juego al ser comido]
    switch(ml_n)
    {
     1: "Eso es simplemente incomestible.";
     2: "Te comes ", (el) ml_o, ". No est� mal.";
    }

!================================================================
! META COMANDOS
!================================================================
! Los siguientes verbos no consumen turno. No son acciones dentro del
! juego, sino fuera de �l.
! Ser� raro que quieras redefinir estos mensajes.

 Pronombres:
    ! Esta acci�n (generada por el verbo PRONOMBRES) muestra una lista
    ! de qu� significa en ese momento para el parser cada pronombre
    ! -lo, -la, -los, -las...
    !
    !  1: Texto introductorio
    !  2: La palabra "es"
    !  3: texto a mostrar si el pronombre no est� definido
    !  4: Si el juego no define pronombres
    switch(ml_n)
    {
     1: print "En este momento, ";
     2: print "es ";
     3: print "no est� definido";
     4: "el juego no conoce ning�n pronombre.";
    }
 Finalizar:
    !  1: Respuesta al comando FIN
    !  2: Respuesta si el jugador escribe algo distinto de "si" o "no"
    switch(ml_n)
    {
     1: print "Por favor, responde s� o no.";
     2: print "�Seguro que quieres abandonar el juego? ";
    }
 Reiniciar:
    !  1: Respuesta al comando REINICIAR
    !  2: Si no se puede reiniciar
    switch(ml_n)
    {
     1: print "�Seguro que quieres reiniciar el juego? ";
     2: "Error.";
    }
 Restaurar:
    ! 1: Si no se pudo cargar la partida con LOAD
    ! 2: �xito (no llega a mostrarse, porque en caso de �xito el
    !    estado del juego cambia al momento en que se salv�. El "Ok"
    !    que se ve entonces es el del comando Salvar.
    switch(ml_n)
    {
     1: "Error. No se pudo recuperar la partida.";
     2: "Ok.";
    }

 Salvar:
    ! 1: Si no se pudo guardar el juego
    ! 2: �xito
    switch(ml_n)
    {
     1: "Error. No se pudo guardar.";
     2: "Ok.";
    }

 Verificar:
    ! 1: �xito
    ! 2: Error en la verificaci�n
    switch(ml_n)
    {
     1: "Fichero de juego verificado e intacto.";
     2: "El fichero de juego no parece intacto, puede estar corrompido
	(a menos que est�s jugando con un int�rprete muy primitivo que
	no sea capaz de realizar la comprobaci�n).";
    }

 ActivarTranscripcion:
    ! 1: Error, ya estaba activada la transcripci�n
    ! 2: �xito (parte inicial del mensaje, la librer�a a�ade el t�tulo
    !    del juego obtenido de la constante Historia)
    ! 3: Error, no se ha podido activar la transcripci�n
    switch (ml_n)
    {
     1: "La transcripci�n ya estaba activada.";
     2: "Iniciando la transcripci�n de";
     3: "Intento de iniciar la transcripci�n fallido.";
    }

 DesactivarTranscripcion:
    ! 1: Error, ya estaba desactivada la transcripci�n
    ! 2: �xito
    ! 3: Error, no se ha podido desactivar la transcripci�n
    switch (ml_n)
    {
     1: "La transcripci�n ya estaba desactivada.";
     2: "^Fin de la transcripci�n.";
     3: "Intento de finalizar la transcripci�n fallido.";
    }

#Ifndef NO_PUNTUACION;
  ActivarNotificacion:
    "Notificaci�n de puntuaci�n activada.";

  DesactivarNotificacion:
    "Notificaci�n de puntuaci�n desactivada.";
#Endif; ! NO_PUNTUACION

#Ifndef NO_LUGARES;
 Lugares:
    ! El verbo "LUGARES" muestra un listado de los lugares que el
    ! jugador ha visitado. Aqu� debemos escribir el texto
    ! introductorio a esa lista.
    print "Has visitado: ";
#Endif; ! NO_LUGARES

 ModoM1:
    ! La acci�n ModoM1 se genera ante el comando BREVE (o NORMAL). La
    ! librer�a imprime la constante Historia y a continuaci�n este
    ! mensaje.
    " est� ahora en su modo normal ~breve~, que da solo descripciones
    largas de los lugares la primera vez que son visitadas, y
    descripciones cortas en otro caso.";

 ModoM2:
    ! La acci�n ModoM2 se genera ante el comando LARGO. La
    ! librer�a imprime la constante Historia y a continuaci�n este
    ! mensaje.
    " est� ahora en su modo ~largo~, que siempre da descripciones
    largas de los lugares (incluso si ya hab�as estado antes).";

 ModoM3:
    ! La acci�n ModoM3 se genera ante el comando SUPERBREVE. La
    ! librer�a imprime la constante Historia y a continuaci�n este
    ! mensaje.
    " est� ahora en su modo ~superbreve~, que siempre da descripciones
    cortas de los lugares (incluso si nunca hab�as estado antes).";

#Ifndef NO_LUGARES;
 Objetos:
    ! Ante el verbo "OBJETOS" se genera esta acci�n, que muestra una
    ! lista de todos los objetos que el jugador ha manipulado a lo
    ! largo del juego, junto con una indicaci�n de qu� hizo con ellos.
    !
    !  1: Texto introductorio a la lista
    !  2: Si no ha manejado a�n ninguno
    !  3: indicaci�n de que lo lleva puesto
    !  4: indicaci�n de que lo lleva en su inventario
    !  5: indicaci�n de qui�n lo tiene ahora (si lo tiene un PNJ)
    !  6: indicaci�n de d�nde est� el objeto (si est� en una localidad)
    !  7: indicaci�n de d�nde est� el objeto (si est� en un "entrable")
    !  8: indicaci�n de d�nde est� el objeto (si est� en un recipiente)
    !  9: indicaci�n de d�nde est� el objeto (si est� en un soporte)
    !  10: indicaci�n de que se ha perdido (no est� en ninguno de los
    !     casos anteriores)
    switch(ml_n)
    {
     1: "Objetos que has manejado:^";
     2: "Ninguno.";
     3: print "   (puest", (o) ml_o, ")";
     4: print "   (l", (o) ml_o, " llevas)";
     5: print "   (en poder ", (del) ml_o, ")";
     6: print "   (en ", (name) ml_o, ")";
     7: print "   (en ", (el) ml_o, ")";
     8: print "   (dentro ", (del) ml_o, ")";
     9: print "   (en ", (el) ml_o, ")";
     10: print "   (perdid", (o) ml_o, ")";
 }
#Endif; ! NO_LUGARES

#Ifndef NO_PUNTUACION;
 Puntuacion:
    ! Puntuaci�n del juego. Puede activarse porque el jugador lo pide
    ! (con el verbo "PUNTUACION") o porque el juego ha terminado. En
    ! este ultimo caso, la variable "banderafin" valdr� true.
    if (banderafin) print "En este juego, tu puntuaci�n ha sido ";
    else print "Hasta el momento tu puntuaci�n es ";
    print puntuacion, " de un total de ", PUNTUACION_MAX,
	", en ", turnos, " turno";
    if (turnos>1) print "s"; return;

 PuntuacionTotal:
    ! Puntuaci�n en modo "explicativo". Puede activarse porque el
    ! jugador lo pida con el verbo "PUNTUACION LARGA" o porque el
    ! juego haya terminado (y la constante HAY_TAREAS est� definida).
    !
    !  1: texto introductorio al desglose de puntos
    !  2: texto de objetos importantes (los que tienen el atributo
    !     "valepuntos")
    !  3: texto de lugares importantes (los que tienen el atributo
    !     "valepuntos")
    !  4: texto final, tras la suma total impresa por la librer�a
    switch(ml_n)
    {
     1: if (banderafin) print "La puntuaci�n se desglos� ";
	else          print "La puntuaci�n se desglosa ";
	"de la siguiente manera:^";
     2: "por encontrar objetos importantes";
     3: "por visitar lugares importantes";
     4: print "total (de ", PUNTUACION_MAX
	 ; ")";
    }
#Endif; ! NO_PUNTUACION

 Inv:
    ! Inventario
    !  1: Mensaje si el inventario est� vac�o
    !  2: Encabezado del inventario, antes de la lista de objetos
    !     generada por la librer�a
    switch(ml_n)
    {
     1: "No llevas nada.";
     2: print "Llevas";
    }
!================================================================
! MISCELANEA
!================================================================
! Esta es una falsa acci�n, que se usa simplemente para agrupar aqu�
! todos los mensajes de error del parser, los mensajes ante algunos
! metacomandos, o algunos mensajes de librer�a no relacionados con
! acci�n alguna. La asignaci�n de n�meros a mensajes es bastante
! caprichosa.

! Debajo de cada mensaje un comentario indica en qu� condiciones se
! genera.

 Miscelanea:
    switch(ml_n)
    {
     1: "(S�lo considero los diecis�is primeros objetos)^";
	! El jugador ha especificado objetos m�ltiples, pero el parser
	! tiene una lista que no admite m�s de 16, de modo que los
	! restantes objetos no ser�n procesados.

     2: "�No s� a qu� objetos te refieres!";
	! El jugador ha usado objetos m�ltiples, pero por alguna raz�n
	! la lista del parser est� vac�a.

     3: TextoLlamativo(" Has muerto ");
	! Mensaje fin de juego. Has muerto.

     4: TextoLlamativo(" Has ganado ");
	! Mensaje fin de juego de victoria.

     5: ! Mensaje a mostrar tras el fin del juego, para pedir al
	! jugador si quiere reiniciar, recuperar, anular, puntuaci�n,
	! curiosidades o terminar.
	print "^�Quieres REINICIAR, RECUPERAR un juego guardado";
                  #Ifdef DEATH_MENTION_ANULAR;
                  print ", ANULAR tu �ltimo movimiento";
                  #Endif;
  #Ifndef NO_PUNTUACION;
	if (HAY_TAREAS==0)
	    print ", ver la PUNTUACI�N de este juego";
  #Endif; ! NO_PUNTUACION
	if (banderafin==2 && HAY_CURIOSIDADES==0)
	    print ", ver algunas CURIOSIDADES";
	" o TERMINAR?";

     6: "[Tu int�rprete no puede ~deshacer~ acciones, �lo siento!]";
	! Error si el int�rprete no tiene "undo"

     7: "~deshacer~ fall�. [No todos los int�rpretes lo tienen.]";
	! Otro error si el int�rprete no tiene "undo", pero no hab�a
	! sido detectado correctamente

     8: "Por favor, da una de las respuestas anteriores.";
	! Si el jugador no responde correctamente a la pregunta del
	! mensaje [Miscelanea,5]

     9: "^�Te has quedado a oscuras!";
	! Mensaje cuando se detecta, al final del turno, que ya no hay
	! luz.

     10: "�Perd�n?";
	! Mensaje cuando el jugador introduce una linea en blanco (no
	! llega a generarse acci�n alguna, por tanto no se consume
	! turno ni se ejecutan daemons)

     11: "[No puedes ~deshacer~ lo que no has hecho.]";
	! Si el jugador intenta "undo" al principio del juego

     12: "[No puedes ~deshacer~ dos veces seguidas. �Lo siento!]";
	! Si el jugador pone "undo" dos veces

     13: "[Retrocediendo al turno anterior.]";
	! �xito en el "undo"

     14: "Lo siento, eso no puede corregirse.";
	! Si el jugador pone EEPA (verbo para corregir), pero el
	! parser no recordaba ninguna palabra mal
	! El comando EEPA se usa as�, por ejemplo:
	!   > SACA MAZANA VERDE DE LA CESTA
	!   No veo eso por aqu�
	!   > EEPA MANZANA
	!   Sacas la manzana verde de la cesta de mimbre.

     15: "No te preocupes.";
	! Si el jugador pone EEPA s�lo (sin especificar la palabra
	! corregida)

     16: "~eepa~ s�lo puede corregir una palabra.";
	! Si el jugador pone EEPA seguido de dos o m�s palabras

     17: "Est� muy oscuro y no puedes ver nada.";
	! Descripci�n del objeto Oscuridad

     18: print "ti mism", (o) jugador;
	! Nombre corto del objeto jugador

     19: "Tan buen aspecto como siempre.";
	! Descripci�n del objeto jugador

     20: "Para repetir un comando como ~rana, salta~, escribe
	~repite~, en lugar de ~rana, repite~.";
	! Cuando el jugador pone PNJ, REPITE para que el PNJ haga otra
	! vez la �ltima acci�n.

     21: "No hay comando que repetir.";
	! Cuando el jugador pone REPITE como primer comando del juego.

     22: "No puedes empezar la frase con una coma.";
	! Cuando ha empezado la frase con una coma :-)

     23: "Parece que quieres hablar con alguien, pero no veo con
	qui�n.";
	! Cuando el jugador pone PEPE, COGE HACHA, pero no hay un
	! objeto que responda al nombre PEPE.

     24: "No puedes hablar con ", (el) ml_o, ".";
	! Si el jugador intenta hablar con un objeto que no es
	! "animado" ni "hablable" ("hablable" debe ponerse a objetos
	! inanimados con los que se podr�a hablar, como un micr�fono)

     25: "Para hablar con alguien intenta ~alguien, hola~ o algo
	as�.";
	! Si hay palabras no comprendidas entre el nombre del PNJ y
	! la coma, como p. ej.: PEPE XADASDGG, SALTA

     26: "(primero tratas de ", (coge)"r ", (el) ml_o, ")";
	! Si la gram�tica especifica que una acci�n debe efectuarse
	! sobre un objeto en poder del jugador (token "held"), pero el
	! jugador lo intenta sobre un objeto que no tiene, pero que
	! est� accesible, el parser intentar� autom�ticamente coger
	! ese objeto antes de efectuar la acci�n. En este mensaje se
	! avisa al jugador de esta intenci�n.

! ================================================================
! ERRORES DE PARSING
! Estos errores son generados por la librer�a, a menos que el
! programador proporcione su propia funci�n ErrorParser para
! manejo de errores.

     27:! El parser se ha atascado. Es el tipo de error m�s
	! gen�rico. Si el parser puede, dar� un error m�s concreto
	! (uno de los siguientes)
	"No entend� esa frase.";

     28:! Al parser le sobran palabras, aunque ha entendido gran parte
	! de la orden. Si la variable parser_listo es 1, debemos
	! sugerir al jugador un comando para ejecutar, basado en lo
	! que hab�a entendido el parser hasta el momento y esperar a
	! que el jugador responda Si o No para ejecutar ese comando.
	! Si parser_listo es 0, un simple mensaje de error basta
	! Si parser_listo es 2, no pregunta y realiza la acci�n
	!modo_mantenido=0;
	!^^^^^^^^^^^ [030305] esto ahora se controla desde EParser.h
        ! [010515] Si parte del comando era la
	! conjunci�n Y, el parser queda en "modo mantenido", lo que
	! puede causar errores en la interpretaci�n de comandos
	! subsiguientes, por si acaso, lo desactivamos
	switch (parser_listo)
	{
	  1:
	    print "No entiendo la �ltima parte. �Quieres ";
            ImprimirComando(0); print "?^^>";
            si_pl=SiONo();
          0:
            print "No entend� la �ltima parte de la frase.^";  ! [030305]
            si_pl=false;
          2:
            si_pl=true;
        }

     29: ! El parser esperaba un token de tipo n�mero
	"No comprend� ese n�mero.";

     30: ! El parser no ha comprendido el nombre del objeto al que se
	! refiere el jugador, o ese objeto no est� aqu�.
	"No veo eso que dices.";

     31: ! Este error parece que no se genera nunca. Un posible bug de
	! librer�a, o restos de versiones arcaicas
 	"�Pareces haber dicho muy poca cosa!";

     32: ! El objeto que el jugador intenta usar no est� en su
	! poder. El parser ha intentado "cogerlo de forma autom�tica",
	! pero ha fallado
	"�No tienes eso!";

     33: ! El jugador ha intentado usar objetos m�ltiples (o "TODO")
	! con un verbo que en su gram�tica no lo admite.
	"No puedes especificar objetos m�ltiples con ese verbo.";

     34: ! El jugador ha intentado objetos m�ltiples para "uno" y para
	! "otro", como en METE TODO EN TODO.
 	"S�lo puedes especificar objetos m�ltiples una vez en cada
	l�nea.";

     35: ! El jugador ha usado un pronombre, como COMELO, pero el
	! parser no tiene asignado un valor a ese pronombre.
 	"No estoy seguro de a qu� se refiere ~", (address) palabra_pronombre,
	 "~.";

     36: ! El jugador ha puesto una lista de objetos y ha usado la
	! palabra EXCEPTO para exceptuar algo que no estaba incluido
	! en la lista, por ejemplo: COGE TODAS LAS MONEDAS EXCEPTO EL
	! SACO.
	"Has exceptuado algo que no estaba incluido.";

     37:! La gram�tica de un verbo obliga a que el objeto sobre el que
	! se act�e sea animado (tiene un token de tipo "creature"),
	! pero el jugador lo ha intentado sobre un objeto que no es
	! animado.
	"S�lo puedes hacer eso con seres animados.";

     38: ! La primera palabra usada por el jugador es desconocida (o
	! la primera palabra tras la coma, si se trata de una orden a
	! un PNJ)
	"No conozco ese verbo.";

     39: ! El jugador intenta acciones sobre las palabras que est�n en
	! la propiedad "irrelevante" de la localidad
 	"Eso no es importante.";

     40: ! El jugador ha usado un pronombre, como EXAMINALO, pero el
	! pronombre se refiere a un objeto que ya no est� visible.
 	"Ahora mismo no puedes ver lo que representa el pronombre ~",
	  (address) palabra_pronombre,
	 "~ (", (el) objeto_pronombre, ").";

     41: ! Este error no sale nunca. Probablemente sigue aqu� por
	! razones de compatibilidad, o por despiste de Graham �Tal vez
	! ha sido sustituido en versiones m�s recientes por el mensaje
	! n�mero 28?
	"No entend� la �ltima parte de la orden.";

     42: ! El jugador ha solicitado un numero de objetos en una lista
	! de objetos m�ltiples, pero el parser no es capaz de
	! encontrar tantos. Por ejemplo: COGE SEIS MONEDAS.
	! En ml_o se recibe el n�mero de objetos hallados por el
	! parser.
 	if (ml_o==0) "No hay suficientes.";
         else if (ml_o==1){
	 print "Aqu� s�lo hay un";
	 if (objeto_multiple-->1) print (o) objeto_multiple-->1;
	 else print "o";
	 " disponible.";
        }
	else
	   "S�lo hay ", (number) ml_o, " disponibles para esa acci�n.";

     43: ! El jugador ha puesto TODO como objeto m�ltiple, pero el
	! parser no ha encontrado ning�n objeto. En realidad este
	! error parece no producirse nunca (otro bug de librer�a) ya
	! que el que siempre acaba gener�ndose es el siguiente (44)
 	"�No encuentro nada para hacer eso!";

     44: ! El jugador ha intentado objetos m�ltiples usando TODO
         ! pero el parser no ha encontrado ninguno. Por ejemplo, COGE
         ! TODO o DEJA TODO si no hay nada cerca o en el inventario.
         ! Modificado en [020621] para dar un mensaje m�s coherente
         ! si el jugador tiene alg�n objeto en su inventario.
       if (accion_que_seria == ##Dejar) {
         print "�Pero si no llevas nada";
         if (children (jugador))
           " de eso!";
         else
           "!";
       }
       print "No hay nada para ";
       IdiomaVerbo(palabra_verbo);
       ".";

     45:! El jugador ha nombrado un PNJ ambiguo (hay m�s de uno con el
	! mismo nombre cerca). El parser le pide aclaraci�n. Este
	! mensaje es la primera parte de la pregunta, el resto lo pone
	! el parser (que es la lista de PNJs entre los que
	! duda). Debemos poner a 1 la variable PreguntaCualExactamente
	! cuando se generan este tipo de preguntas aclaratorias.
 	print "�Qui�n concretamente, ";
	PreguntaCualExactamente=1;
	ImprimirListaDudosos("o");
	print "?^";

     46:! El jugador ha nombrado un objeto ambiguo (hay m�s de uno con el
	! mismo nombre cerca). El parser le pide aclaraci�n. Este
	! mensaje es la primera parte de la pregunta, el resto lo pone
	! el parser (que es la lista de objetos entre los que
	! duda). Debemos poner a 1 la variable PreguntaCualExactamente
	! cuando se generan este tipo de preguntas aclaratorias.
 	print "�Cu�l concretamente, ";
	PreguntaCualExactamente=1;
	ImprimirListaDudosos("o");
	print "?^";

     47: ! El jugador ha respondido "TODOS" o "AMBOS" a una pregunta
	! aclaratoria como la anterior, pero el verbo no admite
	! objetos m�ltiples
	print "Lo siento, s�lo puedes referirte a un objeto aqu�. �Cu�l
	    exactamente?^";
	PreguntaCualExactamente=1;

     48: !El jugador ha escrito una frase u orden a PSI incompleta,
         !como BESA (verbo aplicado sobre PSIs normalmente).
         !El parser le pregunta para que complete la frase
 	PreguntaCualExactamente=1;
	if (IniciarPregunta()==0) print "A qui�n";
	if (actor ~= jugador) print " tiene que ";
	else print " quieres ";
     	IdiomaImprimirComando();
	if (actor~=jugador) print " ", (el) actor;
	print "?^";

     49: !El jugador ha escrito una frase u orden a PSI incompleta,
         !como COGE (verbo aplicado sobre objetos normalmente).
         !El parser le pregunta para que complete la frase
	PreguntaCualExactamente=1;
	if (IniciarPregunta()==0) print "Qu�";
	if (actor ~= jugador) print " tiene que ";
	else print " quieres ";
     	IdiomaImprimirComando();
	if (actor~=jugador) print " ", (el) actor;
	print "?^";

#Ifndef NO_PUNTUACION;
     50: ! El jugador acaba de realizar una acci�n que punt�a (la
	! librer�a ha detectado que la variable puntuacion ha cambiado
	! de valor). Se informa de ello al jugador. El par�metro ml_o
	! contiene el incremento (o decremento) en la puntuaci�n.
	print "Tu puntuaci�n ha ";
	if (ml_o > 0)
          print "aumentado";
        else {
          ml_o = -ml_o;
          print "disminuido";
        }
	print " en ", (number) ml_o, " punto";
	if (ml_o > 1) print "s";
#Endif; ! NO_PUNTUACION

     51: ! El jugador ha intentado una acci�n con objeto m�ltiple
	! (como COGE TODO). Esta acci�n es convertida por el parser en
	! una serie de acciones COGE OBJETO1, COGE OBJETO2, etc... Si
	! en la ejecuci�n de alguna de estas acciones encuentra que la
	! localidad del jugador ha cambiado, debe abortar el
	! proceso. Este mensaje informa de ello al jugador.
	!
	"(Ya que ha ocurrido algo dram�tico, se ha recortado la lista
	de objetos sobre los que actuabas)";

     52: ! En los men�s, se espera a que el jugador escriba un n�mero
	! para mostrar una entrada del men�. Si pulsa un numero
	! incorrecto, se saca este mensaje. El par�metro ml_o contiene
	! el n�mero m�s alto v�lido
	"^Escribe un n�mero del 1 al ", ml_o,
	 ", 0 para volver a mostrarlo, o pulsa Intro.";

     53: ! Mensaje que muestra el sistema de men�s cuando espera una
	! tecla
 	"^[Por favor, pulsa ESPACIO]";
    }

 ListaMiscelanea:
    ! Los siguientes mensajes se muestran como aclaraciones cuando se
    ! est� listando el inventario del jugador, o los objetos que hay
    ! en una localidad. Junto a cada mensaje se comenta qu�
    ! condiciones deben darse en ese objeto para que se muestre ese
    ! mensaje aclaratorio

    switch(ml_n)
    {
     1: print " (alumbrando)";
	! El objeto tiene "luz" y la localidad no
     2: print " (que ", (esta) ml_o, " cerrad", (o) ml_o, ")";
	! El objeto tiene "recipiente" pero no "abierto"
     3: print " (cerrad", (o) ml_o, " y alumbrando)";
	! Casos 2 y 1 juntos
     4: print " (que ", (esta) ml_o, " vac�", (o) ml_o, ")";
	! El objeto es un recipiente abierto (o transparente) y no
	! tiene nada en su interior
     5: print " (vac�", (o) ml_o, " y alumbrando)";
	! Casos 1 y 4 juntos
     6: print " (que ", (esta) ml_o, " cerrad", (o) ml_o, " y vac�",
	 (o) ml_o, ")";
	! El objeto tiene "recipiente", no "abierto", pero s�
	! "transparente"
     7: print " (cerrad", (o) ml_o, ", vac�", (o) ml_o, " y
	    alumbrando)";
	! Casos 1 y 6 juntos

! Los casos siguientes son similares, pero se muestran cuando
! se solicita a la rutina EscribirListaDesde la opci�n INFOTOTAL
! La librer�a puede combinar varios de estos mensajes, por eso no
! deben llevar el cerrar par�ntesis al final, que lo a�ade la
! propia librer�a
! ************************************
!  NO SE ACONSEJA CAMBIAR ESTOS
! ************************************

     8: print " (alumbrando y que llevas puest", (o) ml_o;
	! El objeto tiene "luz" y "puesto"
     9: print " (alumbrando";
	! El objeto tiene "luz" pero no "puesto"
     10: print " (que llevas puest", (o) ml_o;
	! El objeto tiene "puesto" pero no "luz"
     11: print " (que ", (esta) ml_o, " ";
	! Mensaje introductorio para decir "que est�
	! abierto/cerrado/vac�o"...
     12: print "abiert", (o)ml_o;
	! Objeto tiene "recipiente", "abrible" y "abierto" (y cosas dentro)
     13: print "abiert", (o)ml_o, " pero vac�", (o) ml_o;
	! Objeto tiene "recipiente", "abrible" y "abierto (pero vac�o)
     14: print "cerrad", (o) ml_o;
	! Objeto tiene "recipiente", "abrible"  y no "abierto"
     15: print "cerrad", (o) ml_o, " con llave";
	! Objeto tiene "recipiente", "abrible" y "cerrojoechado" o "cerrojo"
     16: print " vac�", (o) ml_o;
	! Objeto tiene "recipiente", no "abrible" y "transparente"
     17: print " (que ", (esta) ml_o, " vac�", (o) ml_o, ")";
	! Como el caso anterior, pero mensaje m�s "largo" (que se activa si
	! EscribirListaDesde es llamada sin el modo BREVE_BIT)
     18: print " que contiene ";
	! encabezado a la lista de lo que hay dentro del objeto
     19: print " (sobre ", (el_) ml_o;
	! Si el objeto tiene "soporte", la librer�a va a listar sus
	! contenidos. Este es el encabezado de la lista
     20: print ", encima ", (del_) ml_o;
	! Como e l9, pero en otra modalidad (que se activa si
	! EscribirListaDesde es llamada sin el modo BREVE_BIT)
     21: print " (en ", (el_) ml_o;
	! Si el contenido tiene "recipiente" y puede verse su interior
	! y hay cosas, la librer�a va a mostrar sus contenidos. Este
	! es el encabezado de la lista
     22: print ", dentro ", (del_) ml_o;
	! Como el 21, pero en otra modalidad (que se activa si
	! EscribirListaDesde es llamada sin el modo BREVE_BIT)
    }

];
! ---------------------------------------------------------------------------

[ TextoLlamativo txt;
    ! Imprime un texto rodeado de asteriscos y en negrita. Es usado
    ! para mostrar el mensaje *** Has muerto *** y *** Has ganado ***
    ! Puedes cambiarlo si quieres que aparezcan en otros formatos.
#Ifdef TARGET_ZCODE;
    #IfV5; style bold; #Endif;
#Ifnot; ! TARGET_GLULX
     glk($0086, 5); ! set alert style
#Endif; ! TARGET_
     print "***", (string) txt, "***"; ! [010508] Corregido bug (string)
#Ifdef TARGET_ZCODE;
     #IfV5; style roman; #Endif;
#Ifnot; ! TARGET_GLULX
     glk($0086, 0); ! set normal style
#Endif; ! TARGET_
      print "^^^";
];


! La siguiente funci�n imprime la lista de objetos entre los que el
! parser tiene dudas (porque todos ellos responden al nombre que ha
! usado el jugador). Esta rutina es llamada desde los mensajes
! (Miscelanea,45) y (Miscelanea,46)

! Modificada en [021025] para que pregunte s�lo por aquellos objetos
! empatados a puntuaci�n m�xima por la desambiguaci�n.

[ ImprimirListaDudosos conjuncion
    i k marker punt_max num_objs;
  marker = 0;

  for (i = 0, punt_max = -1: i < numero_de_encajados: i++) {
    if (encajan_puntos-->i > punt_max) {
      punt_max = encajan_puntos-->i;
      num_objs = 1;
    }
    else if (encajan_puntos-->i == punt_max)
      num_objs++;
  }

  for (i = 1: i <= numero_de_clases: i++)
  {
      while (((encajan_clases-->marker) ~= i)
             && ((encajan_clases-->marker) ~= -i)) marker++;
      k=lista_encajan-->marker;

      if (encajan_puntos-->marker == punt_max) {
        if (encajan_clases-->marker > 0) print (el) k; else print (un) k;

        if (i < num_objs - 1)  print ", ";
        if (i == num_objs - 1) print " ", (string) conjuncion, " ";
      }
  }
];
