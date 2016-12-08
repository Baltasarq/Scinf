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
    thinkWordForPlayer "You think",
    thinkWordForOthers "thinks",
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
        "You should use ", (s_fixed) "talk to <character>", (s_normal) " if you want to communicate with someone.^";
    ],
    kissAction [;
        if ( self ~= player )
                self.say( "Are you crazy!? ... leave me alone!" );
        else    self.think( "That would be difficult!" );

        rtrue;
    ],
    notHereAction [;
        "Sorry, but... not here.";
    ],
    touchAction [;
        "Better not.";
    ],
    tasteAction [;
        "That does not make any sense.";
    ],
    searchAction [;
        print "^You start towards ", self.header( false ), " but...";
        self.say( "Eh! ... Keep your hands away from me!" );
        rtrue;
    ],
    emptyAction [;
        "Is ~Jack the ripper~ one of your ancestors?";
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
            print " does not seem to be interested.^";
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


Verb "talk"
	* 'to'/'with' creature -> tell
;

#Endif;
