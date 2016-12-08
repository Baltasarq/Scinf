! --------------------------------------------------------------------
!
! Contenedores (con capacidad definida)
! para usar con InformATE, adaptado por Zak, del
! original INFORM 6.x, (c) 1999 de Graham Nelson
!
! Versi�n 1.2 en Castellano, liberada por Morgul en 2008-06-19
!
! La versi�n 1.01 en Castellano, fue adaptada por dhan en 26-06-2002
! del original de Peer Schaefer "RECEPTACLES" beta-release 4 (2002-06-25)
!
! --------------------------------------------------------------------
!
! CAMBIOS DE LA VERSI�N 1.2:
!
! - Actualizada con la versi�n original de RECEPTACLES 1.0 (2002-07-06), que
!   incluye soporte de limitaci�n por n�mero de objetos contenidos y empieza
!   las l�neas de los mensajes en may�scula.
! - Corregidos los mensajes, con las correspondientes rutinas de formato del
!   print, para que sean siempre gramaticalmente correctos (coincidiendo en
!   g�nero y n�mero).
!
!
! REFERENCIAS
! =========
! Esta libreria implementa una nueva clase de objetos, llamados "contenedores".
! Estos contenedores pueden manejar los par�metros de Peso, Volumen y Tama�o.
! Cada vez que el jugador intenta colocar un objeto en ellos, el contenedor
! comprobar� si queda suficiente capacidad para �l, o no.
!
! Para definir su peso, volumen y tama�o, cada objeto en el juego deber� tener
! las siguientes propiedades:
!	Peso
!	Volumen
!	Tamano (n�tese que utilizaremos la palabra sin "�" para no ocasionar conflictos
!
! Cada una de estas tres nuevas propiedades pueden ser un valor num�rico o una
! rutina que provea un return con un valor num�rico. Si una de estas propiedades
! no existe o tiene el valor de 0 (cero), el parser entender� que la medida no es
! importante para su manejo en el juego.
!
! Estas unidades no se refieren a una medida de peso, volumen o tama�o concreto. No
! se refiere a gramos ni cent�metros, el programador deber� crear una escala propia.
!
! Para crear un contenedor que autom�ticamente compruebe el peso, volumen y tama�o de
! los objetos, simplemente hay que usar la nueva clase "contenedor". Los objetos de esta
! clase poseer�n tres nuevas propiedades:
! 	capacidad_peso
!	capacidad_volumen
!	capacidad_tamano
!
! Cada una de estas tres propiedades debe ser un valor num�rico o una rutina que devuelva
! un valor num�rico. Si alguna de estas propiedades falta, o tiene el valor de
! CAPACIDAD_INFINITA (una constante predefinida por esta librer�a), la capacidad
! respectiva del contenedor ser� infinita.
!
! Para aclarar todo esto:
! * El jugador puede almacenar varios objetos en un contenedor, siempre
!   que el peso total no exceda de la capacidad_peso del contenedor.
! * El jugador puede almacenar varios objetos en un contenedor, siempre
!   que el peso total no exceda de la capacidad_volumen del contenedor.
! * En otras palabras: capacidad_peso y capacidad_volumen son valores
!   usados por los objetos almacenados dentro del contenedor.
! * La propiedad capacidad_tamano funciona de otra forma: no tiene un
!   valor que se agote a medida que se va llenando de peso o volumen, sino que
!   comprueba cada uno de los objetos por separado. (El "tama�o" representa la
!   extensi�n de alg�n eje del objeto, por ejemplo la longitud de una flecha o
!   un bast�n. Es obvio que el volumen de un carcaj se completa a medida que
!   vas guardando flechas en �l, pero la longitud del carcaj no aumenta debido
!   a la longitud de las flechas que vas guardando: s�lo indica si la flecha
!   encaja en �l o es demasiado larga para entrar)
!
!
! EJEMPLO 1:
! ----------
! Contenedor caja "caja"
!      with nombre 'caja',
!        volumen 10,                ! La caja por s� misma tiene un volumen de 10 unidades
!        capacidad_volumen 9,       ! Y puede almacenar hasta objetos con 9 unidades
!        has recipiente;
!
! Object piedra "piedra"
!      with name "piedra",
!        volumen 2;                 ! La piedra tiene un volumen de 2
!
! Estas l�neas crean una caja con un volumen de 10 y una capacidad de 9, y una
! piedra con un volumen de 2. El jugador puede colocar hasta 4 piedras en la caja
! (lo que dar�a un volumen total de 4x2=8). No podr�as poner una quinta piedra, ya que
! la capacidad de la caja es de 9 y el volumen total de 5 piedras ser�a 10.
!
!
! Algunos detalles t�cnicos:
! -----------------------
!  * Calcular el peso de un recipiente (o soporte) es un proceso recursivo:
!    El peso de todos los objetos-hijo se a�aden al peso propio del contenedor;
!    el peso total de estos objetos-hijos tambi�n son la suma del peso que a su
!    vez tengan sus propios hijos.
!  * Si el peso de un objeto viene dado por una rutina, esta rutina dar� un return
!    del total del peso del objeto (incluendo el peso de todos sus hijos y sub-hijos).
!    El peso de los objetos hijos NO se a�ade en este caso autom�ticamente. Esto da
!    m�s flexibilidad para crear contenedores especiales (por ejemplo, bolsas m�gicas
!    cuyo peso es inferior al contenido).
!  * El Volumen y Tama�o de los hijos NO se a�ade al del objeto (se asume que los
!    contenedores normales no son flexibles y tienen unas proporciones fijas).
!
! Como un peque�o extra, un contenedor puede tambi�n proporcionar la nueva propiedad
! capacidad_numero. Es propiedad puede ser un n�mero o una rutina que
! devuelva un n�mero. Indica cu�ntos objetos (como m�ximo) pueden ser
! almacenados dentro del contenedor. Cualquier objeto m�s all� de este m�ximo ser�n
! rechazados.
!
!
! EJEMPLO 2:
! ----------
! El siguiente ejemplo crea una caja de madera y una de acero:
!
! Recipiente caja_madera "caja de madera"
!        with nombre 'caja' 'madera',
!        volumen 10,              ! La caja por s� misma tiene un volumen de 10 unidades
!        capacidad_volumen 9,     ! Y puede almacenar hasta objetos con 9 unidades
!        has recipiente;
!
! Recipiente caja_acero "caja de acero"
!        with nombre 'caja' 'acero',
!        volumen 8,               ! La caja por s� misma tiene un volumen de 8 unidades
!        capacidad_volumen 7,     ! Y puede almacenar hasta objetos con 7 unidades
!        has recipiente;
!
! Puedes meter la caja de acero dentro de la de madera (un volumen de 8 encaja dentro de
! la capacidad 9), pero no puedes meter la caja de madera dentro de la de acero (un volumen
! de 10 no encaja dentro de la capacidad de 7). Si pones algo que tenga un volumen de 2 o
! m�s dentro de la caja de madera, tampoco podr�s meter la caja de acero, ya que requiere
! un volumen libre de al menos 8.
!
!
! EJEMPLO 3:
! ----------
! El volumen y tama�o de los hijos NO se a�aden al total del volumen o tama�o que
! tienen los objetos (se asume que los recipientes no son flexibles y que tienen unas
! proporciones fijas), as� que si quieres crear una bolsa flexible cuyo volumen crezca
! si se introduce un objeto, debes crear una rutina para la propiedad volumen:
!
! Contenedor -> bolsa "bolsa flexible"
!        with nombre 'bolsa' 'flexible',
!        volumen [ v i;
!                v = 1;                    ! El volumen m�nimo es 1, si est� vac�a
!                objectloop (i in bolsa)   ! A�ade el volumen de los hijos
!                        v = v + CalculaVolumen (i);
!                return v;
!        ],
!        has recipiente;
!
!
! EJEMPLO 4:
! ----------
! El peso de los hijos del objeto se a�aden autom�ticamente al peso del objeto.
! Para evitar eso deber�s crear una rutina de peso. El siguiente ejemplo crea una
! bolsa m�gica, cuyo peso ser� la mitad del peso de su contenido:
!
! Contenedor -> bolsa_magica "bolsa m�gica"
!        with nombre 'bolsa' 'magica' ,
!        Peso [ w i;
!                w = 1;                         ! el peso base de la bolsa es 1
!                objectloop (i in bolsa_magica)
!                        w = w + CalculaPeso (i);  ! A�ade el peso...
!                return (w/2);                     ! ...y devuelve el 50%
!        ],
!        has recipiente;
!
!
! VERBOS PARA DEBUG:
! ----------------
! Cuando se compila en modo debug, la librer�a a�ade tres meta-verbos para
! comprobar el estado de algunos objetos:
!   $peso OBJECT           - revela el peso del objeto
!   $dimensiones OBJECT    - revela todas las dimensiones de ese objeto
!   $capacidad OBJECT      - revela la capacidad del recipiente
!
!
! CONTACTO:
! --------
! Cualquier comentario de la librer�a puede remitirse a su autor original:
! Peer Schaefer, en el siguiente mail: peerschaefer@gmx.net
! o de la adaptaci�n a dhan: dhan@interlap.com.ar
!
!
! INFORMACI�N DE LA VERSI�N ORIGINAL:
! ----------------------------------
!
! RECEPTACLES
! ===========
! (containers with defined capacities)
! for use with INFORM 6.x, (c) 1999 Graham Nelson
! Version 1.0 (2002-July-06)
!
! Written & copyright (c) 2002, 2006 by Peer Schaefer.
!
! The distribution of this file for free or for profit is allowed, as
! long as this copyright notice and the disclaimer (see below) remain
! intact. You may distribute modified versions of this file under the
! same terms, as long as you place a notice on top of the file that it
! is modified by you, and provide your name and the date of the
! modifications. The unmodified or modified version distributed by you
! must be (re)distributable, modifyable and usable under the same terms
! as this version.
!
! You may use this library unaltered or in a modified version freely
! for your own games, commercial or not. It would be nice if you give
! me some credit or provide the sourcecode, but that is not legally
! required.
!
! NO WARRANTY, NO LIABILITY. PROVIDED FREE OF CHARGE "AS IS". USE ON
! YOUR OWN RISK!
!
! Bug reports, comments and suggestions to: peerschaefer@gmx.net
!
! The latest version should be available at:
! http://www.wolldingwacht.de/if/recept.html
!
! --------------------------------------------------------------------

Ifndef CONTENEDORES_H_
Constant CONTENEDORES_H_

System_file;                      ! Para evitar un aviso por no usar esta clase



Class CONTENEDOR_COMODIN              ! Define las seis nuevas propiedades
        with
                peso    0,
                tamano  0,
                volumen 0,
                capacidad_peso    0,
                capacidad_tamano  0,
                capacidad_volumen 0,
                capacidad_numero  0;

Constant CAPACIDAD_INFINITA -1;    ! (-1) simboliza una capacidad infinita


! --------------------------------------------------------

! Las siguientes funciones calculan el peso, volumen y tama�o de cualquier objeto

[ CalculaPeso obj w i;
        if (obj provides Peso)
        {
                if (metaclass(obj.peso) == Routine)
                        return indirect (obj.peso);
                w = obj.peso;
        } else  w = 0;
        if ((obj has recipiente) || (obj has soporte))
                objectloop (i in obj)
                        w = w + CalculaPeso (i);   ! A�ade el peso de los "child"
        return w;
];

[ CalculaTamano obj;
        if (obj provides Tamano)
        {
                if (metaclass(obj.tamano) == Routine)
                        return indirect (obj.tamano);
                return obj.tamano;
        };
        return 0;
];

[ CalculaVolumen obj;
        if (obj provides Volumen)
        {
                if (metaclass(obj.volumen) == Routine)
                        return indirect (obj.volumen);
                return obj.volumen;
        };
        return 0;
];

! --------------------------------------------------------

! Las siguientes funciones calculan la capacidad de cualquier recipiente o soporte

[ CapacidadDePeso obj;
        if (obj provides capacidad_peso)
        {
                if (metaclass(obj.capacidad_peso) == Routine)
                        return indirect (obj.capacidad_peso);
                return obj.capacidad_peso;
        }
        return CAPACIDAD_INFINITA;        ! Capacidad ilimitada de peso
];

[ CapacidadDeVolumen obj;
        if (obj provides capacidad_volumen)
        {
                if (metaclass(obj.capacidad_volumen) == Routine)
                        return indirect (obj.capacidad_volumen);
                return obj.capacidad_volumen;
        }
        return CAPACIDAD_INFINITA;        ! Capacidad ilimitada de volumen
];

[ CapacidadDeTamano obj;
        if (obj provides capacidad_tamano)
        {
                if (metaclass(obj.capacidad_tamano) == Routine)
                        return indirect (obj.capacidad_tamano);
                return obj.capacidad_tamano;
        }
        return CAPACIDAD_INFINITA;        ! Capacidad ilimitada de tama�o
];

[ CapacidadDeNumero obj;
        if (obj provides capacidad_numero)
        {
                if (metaclass(obj.capacidad_numero) == Routine)
                        return indirect (obj.capacidad_numero);
                return obj.capacidad_numero;
        }
        return CAPACIDAD_INFINITA;        ! Capacidad ilimitada de n�mero
];

! --------------------------------------------------------


Class Contenedor
  with
        antes [ s i;

        Recibir:
        ! Comprobamos el peso:
                if ( CapacidadDePeso (self) ~= CAPACIDAD_INFINITA )
                                                       ! Si no tenemos capacidad
                                                       ! infinita
                {
                        if ( CalculaPeso(uno) > CapacidadDePeso (self) )
                                print_ret (_El) uno, " ", (es) uno, " muy pesad", (o) uno," para ", (el) self, ".";
                        s = 0;
                        objectloop (i in self)           ! calcula el
                                s = s + CalculaPeso(i);  ! peso de todo el
                                                         ! contenido
                        if ( (s + CalculaPeso(uno)) > CapacidadDePeso (self) )
                                print_ret (_El) self, " ha", (n) self, " alcanzado su capacidad m�xima.";
                };

        ! Comprobamos el volumen:
                if ( CapacidadDeVolumen (self) ~= CAPACIDAD_INFINITA )
                                                       ! Si no tenemos capacidad
                                                       ! infinita
                {
                        if ( CalculaVolumen(uno) > CapacidadDeVolumen (self) )
                                print_ret (_El) uno, " no encaja", (n) uno, " dentro de ", (el) self, ".";
                        s = 0;
                        objectloop (i in self)               ! calcula el
                                s = s + CalculaVolumen(i);   ! volumen de todo
                                                       	     ! el contenido
                        if ( (s + CalculaVolumen(uno)) > CapacidadDeVolumen (self) )
                                  print_ret (_El) self, " ha", (n) self, " alcanzado su capacidad m�xima.";
                };

        ! Comprobamos el tama�o:
                if ( CapacidadDeTamano (self) ~= CAPACIDAD_INFINITA )
                                                       ! Si no tenemos capacidad
                                                       ! infinita
                {
                        if ( CalculaTamano(uno) > CapacidadDeTamano (self) )
                                  print_ret (_El) uno, " ", (es) uno, " demasiado grande", (s) uno, " para ", (el) self, ".";
                };

        ! Comprobamos el n�mero:
                if ( CapacidadDeNumero (self) ~= CAPACIDAD_INFINITA )
                                                       ! Si no tenemos capacidad
                                                       ! infinita
                {
                        s = 0;
			objectloop (i in self)
				s++;
			if ( (s+1) > CapacidadDeNumero (self) )
                                print_ret (_El) self, " contiene", (n) self, " demasiados objetos.";
                };

                rfalse;
        ];



#ifdef DEBUG;

Verb meta       '$peso'           * noun                -> MetaPeso;
Verb meta       '$dimensiones'    * noun                -> MetaDimensiones;
Verb meta       '$capacidad'      * noun                -> MetaCapacidad;

 VerboIrregular "averiguar el peso" with imperativo '$peso';
 VerboIrregular "averiguar las dimensiones" with imperativo '$dimensiones';
 VerboIrregular "averiguar su capacidad" with imperativo '$capacidad';


[ MetaPesoSub;
                print_ret (_El) uno, " pesa", (n) uno, " ",
                CalculaPeso (uno), " unidades.";
];
[ MetaDimensionesSub;
                print (_El) uno, ":^";
                print "Peso: ",   CalculaPeso   (uno)," unidades^";
                print "Tama�o: ", CalculaTamano (uno)," unidades^";
                print "Volumen: ",CalculaVolumen(uno)," unidades^";
                rtrue;
];
[ MetaCapacidadSub;
                print (_El) uno, ":^";

                print "Capacidad (peso): ";
                if (CapacidadDePeso(uno) == CAPACIDAD_INFINITA)
                        print "infinito^";
                else
                        print CapacidadDePeso (uno), " unidades^";

                print "Capacidad (tama�o): ";
                if (CapacidadDeTamano(uno) == CAPACIDAD_INFINITA)
                        print "infinito^";
                else
                        print CapacidadDeTamano(uno)," unidades^";

                print "Capacidad (volumen): ";
                if (CapacidadDeVolumen(uno) == CAPACIDAD_INFINITA)
                        print "infinito^";
                else
                        print CapacidadDeVolumen(uno)," unidades^";

                print "Capacidad (n�mero de objetos): ";
                if (CapacidadDeNumero(uno) == CAPACIDAD_INFINITA)
                        print "infinito^";
                else
                        print CapacidadDeNumero(uno), "^";

                rtrue;
];

#endif;

! End

Endif;
