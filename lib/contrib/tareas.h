! tareas.h
! ---------------------------------------------------
! Permite activar tareas que hacen saber al jugador
! lo que tiene que hacer, por si se siente perdido.
! v1.0 Diciembre 2006

System_file;

object GestorTareas
with
    getNumTareas [ x numTareas;
        numTareas = 0;
    
        objectloop ( x in self ) {
            if ( x ofclass Tarea
              && x.fueActivada()
              && ~~( x.fueCompletada() ) )
            {
                numTareas++;
            }
        } 
        
        return numTareas;   
    ],
    verTareasPendientes [x numTareas;
        numTareas = self.getNumTareas();

        if ( numTareas > 0 ) {
            print "^Repasas mentalmente las tareas por completar:^";        
            
            objectloop (x in self) {
                if ( x ofclass Tarea ) {
                    if ( x.fueActivada()
                      && ~~( x.fueCompletada() ) )
                    {
                        
                        print " - ",(string) x.descripcion, ".^";
                    }
                }
            }
            
            print "^";            
        }
        else "En este momento no se te ocurre nada.";
    ]
;

class Tarea
private
    tareaFueActivada false,
    tareaFueCompletada false,
with 
    fueActivada [;
        return self.tareaFueActivada;
    ],
    fueCompletada [;
        return self.tareaFueCompletada;
    ],
    activar [ver;
        move self to GestorTareas;
        self.tareaFueActivada = true;
        self.tareaFueCompletada = false;
        
        if ( ver ) {
            print "^Mentalmente, anotas que debes ";
            print (string) self.descripcion, ".^";
        }
        
        rtrue;
    ],
    desactivar [;
        self.tareaFueCompletada = true;
        print "^Mentalmente, tachas de tu lista de asuntos pendientes ";
        print (string) self.descripcion, ".^";
        
        rtrue;
    ],
    descripcion ""
;

[ PensarTareasSub;
   GestorTareas.verTareasPendientes();
];

Extend "piensa" first
    * -> PensarTareas
;
