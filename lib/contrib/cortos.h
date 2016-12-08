!
! Cortos.h v2.0 biplataforma
! (c) Zak.
! 	preparada para SGW por baltasarq en Jun2008
!
! Creación de cortometrajes (secuencias no interactivas)
!
! Para documentacion y ejemplo de uso ver cortodem.inf
!

#ifndef CORTOS_H_;
Constant CORTOS_H_;

! Las dos lineas siguientes son para que esto siga funcionando con el
! antiguo compilador inform 6.15, que no define la constante
! TARGET_ZCODE.
#ifndef WORDSIZE;
Constant WORDSIZE = 2;
Constant TARGET_ZCODE;
#endif;



!=========================================================
! Variables globales de interés para el usuario
!=========================================================

Global velocidad_texto=20;


!=========================================================
! Variables y funciones auxiliares
!=========================================================

Array StringAux->500;

! Calcula la longitud de la cadena str
[ Cortos_LStrLen str;
    str.print_to_array(StringAux);
    return StringAux-->0;
];


! Funcion "tonta" necesaria para una lectura de teclado temporizada
! PrintAutoPausa
!
! La siguiente función imprime txt, y despues espera
! un tiempo que depende de la longitud del texto
! y de la variable global velocidad_texto
! La espera termina tambien si el lector pulsa una tecla
[ PrintAutoPausa txt k;
  if ( velocidad_texto == 0 )
    k = wait( txt, 0 );
  else
    k = wait( txt, Cortos_LStrLen(txt)*10/velocidad_texto+10 );
  return k;
];      




!=======================================================
! CLASE Cortometraje
!=======================================================

Class 	CortoMetraje
 with  	proyeccion [i t;
	    if (~~i) clearMainWindow();
	    if (self provides descripcion) {
	    	for (i=0:i<(self.#descripcion)/WORDSIZE:i++) {
		    if ((self.&descripcion)-->i ofclass string)
	    		t=PrintAutoPausa((self.&descripcion)-->i);
		    else if ((self.&descripcion)-->i ofclass routine)
		    {
		    	indirect((self.&descripcion)-->i);
			t=wait(0, self.delay);
		    }
		    else jump error; 
		    if (t=='q' or 'Q') print_ret " ";
	    	}
		return;
	    }
	    .error;
	    
	    #ifdef DEBUG;
	    print "Error: CortoMetraje sin descripción.^";
	    #endif;
	],
	delay 0,
;
#endif;

