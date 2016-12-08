! pensamiento.h
! Pensamientos que:
!     aparecen y desaparecen (PensamientoFugaz)
!     van cambiando          (PensamientoEnCadena)
!     varían                 (PensamientosVarios)

#Ifndef PENSAMIENTO_H_;
Constant PENSAMIENTO_H_;

System_file;

Include "responde";
Include "character";

class Pensamiento
    with
        elPensamiento [;
            return "";
        ],
        piensa [ persona ideaPensada;
            ideaPensada =  self.elPensamiento();
            
            if ( ideaPensada == Nothing ) {
                return;
            }
        
            ! ¿Quién piensa ésto?, indicarlo
            if ( persona == player ) {
                print (s_bold) "Piensas: ";
            }
            else
            if ( persona ofclass Character ) {
                persona.header();
                print (s_bold) " piensa: ";
            }
            else
            if ( persona ofclass string ) {
                s_bold();
                print (string) persona;
                s_normal();
            }
            else
            if ( persona ofclass object ) {
                s_bold();
                print (string) persona, ":";
                s_normal();
            }
            else {
                print "^^*** ERROR *** Pensamientos.pensar(): ¿quién piensa ésto?^^";
                rfalse;
            }
        
            ! Ahora, el pensamiento
            print "~";
            s_underline();
            print (string) ideaPensada, "~^";
            s_normal();
            return;
        ]
;

class PensamientoFugaz
class Pensamiento
private
    mostrado false
with
    ideaFugaz "",
    elPensamiento [;
        if ( ~~self.mostrado ) {
            self.mostrado = true;            
            return self.ideaFugaz;
        }
        else return "";
    ]
;

class PensamientoEnCadena
class Pensamiento
class RespondeUnaVez
with
    elPensamiento [;
        if ( self.num < self.longitud() )
            return self.dev_msg();
        else    return "";
    ]
;

class PensamientosVarios
class Pensamiento
class Responde
with
    elPensamiento [;
        return self.dev_msg();
    ]
;

#Endif;