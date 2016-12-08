! Util.h
! A few functions for Inform programming.

system_file;

! Tests whether an object is held by the player or in the current location -----
! ------------------------------------------------------------------------------
[ getRootParent x obj;
    obj = x;

    while( parent( obj ) ~= Nothing ) {
        obj = parent( obj );
    }

    return obj;
];

! ------------------------------------------------------------------------------
! Tests whether an object is held by the player or in the current location -----
! ------------------------------------------------------------------------------
[ isReachable x obj;
    obj = getRootParent( x );

	return ( obj == location
	      || obj == player )
	;
];

! Lists all objects that are sons of x -----------------------------------------
! ------------------------------------------------------------------------------
[ listChildrenOf x num i;
        num = children( self );

        if ( num > 0 ) {
            i = 1;
            objectloop( x  in self ) {
                print (a) x;

                if ( i == num )
                        print ".";
                else	print ", ";

                i++;
            }
        }
];

! Checks whether the player has a light source, or whether it is in the location
! ------------------------------------------------------------------------------
[ isThereLight toret;
    toret = ( location has light );

    if ( ~~toret ) {
        toret = hasLightSource( player );
    }

    if ( ~~toret ) {
        toret = hasLightSource( location );
    }

    return toret;
];

! Finds the power of x to y: x^y
! ------------------------------------------------------------------------------
[ pow x y toret;
    toret = 1;
    while( y > 0 ) {
        toret = toret * x;
        y--;
    }

    return toret;
];

! Finds the absolute value of a x
! ------------------------------------------------------------------------------
[ abs x;
  if ( x < 0 )
        return -x;
  else  return x;
];

! System clock made easy
! ----------------------------------------------------------------------------
object Clock
private
    is24 false,
with
    is24Hour [;
        return self.is24;
    ],
    setIs24Hour [ x;
        if ( x == Nothing ) {
            x = true;
        }

        self.is24 = x;
    ],
    getHour [;
      return ( the_time / 60 );
    ],
    getMinute [;
      return ( the_time % 60 );
    ],
    print24h [ min;
        min = self.getMinute();

        print self.getHour(), "h";

        if ( min < 10 ) {
            print "0";
        }

        print min;
    ],
    print12h [ hour hour12 min;
        hour = self.getHour();
        hour12 = hour % 12;
        min = self.getMinute();

        if ( hour12 == 0
          && hour ~= 0 )
        {
            hour12 = 12;
        }

        print hour12, ":";

        if ( min < 10 ) {
            print "0";
        }

        print min, " ";

        if ( hour >= 12 )
                print "pm";
        else    print "am";
    ],
    print [;
        if ( self.is24Hour() )
                self.print24h();
        else    self.print12h();
    ],

    ! Sets the clock used when the status line is in time mode
    ! --------------------------------------------------------
    setClock [ h m rate;
        ! Find time data
        if ( h == Nothing ) {
            h = random( 23 );
        }

        if ( m == Nothing ) {
            m = random( 59 );
        }

        if ( rate == Nothing ) {
            rate = 1;
        }

        ! Set time
        setTime( ( h * 60 ) + m, rate );
    ]
;

class SequentialMessages
private
    msgNumber 0,
with
    messages 'item1' 'item2',

	getCurrentMessageNumber [;
        return self.msgNumber;
    ],
    setCurrentMessageNumber [ x;
        if ( x < 0
          || x >= self.getNumberOfMessages() )
        {
            x = 0;
        }

        self.msgNumber = x;
    ],
    incrementCurrentMessageNumber [;
        self.setCurrentMessageNumber(
                ( self.getCurrentMessageNumber() + 1 ) % self.getNumberOfMessages()
        );
    ],
    getNumberOfMessages [;
        return self.#messages / WORDSIZE;
    ],
    getMessage [ x;
        return ( self.&messages-->x );
    ],
	getNextMessage [ msg;
        msg = self.getMessage( self.getCurrentMessageNumber() );
        self.incrementCurrentMessageNumber();

        return msg;
	]
;
