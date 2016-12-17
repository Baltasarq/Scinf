! escr.h
! Baltasarq@yahoo.es
! Presenta un vector de cadenas en pantalla.
! Hace una pausa tras cada cadena.
! Visualiza cada cadena caracter a caracter.
! Imprime todo lo que queda de golpe si se pulsa la tecla 'Q'.

System_file;

#ifndef  ESCR_LIB;
Constant ESCR_LIB;

Message "Compilando librería de escritura letra a letra.";

Array escr_buffer_lib --> 1024;

#ifdef TARGET_GLULX;
Constant ESCR_PRIMERA_LETRA 4;
#endif;
#ifdef TARGET_ZCODE;
Constant ESCR_PRIMERA_LETRA 2;
#endif;

class escritura
class vector
private
    sonidoLetra Nothing,
    sonidoMensaje Nothing,

    volumen SMW_VOLUME_NORMAL,
    correr false,
with
    presenta [ch;
	print (char) ch;

	! Tocar un sonido, esperar a pulsar una tecla o que pase un tiempo
	self.hazSonido( self.sonidoLetra );
        self.hazPausa( self.pausaLetra );                    
    ],
    presentaFinMensaje [;
	self.hazSonido( self.sonidoMensaje );
	self.hazPausa( self.pausaMensaje );
    ],
    hazPausa [ pausa k;
        if ( ~~( self.correr )
	  && pausa > -1 )
	{
            k = wait( Nothing, pausa );

	    if ( k == 'Q' 
	      || k == 'q' )
	    {
		self.correr = true;
	    }
        }
    ],
    hazSonido [ sonido;
		if ( sonido != Nothing
		  && ~~( self.correr ) )
		{
			playSound( chan1, sonido, 1, self.volumen );
		}
    ],
    pausaLetra 10,
    pausaMensaje 15,
    visualiza [ n p lon;
	self.correr = false;
        escr_buffer_lib-->0 = 1022;

        ! Para cada cadena a visualizar
        for (n=0: n<self.longitud(): n++)
        {
            ! Para cada una de las cadenas
            ! Convertirlas a vector
            lon = ( self.elemento( n ) ).print_to_array( escr_buffer_lib );

            ! Visualizar las letras una a una
            for(p = ESCR_PRIMERA_LETRA: p < (lon + ESCR_PRIMERA_LETRA): p++) {
            	self.presenta( escr_buffer_lib->p );
            }
            print "^";
            
	    self.presentaFinMensaje();
        }
    ]
;


#endif;
