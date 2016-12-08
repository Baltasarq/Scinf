System_file;

#ifndef CHARACTER_H;
Constant CHARACTER_H;

! --------------------------------------------------------- Class Character -----------
class Character
private
    status 0,
with
    getStatus [;
        return self.status;
    ],
    toProperName [s;
        give self proper;
        self.short_name = s;
    ],
    noLineFeed true,
    printHeader [;
        s_bold();
        if ( self == player )
                print (string) self.short_name;
        else    print (The) self;
        s_normal();
        rtrue;
    ],
    header [ noLineFeed;
            if ( ~~noLineFeed ) {
                print "^";
        }

        self.printHeader();
    ],
    headerForSaying [;
        self.header();
        print ": ~";
    ],
    thinkWordForPlayer "Piensas",
    thinkWordForOthers "piensa",
    headerForThinking [;
        s_bold();
        if ( player == self ) {
                print (string) self.thinkWordForPlayer, ": ";
        } else {
            self.printHeader();
            print " ", (string) self.thinkWordForOthers, ": ";
        }

        s_normal();
        print "~";
    ],
    say [s;
        self.headerForSaying();
        s_underline();
        print (string) s;
        s_normal();
        print "~";
        wait();
        print "^";
    ],
    think [s;
        self.headerForThinking();
        s_underline();
        print (string) s;
        s_normal();
        print "~^";
    ],
    helpTalking [;
        "Debes usar ", (s_fixed) "hablar con <personaje>", (s_normal) " para hablar con alguien.^";
    ],
    kissAction [;
        if ( self ~= player )
                self.say( "¡¿ Te has vuelto loco !? ... ¡déjame de una vez!" );
        else    self.think( "¡Eso sería difícil!" );

        rtrue;
    ],
    notHereAction [;
        "Pero ... ¡si no está aquí!";
    ],
    touchAction [;
        "Mejor no.";
    ],
    tasteAction [;
        "Eso no tiene ningún sentido.";
    ],
    searchAction [;
        print "^Haces ademán de comenzar a registrar ", (al) self, " pero ...";
        self.say( "¡Eh! ... ¡Las manos quietas!" );
        rtrue;
    ],
    emptyAction [;
        "¿Será ~Javier el destripador~ uno de vuestros ascendientes?";
    ],
    before [;
        tell:
                self.conversation();
                rtrue;

        answer:
                return self.helpTalking();

        ask:
                return self.helpTalking();

        default:
            if ( self notin location
              && player ~= self )
            {
                return self.notHereAction();
            }

            if ( action == ##kiss ) {
                return self.kissAction();
            }

        	return self.before_procedure();
    ],
    before_procedure [;
            touch: return self.touchAction();
            taste: return self.tasteAction();
            search:
                if ( self ~= player )
                        return self.searchAction();
                else    <<Examine player>>;
            empty: return self.emptyAction();
            default: rfalse;
    ],
    conversation [;
            self.header();
            print " no parece ";

            if ( self has female )
                    print "interesada.^";
            else    print "interesado.^";

            return;
    ],
    changeStatus [;
    ],
    daemon [;
            self.changeStatus();
    ],
    prepareAllCharacters [x;
            objectloop ( x ofclass Character ) {
                x.init();
            }

            rtrue;
    ],
    init [;
            self.status = 0;
            startDaemon( self );

            rtrue;
    ]
has animate;


Extend "habla" first
	* 'con'/'a//'/'al' creature -> tell
;

#Endif;
