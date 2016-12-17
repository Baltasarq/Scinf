! BajoNivel.h
! ----------------------------------------
! Modificado: baltasarq. 27/08/2006
! Ahora se puede poner tambi�n estilo de letra proporcional en Glulxe y en Z
!
! Modificado: baltasarq. 22/04/2002
! Ahora se puede poner estilo negrita, cursiva y normal en Glulxe y en Z
!
! (c) 2000 Zak McKracken (17/Octubre/2000)
!
! Las funciones definidas en este m�dulo vienen tambi�n en la librer�a
! SIX v2, por lo que si usas SIX no necesitas incluir este m�dulo (no
! podr�s, de hecho).
!
! Este m�dulo implementa las funciones BorrarPantalla
! y EsperarTecla. Estas funciones sol�an escribirse en ensamblador de
! la m�quina Z a base de @read y @erase_window. Pero este m�todo
! complica la adaptaci�n del juego para su compilaci�n bajo Glulx.
!
! Incluyendo este m�dulo, el programador puede poner simplemente
! BorrarPantalla(); en lugar de @erase_window -1. Cuando compile para
! la m�quina Z, el efecto ser� el mismo, pero cuando compile para
! Glulx, se convertir� en llamadas a Glk para borrar la pantalla.
!
! De forma an�loga EsperarTecla(); espera a que se pulse una tecla
! antes de continuar. Pueden pas�rsele dos par�metros, opcionales. El
! primero ser�a un texto a mostrar antes de esperar, y el segundo el
! tiempo m�ximo a esperar en d�cimas de segundo. Por ejemplo:
!
! EsperarTecla("[Pulsa una tecla]", 100);
!
! esperar�a un m�ximo de 10 segundos, tras lo cual retornar�a como si
! el jugador hubiera pulsado una tecla. Si se pulsa una tecla, se
! retorna el c�digo de la misma, si no se pulsa y el tiempo se agota,
! se retorna cero.
!
! Si se omite el segundo par�metro, la espera ser� infinita. Si se
! omiten ambos par�metros, no se muestra texto y la espera es
! infinita. Para omitir el primer par�metro pero no el segundo la
! llamada ha de ser algo como:
!
! EsperarTecla(0, 100);
!
! En cuyo caso no se escribir�a nada y se esperar�an 10 segundos.
! [NOTA: La espera temporizada puede no estar disponible en algunos
! int�rpretes, que har�n pausa infinita siempre]
!
System_file;

#ifndef WORDSIZE;
Constant WORDSIZE = 2;
Constant TARGET_ZCODE;
#endif;

#ifdef TARGET_ZCODE;
[ BorrarPantalla ;
  @erase_window -1;
];

[ Volver;
    rtrue;
];

[ EsperarTecla msg delay k;
    if (msg~=0) print (string) msg;
    if (delay==0)
        @read_char 1 0 0 k;
    else @read_char 1 delay Volver k;
    return k;
];

[ Negrita;
      style bold;
];

[ Italica;
      style underline;
];

[ Normal;
      font on;
      style roman;
];

[ Proporcional;
      font off;
];
#endif;

#ifdef TARGET_GLULX;
[ BorrarPantalla w;
    if (w==0) w=gg_mainwin;
    if (gg_quotewin) ! Cerrar la ventana de boxes
    {
        glk($0024, gg_quotewin, 0); ! close_window
        gg_quotewin = 0;
    }
    glk($002A, w);  ! window_clear
];

[ EsperarTecla s delay;
    if (s) print (string) s;
    glk($00D6, delay*100); ! request_timer_events
    glk($00D2, gg_mainwin); ! glk_request_char_event(gg_mainwin);
    while(1) 
    {
    glk($00C0, gg_arguments); ! glk_select(gg_arguments);
    if ((gg_arguments-->0) == 2) break; ! 2=evType_CharInput
    if ((gg_arguments-->0) == 1)
    {
        glk($00D3, gg_mainwin); ! cancel_char_event
            glk($00D6, 0); ! request_timer_events (cancelados)
        return 0;
    }
    }
    return gg_arguments-->2;
];

Constant GLK_ESTILO_NORMAL 0;
Constant GLK_ESTILO_ENFASIS 1;
Constant GLK_ESTILO_ALERTA 5;
Constant GLK_ESTILO_PREFORMATEADO 2;
Constant GLK_ESTILO_NOTA 6;
Constant GLK_ESTILO_CITA 7;

[ Normal;
      glk($0086, GLK_ESTILO_NORMAL); 
];

[ Negrita;
      glk($0086, GLK_ESTILO_ALERTA);
];

[ Italica;
      glk($0086, GLK_ESTILO_NOTA);
];

[ Proporcional;
     glk($0086, GLK_ESTILO_PREFORMATEADO);
];
#endif;
