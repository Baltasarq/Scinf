!===============================================================================!
! SMW - a Simple Multimedia Wrapper
!===============================================================================!
! SMW version 1.32 20120121			(remember to also change the #message)
! WeB   : http://caad.es/baltasarq/
! @mail : baltasarq@yahoo.es
!
! ** This version was forked from SGW by Baltasar, started in may/July 2008 **
!			     ** with the collaboration of Alessandro **
!		       ** and Carlos Sanchez                   **
! (SGW Version 1.6.1 20060311)
! (by Alessandro Schillaci, Vincenzo Scarpa, Paolo Maroncelli)
! (WeB   : http://slade.altervista.org)
! (@mail : silver.slade@tiscalinet.it)
!===============================================================================!
!
! WHAT IS THIS FOR ?
! ==================
! "smw.h" (this file) is a simple and small multimedia (glulxe) wrapper
! created for a novice inform programming level.
! With this library it's possible to visualize an image or simply to play a sound
! (or music) by using a small set of functions that wrap the glulx functions.
! There are also text styles ready to be used, and keyboard ones.
!
! It's possible to convert a z-code adventure to a glulx adventure with
! multimedia support, in few steps.
!
! You can use 3 audio channels:
!
! - SMW.music : for the music channel
! - SMW.chan1 : channel 1 for audio (sound effects)
! - SMW.chan2 : channel 2 for audio (sound effects)
!
!===============================================================================!
!
! HOW TO USE
! ==========
!
! Just follow these points:
!
! 1) Put in your main file the directive
!    include "smw.h";
!    before the Include "Parser"; directive
!
! 2) Use the initializeSMW(x, pos) function in your initialize standard function.
!
!    Example 1:
!
!    initializeSMW( 240, SMW_POS_UP );
!
!    This will set the main upper graphic window to have an height=240 pixels
!    but you can change this resolution as you like. You can choose the side
!    of the screen where you want graphics to appear, if not provided,
!    then SMW_POS_UP is assumed.
!
!    Example 2:
!
!    initializeSMW( 0 );
!
!    This won't create any special window for graphics. Graphics will appear centered,
!    at the right or at the left, but inlined with text.
!
!    Alternatively, you can define a proportional graphic window. In that case add
!
!    Constant SMW_PROPORTIONAL;
!
!    at the beginning of your source code. And the the function
!
!    initializeSMW( 40 );
!
!    will mean the graphic window will use a 40% of the screen.
!
!
! 3) Now you can play a sound or visualize an image simply using these functions into your Inform
!    code: Left (or viewImageCenter or viewImageRight) and playSound()
!
! 4) You can customize colors settings, by creating these Globals
!    before you include the "smw.h" library, to override them
!
!    Constant SMW_SCBACK $110101;			! background color (nearly everything)
!    Constant SMW_SCTEXT $DDBB99;			! plain text
!    Constant SMW_SCEMPH $FFFFDD;			! emphasized text
!    Constant SMW_SCHEAD $EEDDAA;			! header text
!    Constant SMW_SHBACK $EEDDAA;			! header text background
!    Constant SMW_SCINPU $DDEEAA;			! input text
!    Constant SMW_UDS1   $665544;			! user defined style 1
!    Constant SMW_UDS2   $665544;			! user defined style 2
!
!    or, using the color constants,
!
!    Constant SMW_SCBACK SMW_CLR_BLACK;		! background color (nearly everything)
!    Constant SMW_SCTEXT SMW_CLR_WHITE;		! plain text
!    Constant SMW_SCEMPH SMW_CLR_YELLOW;	! emphasized text
!    Constant SMW_SCHEAD SMW_CLR_CYAN;		! header text
!    Constant SMW_SHBACK SMW_CLR_BLACK;		! header text background
!    Constant SMW_SCINPU SMW_CLR_GREEN;		! input text
!    Constant SMW_UDS1   SMW_CLR_WHITE;		! user defined style 1
!    Constant SMW_UDS2   SMW_CLR_WHITE		! user defined style 2
!
! 5) If you want to use ONLY the sounds (no graphics) you should define this constant
!
!    Constant SMW_NOGRAPHICS;
!
!    Before you Include the smw.h library
!
! 6) If you want to use the text styles (examples):
!
!  with description [;
!             print "Text Style ", (s_emph) "Emphasized", "^";
!             print "Text Style ", (s_bold) "Bold", " (like Inform)^";
!             print "Text Style ", (s_pref) "Preformatted", "^";
!             print "Text Style ", (s_fixed) "Fixed", " (like Inform)^";
!             print "Text Style ", (s_head) "Header", "^";
!             print "Text Style ", (s_subhead) "Subheader", "^";
!             print "Text Style ", (s_alert) "Alert", "^";
!             print "Text Style ", (s_reverse) "Reverse", " (like Inform)^";
!             print "Text Style ", (s_note) "Note", "^";
!             print "Text Style ", (s_underline) "Underline/Italic", " (like Inform)^";
!             print "Text Style ", (s_block) "BlockQuote", "^";
!             print "Text Style ", (s_input) "Input", "^";
!       ],
!
!  from these, s_bold, s_fixed, s_reverse and s_underlined, are multiplatform (they'll
!  work compiling for Z or for Glulx). Remember that, in the end, the interpreter will
!  represent each one following the preferences of the user.
!
!  s_bold			bold style (Z/Glulx)
!  s_fixed			fixed font (proportional) style (Z/Glulx)
!  s_reverse		reverse colors for text style (Z/Glulx)
!  s_underline		italic/underline for text style (Z/Glulx)
!
!
! You can use these new simple functions in your game, also :
!
! GRAPHIC FUNCTIONS
! =================
! clearMainWindow()			= clears the main window
! closeAllWindows()			= closes all graphic windows
! wait()					= 3s for a key or for an amount of time
! initializeSMW(h)			= graphic window dimension is set to h=height
! viewImageLeft(image)*		= shows the "image" in the graphic window on the Left
! viewImageCenter(image)*		= shows the "image" in the graphic window (Centered)
! viewImageRight(image)*		= shows the "image" in the graphic window on the Right
!
! * optional parameters: imageWidth, imageHeight (ignored if it is possible to get image info)
!
! AUDIO FUNCTIONS
! ===============
! playSound(channel,sound,length,volume)	= plays a sound/music*
! playMusic(sound,length,volume)			= plays a music*
! playSnd1(sound,length,volume)			= plays a sound*
! playSnd2(sound,length,volume)			= plays a sound*
! silenceAll()						= silences all audio channels
! silenceChannel(channel)				= silences the audio "channel"
! setVolume(val, channel)				= set "val" for volume of the channel
!
! *length can be any number of repetitions of the sound. -1 makes it to be repeated infinitely.
!
! Wait
! ====
! wait() waits for key to be pressed or for an amount of time, in both vm's.
! If a key is pressed during a wait during an amount of time,
! then the wait is cancelled as well.
! It has two optional parameters. The first one would be the text to show before waiting,
! and the second would be the time to wait for in tenths of second. For example:
!
! wait( "[Press a key]", 100 );
!
! will wait for 10 seconds, returning as if the user had pressed a key.
! When a key is pressed, its code is returned, if not, then the returned value is zero.
!
! If the second parameter is omitted, then the wait will be infinite (only a key press
! makes it return). If the two parameters are omitted, then no text is shown and the
! time for waiting for is infinite. If you want to omit the first parameter, but not the
! second one, then you should call wait() such as:
!
! wait( Nothing, 100 );            ! wait( 0, 100 );
!
! In this case, nothing would be written and ten seconds (or a key press) would be the time
! to wait for. Please note that some interpreters can always interpret any way as
! an infinite wait, as they are not obligued to provide temporizers.
!
! (This code was inspired by Zak's library, BajoNivel.h, modified by Baltasar
! and adapted for SMW by Baltasar)
!
!===============================================================================!
! LICENSE
! =======
!
! This file is free software, it can be freely used, copied, distribuited and
! modified. Any modified or unmodified copy of this file distribuited as source
! code must acknowledge the original author and must be freely usable, copyable,
! distributable and modifiable.
! There's absolutely no condition or binding on the distribution as compiled
! binary file.
! This software is distribuited as-is, with NO WARRANTY. The author cannot be
! held as responsable for any damage due directly or indirectly to this file.
!
!===============================================================================!

System_file;

message "Using the SMW 1.32 (Simple Multimedia Wrapper) library by Baltasar (based on SGW by Alessandro Schillaci)";

#Ifdef SMW_NOGRAPHICS;
    message "[SMW] Using ONLY sounds";
#endif;

#Ifdef SMW_PROPORTIONAL;
  message "[SMW] Using proportional graphic window";
#endif;

Constant SMW_VOLUME_HIGH            5;
Constant SMW_VOLUME_NORMAL          3;
Constant SMW_VOLUME_LOW             2;

Constant SMW_MUSICCHAN_ROCK        410;
Constant SMW_MUSICCHANSOUND1_ROCK  411;
Constant SMW_MUSICCHANSOUND2_ROCK  412;
Constant SMW_PICWIN_ROCK           210;         ! Image Location window

! Window types
Constant SMW_GRAPHICS_WIN          100;
Constant SMW_TEXT_WIN              101;

! Position constants - (originally added by Paolo Maroncelli)
Constant SMW_POS_LEFT               1;
Constant SMW_POS_CENTER             2;
Constant SMW_POS_RIGHT              3;
Constant SMW_POS_UP                 4;
Constant SMW_POS_DOWN               5;


! Colors constants - (originally added by Vincenzo Scarpa)
! ------------------------------------------------------------------------ Black
#Ifndef SMW_CLR_BLACK;
    #ifdef TARGET_GLULX;
        Constant SMW_CLR_BLACK                $000000;
    #ifnot;
        Constant SMW_CLR_BLACK                2;
    #endif;
#endif;

! ------------------------------------------------------------------------ White
#Ifndef SMW_CLR_WHITE;
    #ifdef TARGET_GLULX;
        Constant SMW_CLR_WHITE                $ffffff;
    #ifnot;
        Constant SMW_CLR_WHITE                9;
    #endif;
#endif;

! ------------------------------------------------------------------------- Blue
#Ifndef SMW_CLR_BLUE;
    #ifdef TARGET_GLULX;
        Constant SMW_CLR_BLUE                 $0000a0;
    #ifnot;
        Constant SMW_CLR_BLUE                 6;
    #endif;
#endif;

! ------------------------------------------------------------------------ Azure
#Ifndef SMW_CLR_AZURE;
    Constant SMW_CLR_AZURE                    SMW_CLR_BLUE;
#Endif;

! ------------------------------------------------------------------------- Cyan
#Ifndef SMW_CLR_CYAN;
    #ifdef TARGET_GLULX;
        Constant SMW_CLR_CYAN                 $30ffff;
    #ifnot;
        Constant SMW_CLR_CYAN                 8;
    #endif;
#endif;

! ------------------------------------------------------------------------ Green
#Ifndef SMW_CLR_GREEN;
    #ifdef TARGET_GLULX;
        Constant SMW_CLR_GREEN                $30ff30;
    #ifnot;
        Constant SMW_CLR_GREEN                4;
    #endif;
#endif;

! -------------------------------------------------------------------------- Red
#Ifndef SMW_CLR_RED;
    #ifdef TARGET_GLULX;
        Constant SMW_CLR_RED                  $ff3030;
    #ifnot;
        Constant SMW_CLR_RED                  3;
    #endif;
#endif;

! ---------------------------------------------------------------------- Magenta
#Ifndef SMW_CLR_MAGENTA;
    #ifdef TARGET_GLULX;
        Constant SMW_CLR_MAGENTA              $ff30ff;
    #ifnot;
        Constant SMW_CLR_MAGENTA              7;
#endif;

! ----------------------------------------------------------------------- Purple
#Ifndef SMW_CLR_PURPLE;
    #ifdef TARGET_GLULX;
        Constant SMW_CLR_PURPLE               $ff30ff;
    #ifnot;
        Constant SMW_CLR_PURPLE               SMW_CLR_MAGENTA;
    #endif;
#endif;

! ------------------------------------------------------------------------- Pink
#Ifndef SMW_CLR_PINK;
    #ifdef TARGET_GLULX;
        Constant SMW_CLR_PINK                 $ff7fff;
    #ifnot;
        Constant SMW_CLR_PINK                 SMW_CLR_MAGENTA;
    #endif;
#endif;

! ------------------------------------------------------------------------ Brown
#Ifndef SMW_CLR_BROWN;
    #ifdef TARGET_GLULX;
        Constant SMW_CLR_BROWN                $7f3f00;
    #ifnot;
        Constant SMW_CLR_BROWN                SMW_CLR_RED;
    #endif;
#endif;

! ----------------------------------------------------------------------- Yellow
#Ifndef SMW_CLR_YELLOW;
    #ifdef TARGET_GLULX;
        Constant SMW_CLR_YELLOW               $ffff30;
    #ifnot;
        Constant SMW_CLR_YELLOW               5;
    #endif;
#endif;

! ----------------------------------------------------------------------- Orange
#Ifndef SMW_CLR_ORANGE;
    #ifdef TARGET_GLULX;
        Constant SMW_CLR_ORANGE               $ff7f00;
    #ifnot;
        Constant SMW_CLR_ORANGE               SMW_CLR_YELLOW;
    #endif;
#endif;

! ------------------------------------------------------------------------- Grey
#Ifndef SMW_CLR_GREY;
    #ifdef TARGET_GLULX;
        Constant SMW_CLR_GREY                 $bfbfbf;
    #ifnot;
        Constant SMW_CLR_GREY                 SMW_CLR_WHITE;
    #endif;
#endif;

! --------------------------------------------------------------------- Persback
#Ifndef SMW_CLR_PERSBACK;
    #ifdef TARGET_GLULX;
        Constant SMW_CLR_PERSBACK             $110101;
    #ifnot;
        Constant SMW_CLR_PERSBACK             1;
    #endif;
#endif;

! --------------------------------------------------------------------- Perstext
#Ifndef SMW_CLR_PERSTEXT;
    #ifdef TARGET_GLULX;
        Constant SMW_CLR_PERSTEXT             $DDBB99;
    #ifnot;
         Constant SMW_CLR_PERSTEXT            1;
    #endif;
#endif;

! --------------------------------------------------------------------- Perssoft
#Ifndef SMW_CLR_PERSSOFT;
    #ifdef TARGET_GLULX;
        Constant SMW_CLR_PERSSOFT             $665544;
    #ifnot;
        Constant SMW_CLR_PERSSOFT             SMW_CLR_PERSTEXT;
    #endif;
#endif;

! --------------------------------------------------------------------- Persemph
#Ifndef SMW_CLR_PERSEMPH;
    #ifdef TARGET_GLULX;
        Constant SMW_CLR_PERSEMPH             $FFFFDD;
    #ifnot;
        Constant SMW_CLR_PERSEMPH             SMW_CLR_PERSTEXT;
    #endif;
#endif;

! --------------------------------------------------------------------- Pershead
#Ifndef SMW_CLR_PERSHEAD;
    #ifdef TARGET_GLULX;
        Constant SMW_CLR_PERSHEAD             $EEDDAA;
    #ifnot;
        Constant SMW_CLR_PERSHEAD             SMW_CLR_PERSTEXT;
    #endif;
#endif;

! --------------------------------------------------------------------- Persinpu
#Ifndef SMW_CLR_PERSINPU;
    #ifdef TARGET_GLULX;
        Constant SMW_CLR_PERSINPU             $DDEEAA;
    #ifnot;
        Constant SMW_CLR_PERSINPU             SMW_CLR_PERSTEXT;
    #endif;
#endif;

! Playing Colors settings ------------------------------------------------------
#Ifndef SMW_SCBACK;
    Constant SMW_SCBACK                SMW_CLR_PERSBACK;
#endif;
#Ifndef SMW_SHBACK;
    Constant SMW_SHBACK                SMW_CLR_PERSBACK;
#endif;
#Ifndef SMW_SCTEXT;
    Constant SMW_SCTEXT                SMW_CLR_PERSTEXT;
#endif;
#Ifndef SMW_SCUDS1;
    Constant SMW_SCUDS1                SMW_CLR_PERSSOFT;
#endif;
#Ifndef SMW_SCUDS2;
    Constant SMW_SCUDS2                SMW_CLR_PERSSOFT;
#endif;
#Ifndef SMW_SCEMPH;
    Constant SMW_SCEMPH                SMW_CLR_PERSEMPH;
#endif;
#Ifndef SMW_SCPREF;
    Constant SMW_SCPREF                SMW_CLR_PERSTEXT;
#endif;
#Ifndef SMW_SCHEAD;
    Constant SMW_SCHEAD                SMW_CLR_PERSHEAD;
#endif;
#Ifndef SMW_SCINPU;
    Constant SMW_SCINPU                SMW_CLR_PERSINPU;
#endif;
#Ifndef SMW_SCNOTE;
    Constant SMW_SCNOTE                SMW_CLR_PERSINPU;
#endif;

object SMW
private
    MaxNumberOfWindows 10,
    maxWindows 0,
    subWindows      0 0 0 0 0 0 0 0 0 0,
    subWinRocks     230 231 232 233 234 235 236 237 238 239,
    subImg          0 0 0 0 0 0 0 0 0 0,
    posOfGraphicsWindow	     SMW_POS_UP,
    sizeOfGraphicsWindow     0,		! Graphic's Window size, 0 inlined graphics
    currentSound             0,
    gg_VolumeSupport     false,		! Change Volume supported?
    picWin                   0,			! Image Location window
    currentPic               0,
    currentPicPos            0,
    currentPicWidth          0,
    currentPicHeight         0,
    inlinedGraphics 	  false,
with
    music                    0,			! Music Channel
    chan1                    0,			! Channel 1 sound effects
    chan2                    0,			! Channel 2 sound effects

    ! The functionality of the following function has been previously represented
    ! as size > 0, gg_mainwin == picwin,  and other hackings,
    ! only to run into a lot of problems
    ! due to the indentifyGlkObject() function, in which window information
    ! cannot be retrieved. Since 1.31, it has been preferred for clarity
    ! as well as reliability to clearly store this information
	    
    usingInlinedGraphics [;
	return self.inlinedGraphics;
    ],
    
    usingProportionalHeight [;
	#Ifdef SMW_PROPORTIONAL;
		return true;
	#Ifnot;
		return false;
	#Endif;
    ],

    getSubWindowCount [;
        return self.maxWindows;
    ],

    getSubWindow [ i;
        if ( i < self.maxWindows )
                return self.&subWindows-->i;
        else    return Nothing;
    ],

    getSubWindowRock [ i;
        if ( i < self.maxWindows )
                return self.&subWinRocks-->i;
        else    return Nothing;
    ],

    chkAllGlkReferences[ i;
        ! Subwindows
        for( i = 0: i < self.maxWindows: ++i) {
            if ( self.&subWindows-->i == Nothing ) {
                print "^*** ERROR: Subwindow #", i, " does not have a valid Glk reference.^";
                break;
            }
        }

        ! Reset graphic
        if ( self.picWin == Nothing ) {
            print "^*** ERROR: Graphics window does not have a valid Glk reference.^";
        }
    ],

    resetAllGlkReferences [ i;
        ! Reset subwindows
        for( i = 0: i < self.maxWindows: ++i) {
            self.&subWindows-->i = Nothing;
        }

        ! Reset graphic
        self.picWin = Nothing;

        ! Reset sounds
        self.currentSound = Nothing;
        self.music        = Nothing;
        self.chan1        = Nothing;
        self.chan2        = Nothing;
    ],

    updateSubWindowRef [ rock ref toret i;
        toret = false;

        for(i = 0: i < self.maxWindows: ++i) {
            if ( self.&subWinRocks-->i == rock ) {
                toret = true;
                self.&subWindows-->i = ref;
            }
        }

        return toret;
    ],
    setGraphicsWindow [g;
        self.picWin = g;
    ],

    getGraphicsWindow [;
        return self.picWin;
    ],

    getMainWindow [;
        #ifdef TARGET_GLULX;
            return gg_mainwin;
        #Ifnot;
            return Nothing;
        #Endif;
    ],

    getStatusWindow [;
        #ifdef TARGET_GLULX;
            return gg_statuswin;
        #Ifnot;
            return Nothing;
        #Endif;
    ],

    getPosOfGraphicsWindow [;
	return self.posOfGraphicsWindow;
    ],

    getSizeOfGraphicsWindow [;
    #IFDEF SMW_PROPORTIONAL;
    	return self.getWindowHeight( self.picWin );
    #ifnot;
    	return self.sizeOfGraphicsWindow;
    #endif;
    ],

    getWidthOfGraphicsWindow [;
        return self.getWindowWidth( self.picWin );
    ],

    getCurrentPic [;
        return self.currentPic;
    ],

    init [ h pos;
        #Ifdef TARGET_GLULX;
	    #Ifdef SMW_NOGRAPHICS;
		h = 0;				! Force inlined graphics (actually, no graphics at all)
	    #Endif;
	    
	    ! Set size & pos of the graphics window
            self.sizeOfGraphicsWindow = h;
	    self.inlinedGraphics = ( h == 0 );
	    
	    if ( pos == 0 ) {
		pos = SMW_POS_UP;
	    }
	    self.posOfGraphicsWindow = pos;

            ! Music and sounds
            if ( self.music == Nothing ) {
                self.music = glk_schannel_create( SMW_MUSICCHAN_ROCK );
            }

            if ( self.chan1 == Nothing ) {
                self.chan1 = glk_schannel_create( SMW_MUSICCHANSOUND1_ROCK );
            }

            if ( self.chan2 == Nothing ) {
                self.chan2 = glk_schannel_create( SMW_MUSICCHANSOUND2_ROCK );
            }

            ! Init multimedia
           !self.testGlulx();           		! Test about Interpreter's performances
            self.closeAllSubwindows();  	! Closing all windows
            self.silenceAudioChannels();	! Silence all audio channels
            self.initGlulx( h, pos );   		! Initialize the glulx system
            self.cleanMainWindow();
            self.setCurrentWindow( gg_mainwin );
        #ifnot;
            self.picWin  = 0;
            self.chan1   = 0;
            self.music   = 0;
            self.chan2   = 0;
            self.maxWindows = 0;
	    self.sizeOfGraphicsWindow = 0;
	    self.posOfGraphicsWindow = 0;
	    self.inlinedGraphics = true;
            h = 0;
	    pos = SMW_POS_UP;

            self.initZ();                ! Initialize the Z VM system
        #endif;

        return h;
    ],

    getWindowHeight [ win toret;
        toret = 0;

        #Ifdef TARGET_GLULX;
            glk_window_get_size( win, gg_arguments, gg_arguments+WORDSIZE );
            toret = gg_arguments-->1;
        #ifnot;
            win = 0;
        #endif;

        return toret;
    ],

    getWindowWidth [ win toret;
        toret = 0;

        #Ifdef TARGET_GLULX;
            glk_window_get_size( win, gg_arguments, gg_arguments+WORDSIZE );
            toret = gg_arguments-->0;
        #ifnot;
            win = 0;
        #endif;

        return toret;
    ],

    getImageHeight [ img toret;
        toret = 0;

        #Ifdef TARGET_GLULX;;
            glk_image_get_info( img, gg_arguments, gg_arguments+WORDSIZE );
            toret = gg_arguments-->1;
        #ifnot;
            img = 0;
        #endif;

        return toret;
    ],

    getImageWidth [ img toret;
        toret = 0;

        #Ifdef TARGET_GLULX;
            glk_image_get_info( img, gg_arguments, gg_arguments+WORDSIZE );
            toret = gg_arguments-->0;
        #ifnot;
            img = 0;
        #endif;

        return toret;
    ],

    ! Get image size, if possible
    setImageSize [ image_width image_height;
      #Ifdef TARGET_GLULX;
            if ( glk_image_get_info( self.currentPic, gg_arguments, gg_arguments+WORDSIZE ) )
            {
                self.currentPicWidth  = gg_arguments-->0;
                self.currentPicHeight = gg_arguments-->1;
            }
            else {
                self.currentPicWidth  = image_width;
                self.currentPicHeight = image_height;
            }
      #ifnot;
            self.currentPicWidth = image_width;
            self.currentPicHeight = image_height;
      #endif;
    ],

! --- Graphics functions -------------------------------------------------------
! Centralized visualization routine - (originally added by Paolo Maroncelli)

    viewSubImage [ i g;
        #Ifdef TARGET_GLULX;
                #Ifndef SMW_NOGRAPHICS;
                if ( i < self.maxWindows )
                {
			    g = self.&subImg-->i;

			    drawImageInSubWindow( i, g );

                } else {
			print "^ERROR: trying to view a sub imag #",
				i ,
			    " > max number of images.^"
		       ;
		}
		#Ifnot;
		i = g;
                #Endif;
        #Ifnot;
            g = i;
        #Endif;
    ],

     viewImage [winWidth winHeight x_pos y_pos gwin cpic image_width image_height ratiox ratioy;

      #Ifdef TARGET_GLULX;
            #Ifndef SMW_NOGRAPHICS;
                cpic      = self.getCurrentPic();
                gwin      = self.getGraphicsWindow();
                winWidth  = self.getWidthOfGraphicsWindow();
                winHeight = self.getSizeOfGraphicsWindow();

                #ifdef SMW_PROPORTIONAL;

                    image_height = self.getImageHeight(self.currentPic);
                    image_width = self.getImageWidth(self.currentPic);


                    winWidth = winWidth * 256;
                    winHeight = winHeight * 256;



	                if (image_width == 0) ratiox = 0; else ratiox = winWidth / image_width;
	                if (image_height == 0) ratioy = 0; else ratioy = winHeight / image_height;


                    glk_window_clear( gwin );

                    if (ratiox < ratioy)
                  	{
                  		image_width = image_width * ratiox / 256;
                  		image_height = image_height * ratiox / 256;
                  	}
                  	else
                  	{
                  		image_width = image_width * ratioy / 256;
                  		image_height = image_height * ratioy / 256;
                  	}





                    switch ( self.currentPicPos )
                    {
	                        SMW_POS_LEFT:   x_pos = 0;
	                        SMW_POS_CENTER: x_pos = ( winWidth/256 - image_width  ) / 2;
	                        SMW_POS_RIGHT:  x_pos = winWidth/256 - image_width;
	                }


	                ! Set vertical position
	                y_pos = ( winHeight/256 - image_height ) / 2;

	                ! Test locations correctness
	                if ( y_pos < 0 ) {
	                    y_pos = 0;
	                }
	                if ( x_pos < 0 ) {
	                    x_pos = 0;
	                }


	                ! Show image
	                if ( gwin ~= Nothing
	                  && glk_gestalt( gestalt_Graphics, 0 ) )
	                {
	                    glk_image_draw_scaled( gwin, self.currentPic, x_pos, y_pos, image_width, image_height );
	                }


                #ifnot;
                    image_width = ratiox = ratioy = image_height = 0;

	                if ( gwin ~= gg_mainwin ) {
	                    glk_window_clear( gwin );
	                    switch ( self.currentPicPos ) {
	                        SMW_POS_LEFT:   x_pos = 0;
	                        SMW_POS_CENTER: x_pos = ( winWidth - self.currentPicWidth ) / 2;
	                        SMW_POS_RIGHT:  x_pos = winWidth - self.currentPicWidth;
	                    }
	                } else {
	                    switch ( self.currentPicPos ) {
	                        SMW_POS_LEFT:   x_pos = imagealign_MarginLeft;
	                        SMW_POS_CENTER: x_pos = imagealign_InlineCenter;
	                        SMW_POS_RIGHT:  x_pos = imagealign_MarginRight;
	                    }
	                }



	                ! Set vertical position
	                y_pos = ( winHeight - self.currentPicHeight ) / 2;

	                ! Test locations correctness
	                if ( y_pos < 0 ) {
	                    y_pos = 0;
	                }
	                if ( x_pos < 0 ) {
	                    x_pos = 0;
	                }

	                ! Show image
	                if ( gwin ~= Nothing
	                  && glk_gestalt( gestalt_Graphics, 0 ) )
	                {


	                    glk_image_draw( gwin, self.currentPic, x_pos, y_pos );
	                }
                #endif;
	    #Ifnot;
	    gwin = cpic = winWidth = 0;
            winHeight = 0;
	    ratiox = ratioy = 0;
	    image_width = image_height = 0;
            x_pos = 0;
            y_pos = 0;
            #endif;
      #ifnot;
         gwin = cpic = winWidth = 0;
         winHeight = 0;
	 ratiox = ratioy = 0;
	 image_width = image_height = 0;
         x_pos = 0;
         y_pos = 0;
      #endif;

      return x_pos;
     ],

    ! Close all windows
    closeAllSubwindows [ gwin;
      #Ifdef TARGET_GLULX;
            #Ifndef SMW_NOGRAPHICS;
                ! Close all subwindows ----------------------------------------
                for( gwin = 0: gwin < self.maxWindows: ++gwin) {
                    glk_window_close( self.&subWindows-->gwin, 0 );
                    self.&subWindows-->gwin = Nothing;
                }
                self.maxWindows = 0;

                ! Close picture window ----------------------------------------
                gwin = self.getGraphicsWindow();

                if ( gwin ~= Nothing
                  && gwin ~= gg_mainwin )
                {
                    glk_window_close( gwin, 0 );
                }

                self.setGraphicsWindow( Nothing );

                ! Close status bar window -------------------------------------
                if ( gg_statuswin ~= Nothing ) {
                    glk_window_close( gg_statuswin, 0 );
                    gg_statuswin = Nothing;
                }

                ! Close & Reopen main window ----------------------------------
                glk_window_close( gg_mainwin, 0 );
                gg_mainwin = glk_window_open( 0, 0, 0, wintype_TextBuffer, GG_MAINWIN_ROCK );

                SMW.setMainWindowAsCurrent();
            #endif;
      #endif;

      gwin = 0;
    ],

    ! Clean windows
    cleanSubWindow[ i w;
        w = self.getSubWindow( i );

        if ( w ~= Nothing ) {
            self.cleanWindow( w );
        }
    ],

    cleanWindow [ winId;
        #Ifdef TARGET_GLULX;
            #Ifndef SMW_NOGRAPHICS;
                glk_window_set_background_color( winId, SMW_SCBACK );
                glk_window_clear( winId );
                glk_window_set_background_color( winId, SMW_SCBACK );
                glk_window_clear( winId );
	    #ifnot;
		winId = 0;
            #endif;
        #Ifnot;
            winId = 0;
            SMW.cleanMainWindow();
        #Endif;
    ],

    cleanMainWindow [;
        #Ifdef TARGET_GLULX;
            self.cleanWindow( gg_mainwin );
            self.cleanWindow( self.getGraphicsWindow() );
        #ifnot;
            @erase_window -1;
        #endif;
    ],

    ! Redraws an image
    redrawGraphicsWindows [i;
        ! Main pic window
        self.viewImage();

        ! View image in other windows
        for(i = 0: i < self.maxWindows: ++i) {
            self.viewSubImage( i );
        }
    ],

! --- Audio functions ----------------------------------------------------------

! Plays the sound "sound" for the channel "channel" , with "length" and "volume"
    play [channel sound length volume;
          ! Give default values
          if ( length == 0 ) {
              length = 1;
          }

          if ( volume == 0 ) {
              volume = SMW_VOLUME_NORMAL;
          }

          if ( channel == 0 ) {
              channel = self.chan1;
          }

          if ( length ~= -1
            && length < 1 )
          {
            print "^*** SMW: playSound() - length parameter must be -1 (inf. loop)";
            print "or a non-zero positive number, not ", length, " ***^";
            return -1;
          }

          if ( sound == Nothing ) {
             print "^*** SMW: playSound() - sound to play cannot be zero ***^";
             return -1;
          }

      #ifdef TARGET_GLULX;
          if ( channel ~= Nothing
            && glk_gestalt( gestalt_Sound, 0 )
            && glk_gestalt( gestalt_SoundVolume, 0 ) )
          {
            self.currentSound = sound;
            glk_schannel_stop( channel );
            self.setVolumeForChannel( volume, channel );
            glk_schannel_play_ext( channel, sound, length, 0 );
           }
      #ifnot;
           volume = channel = 0;
      #endif;

      return sound;
    ],

    ! Silences all the audio channels
    silenceAudioChannels [;
       self.resetAudioChannels();
    ],

    ! Silences the channel "channel"
    silenceAudioChannel [ channel;
      #ifdef TARGET_GLULX;
            if ( self.channel ~= Nothing
              && glk_gestalt( gestalt_Sound, 0 ) )
            {
                glk_schannel_stop( self.channel );
            }
      #endif;

      return channel;
    ],

    ! Reset all audio channels
    resetAudioChannels [;
      #ifdef TARGET_GLULX;
        if ( glk_gestalt( gestalt_Sound, 0 ) ) {
            glk_schannel_stop( self.music );
            glk_schannel_stop( self.chan1 );
            glk_schannel_stop( self.chan2 );
        }
      #endif;
    ],

    ! Set a volume for the channel
    setVolumeForChannel [ val channel;
      if ( val < 0 ) {
         print "^*** SMW: setVolume() - volume parameter must be positive or zero ***^";
         return -1;
      }

      #ifdef TARGET_GLULX;
            if ( self.gg_VolumeSupport
              && glk_gestalt( gestalt_Sound, 0 ) )
            {
                if (val > 0) glk_schannel_set_volume(channel, val * 16384);
            }
      #endif;

      return channel;
    ],

    ! Test the Glulx Interpreter's performances
    testGlulx [;
        #Ifdef TARGET_GLULX;
        #Ifndef SMW_NOGRAPHICS;
            if ( ~~glk_gestalt( gestalt_Graphics, 0 ) ) {
                print "^[This Interpreter doesn't support graphics.]^";
            }
        #endif;

        if ( ~~glk_gestalt( gestalt_GraphicsTransparency, 0 ) ) {
            print "^[This Interpreter doesn't support transparency.]^";
        }

        if ( ~~glk_gestalt( gestalt_Version, 0 ) ) {
            print "^[This Interpreter doesn't support this version.]^";
        }

        if ( ~~glk_gestalt( gestalt_Sound, 0 ) ) {
            print "^[This Interpreter doesn't support sound.]^";
        }

        if ( ~~glk_gestalt( gestalt_SoundVolume, 0 ) ) {
            print "^[This Interpreter doesn't support sound volume.]^";
        }

        if ( ~~glk_gestalt( gestalt_SoundMusic, 0 ) ) {
            print "^[This Interpreter doesn't support mod music.]^";
        }

        if ( ~~glk_gestalt( gestalt_SoundNotify, 0 ) ) {
            print "^[This Interpreter doesn't support sound notify.]^";
        }

        if ( ~~glk_gestalt( gestalt_Timer, 0 ) ) {
            print "^[This Interpreter doesn't support timer.]^";
        }

        if ( ~~glk_gestalt( gestalt_Hyperlinks, 0 ) ) {
            print "^[This Interpreter doesn't support hyperlinks.]^";
        }
        #endif;
    ],

    createGraphicsWindow [ win size pos;
        return self.createWindow( win, size, pos, SMW_GRAPHICS_WIN );
    ],

    createTextWindow [ win size pos;
        return self.createWindow( win, size, pos, SMW_TEXT_WIN );
    ],

    createWindow [ win size pos type toret;
        #Ifdef TARGET_GLULX;
            if ( self.maxWindows >= self.MaxNumberOfWindows ) {
                print "^*** ERROR *** max number of subwindows reached.^";
            }

            ! Determine position
            if ( pos == SMW_POS_LEFT ) {
                pos = winmethod_Left;
            }
            else
            if ( pos == SMW_POS_RIGHT ) {
                pos = winmethod_Right;
            }
            else
            if ( pos == SMW_POS_UP ) {
                pos = winmethod_Above;
            }
            else
            if ( pos == SMW_POS_DOWN ) {
                pos = winmethod_Below;
            }
            else pos = winmethod_Below;

            ! Determine type
            if ( type == SMW_GRAPHICS_WIN ) {
                type = wintype_Graphics;
            }
            else
            if ( type == SMW_TEXT_WIN ) {
                type = wintype_TextBuffer;
            }
            else type = wintype_TextBuffer;

            toret = glk_window_open(
                win,
                ( pos + winmethod_Proportional ),
                size,
                type,
                self.&subWinRocks-->self.maxWindows )
            ;

            if ( toret ~= Nothing ) {
                self.&subWindows-->self.maxWindows = toret;
                self.maxWindows++;
                glk_request_hyperlink_event( toret );
            }
        #Ifnot;
            win   =  Nothing;
            size  =  Nothing;
            type  =  Nothing;
            pos   =  Nothing;
            toret =  Nothing;
        #Endif;

        return toret;
    ],

    ! Z VM Inizialize function
    initZ [;
        #Ifndef TARGET_GLULX;
            @set_colour SMW_SCTEXT SMW_SCBACK;
            @erase_window -1;
        #endif;
    ],

    createMainGraphicsWindow [ value proportional side winPos winSize;
	#Ifdef TARGET_GLULX;
	! Choose side
	winPos = winmethod_Above;
	if ( side == SMW_POS_LEFT ) {
		winPos = winmethod_Left;
	}
	else
	if ( side == SMW_POS_RIGHT ) {
		winPos = winmethod_Right;
	}
	else
	if ( side == SMW_POS_DOWN ) {
		winPos = winmethod_Below;
	}

	! Choose proportional
	winSize = winmethod_Fixed;
	if ( proportional ) {
		winSize = winmethod_Proportional;
	}

	! Create it
	self.setGraphicsWindow(
            glk_window_open(
                    gg_mainwin,
                    ( winPos + winSize ),
                    value,
                    wintype_Graphics,
                    SMW_PICWIN_ROCK
            )
        );
	#Ifnot;
	value = 0;
	proportional = 0;
	side = 0;
	winPos = 0;
	winSize = 0;
	#Endif;
    ],

    initGlulx [h pos gwin;
        #Ifdef TARGET_GLULX;
        #Ifndef SMW_NOGRAPHICS;

            ! Status window ---------------------------------------------------
            if ( gg_statuswin == Nothing ) {
                glk_window_close(  gg_statuswin, 0 );
            }

            gg_statuswin = glk_window_open(
                                gg_mainwin,
                                ( winmethod_Above + winmethod_Proportional ),
                                1,
                                wintype_TextGrid,
                                GG_STATUSWIN_ROCK)
            ;

            ! Graphics window -------------------------------------------------
            if ( h > 0 ) {
                gwin = self.getGraphicsWindow();
                if ( gwin ~= Nothing
                  && gwin ~= gg_mainwin )
                {
                    glk_window_close( gwin, 0 );
                }

                #Ifdef SMW_PROPORTIONAL;
			self.createMainGraphicsWindow( h, true, pos );
                #ifnot;
                	self.createMainGraphicsWindow( h, false, pos );
                #endif;


            } else {
                    ! inlined graphics (no exclusive window for graphics)
                    self.setGraphicsWindow( gg_mainwin );
	    }

            ! Set main back color as background colour for all windows
            self.maxWindows = 0;
            glk_request_hyperlink_event( gg_mainwin );
            glk_window_set_background_color( gg_mainwin, SMW_SCBACK );
            glk_window_clear( gg_mainwin );
            glk_window_set_background_color( gg_statuswin, SMW_SCBACK );
            glk_window_clear( gg_statuswin );
            glk_window_set_background_color( self.getGraphicsWindow(), SMW_SCBACK );
            glk_window_clear( self.getGraphicsWindow() );
	#ifnot;
	    h = gwin = pos;
        #endif;
        #ifnot;
            h = gwin = pos;
        #endif;
    ],

    drawSubWindowImage [i grf win x_pos y_pos;
        if ( i >= self.maxWindows ) {
            print "^ERROR: Tried to show a subimage > available subwindows^";
        }

        #ifdef TARGET_GLULX;
            win = self.&subWindows-->i;

            if ( grf == Nothing ) {
                return;
            }

            self.&subImg-->i = grf;

            ! Calculate position
            x_pos = ( SMW.getWindowWidth( win )
                        - SMW.getImageWidth( grf )
                    ) / 2
            ;
            y_pos = ( SMW.getWindowHeight( win )
                        - SMW.getImageHeight( grf )
                    ) / 2
            ;

            ! Test locations correctness
            if ( y_pos < 0 ) {
                y_pos = 0;
            }
            if ( x_pos < 0 ) {
                x_pos = 0;
            }

            ! Show image
            if ( glk_gestalt( gestalt_Graphics, 0 ) ) {
                self.cleanWindow( win );
                glk_image_draw( win, grf, x_pos, y_pos );
            }
        #ifnot;
            x_pos = y_pos = win = grf = 0;
        #endif;
    ],

! --- Wait for a key press or an amout of time ---------------------------------
    waitForKey [ msg delay k;
        if ( msg ~= Nothing ) {
                print (string) msg;
        }

      #Ifdef TARGET_GLULX;
        glk_request_timer_events( delay * 100 );
        glk_request_char_event( gg_mainwin );

        while( true )
        {
            glk_select( gg_arguments );

            if ( gg_arguments-->0 == evtype_Arrange or evtype_Redraw) {
                SMW.redrawGraphicsWindows();
            }

            if ( gg_arguments-->0 == evtype_MouseInput or evType_CharInput ) {
                if ( gg_arguments-->0 == evtype_MouseInput ) {
                    glk_cancel_char_event( gg_mainwin );
                }
            }

            if ( ( gg_arguments-->0 ) ==  evType_CharInput ) break;

            if ( ( gg_arguments-->0 ) == 1 )
            {
                glk_cancel_char_event( gg_mainwin );
                glk_request_timer_events( 0 );         ! cancel timer events
                return 0;
            }
        }

        SMW.activateHyperlinksForAllWindows();
        k = gg_arguments-->2;
      #Ifnot;
        if ( delay == 0 )
                @read_char 1 0 0 k;
        else    @read_char 1 delay SMWretWaitFn k;
      #endif;

      return k;
    ],

    setPic [ image pos image_width image_height;
          SMW.currentPic    = image;
          SMW.currentPicPos = pos;
          SMW.setImageSize( image_width, image_height );
    ],

    setCurrentSubWindow[ i;
        if ( i < self.getSubWindowCount() ) {
            self.setCurrentWindow( self.getSubWindow( i ) );
        }
    ],

    setCurrentWindow [ w;
        if ( w ~= Nothing ) {
            #Ifdef TARGET_GLULX;
                glk_set_window( w );
            #Endif;
        }
    ],

    setMainWindowAsCurrent [;
        #Ifdef TARGET_GLULX;
            self.setCurrentWindow( gg_mainwin );
        #Endif;
    ],

    activateHyperLinksForAllWindows [ i;
        #Ifdef TARGET_GLULX;
            glk_request_hyperlink_event( gg_mainwin );
            glk_request_hyperlink_event( self.picWin );

            for(i = 0: i < self.maxWindows: ++i) {
                glk_request_hyperlink_event( self.&subWindows-->i );
            }
        #Ifnot;
            i = 0;
        #Endif;
    ],
; ! End of SMW object

! --- Wait for a key press or an amout of time ---------------------------------
[ wait msg delay;
    return SMW.waitForKey( msg, delay );
];

[ SMWretWaitFn;
    rtrue;
];

! --- Texts functions - (originally added by Vincenzo Scarpa) ------------------

[ s_normal txt;
   #Ifdef TARGET_GLULX;
       glk_set_style( style_Normal );
   #ifnot;
       style roman;
       font on;
   #endif;

   if ( txt ~= Nothing ) {
	print (string) txt;
   }
];

! Text in Bold style (like Inform)
[ s_bold txt;
   #Ifdef TARGET_GLULX;
	s_emph();
   #ifnot;
       style bold;
   #endif;

   if ( txt ~= Nothing ) {
	print (string) txt;
	s_normal();
   }
];

! Text in Reverse style (like Inform)
[ s_reverse txt;

    #Ifdef TARGET_GLULX;
       s_alert();
    #ifnot;
       style reverse;
    #endif;

    if ( txt ~= Nothing ) {
	print (string) txt;
	s_normal();
    }
];

! Text in Fixed style (like Inform)
[ s_fixed txt;
    #Ifdef TARGET_GLULX;
       s_pref();
    #ifnot;
       font off;
    #endif;

    if ( txt ~= Nothing ) {
	print (string) txt;
	s_normal();
    }
];

! Text in Underline/Italic style (like Inform)
[ s_underline txt;
    #Ifdef TARGET_GLULX;
       s_note();
    #ifnot;
       style underline;
    #endif;

    if ( txt ~= Nothing ) {
	print (string) txt;
	s_normal();
    }
];

! Text in Emphasized style
[ s_emph txt;
  #Ifdef TARGET_GLULX;
       glk_set_style( style_Emphasized );
  #ifnot;
       style bold;
  #endif;

  if ( txt ~= Nothing ) {
	print (string) txt;
	s_normal();
  }
];

! Text in Preformatted style
[ s_pref txt;
  #Ifdef TARGET_GLULX;
       glk_set_style(style_Preformatted);
  #ifnot;
       font off;
  #endif;

  if ( txt ~= Nothing ) {
	print (string) txt;
	s_normal();
  }
];

! Text in Header style
[ s_head txt;
  #Ifdef TARGET_GLULX;
       glk_set_style( style_Header );
  #endif;

  if ( txt ~= Nothing ) {
	print (string) txt;
	s_normal();
  }
];

! Text in Subheader style
[ s_subhead txt;
  #Ifdef TARGET_GLULX;
       glk_set_style( style_Subheader );
  #endif;

  if ( txt ~= Nothing ) {
	print (string) txt;
	s_normal();
  }
];

! Text in Alert style
[ s_alert txt;
  #Ifdef TARGET_GLULX;
       glk_set_style( style_Alert );
  #endif;

  if ( txt ~= Nothing ) {
	print (string) txt;
	s_normal();
  }
];

! Text in Note style
[ s_note txt;
  #Ifdef TARGET_GLULX;
       glk_set_style( style_Note );
  #endif;

  if ( txt ~= Nothing ) {
	print (string) txt;
	s_normal();
  }
];

! Text in BlockQuote style
[ s_block txt;
  #Ifdef TARGET_GLULX;
       glk_set_style( style_BlockQuote );
  #endif;


  if ( txt ~= Nothing ) {
	print (string) txt;
	s_normal();
  }
];

! Text in Input style
[ s_input txt;
  #Ifdef TARGET_GLULX;
       glk_set_style( style_Input );
  #endif;


  if ( txt ~= Nothing ) {
	print (string) txt;
	s_normal();
  }
];


! Graphics functions -----------------------------------------------------------
! Shows any image at the center of any (graphics) window

! View an image centered on any subwindow
[ drawImageInSubWindow i grf;
    return SMW.drawSubWindowImage( i, grf );
];

! View an image in any pos
[ drawImage img pos image_width image_height;
  SMW.setPic( img, pos, image_width, image_height );

  #Ifdef TARGET_GLULX;
        SMW.viewImage();
  #endif;
];

! View an image on the left of the main graphic window
[ viewImageLeft image image_width image_height;
  SMW.setPic( image, SMW_POS_LEFT, image_width, image_height );

  #Ifdef TARGET_GLULX;
        SMW.viewImage();
  #endif;

  return image;
];

! View an image on the center of the main graphic window
[ viewImageCenter image image_width image_height;
  SMW.setPic( image, SMW_POS_CENTER, image_width, image_height );

  #Ifdef TARGET_GLULX;
        SMW.viewImage();
  #endif;

  return image;
];

! View an image on the right of the main graphic window
[ viewImageRight image image_width image_height;
  SMW.setPic( image, SMW_POS_RIGHT, image_width, image_height );

  #Ifdef TARGET_GLULX;
      SMW.viewImage();
  #endif;

  return image;
];

! Close all windows
[ closeAllWindows;
    SMW.closeAllSubwindows();
];

! Clean the main window
[ clearMainWindow;
    SMW.cleanMainWindow();
];

! Sound functions --------------------------------------------------------------
! Plays the sound "sound" for the channel "channel" , with "length" and "volume"
[ playSound channel sound length volume;
    SMW.play( channel, sound, length, volume );
];

[ playMusic sound length volume;
    SMW.play( SMW.music, sound, length, volume );
];

[ playSnd1 sound length volume;
    SMW.play( SMW.chan1, sound, length, volume );
];

[ playSnd2 sound length volume;
    SMW.play( SMW.chan2, sound, length, volume );
];

! Silences all the audio channels
[ silenceAll;
    SMW.silenceAudioChannels();
];

! Silences the channel "channel"
[ silenceChannel channel;
    SMW.silenceAudioChannel( channel );
];

! Reset all audio channels
[ resetMusicChannels;
    SMW.resetAudioChannels();
];

[ resetMusicChannel;
    SMW.resetAudioChannels();
];

[ resetAllAudioChannels;
    SMW.resetAudioChannels();
];

! Set a volume for the channel
[ setVolume val channel;
    return SMW.setVolumeForChannel( val, channel );
];

! === GLULX functions ==========================================================
#Ifndef TARGET_GLULX;
[ setBeginHyperlink hlid;
    hlid = 0;
];

[ setEndHyperLink;
];

#Ifnot;

[ manageHyperlinks hyperlink_num;
    hyperlink_num = 0;
    return "";
];

[ setBeginHyperlink hlid;
    glk_set_hyperlink( hlid );
];

[ setEndHyperLink;
    glk_set_hyperlink( 0 );
];

[ HandleGlkEvent event newcmd abortres cmdlen bufferlen;
    switch ( event-->0 ) {
        evtype_Redraw,
        evtype_Arrange:              ! redraw window
            SMW.redrawGraphicsWindows();
        evtype_SoundNotify:          ! non-stop music
            glk_schannel_play_ext( self.music, self.currentSound, 1, 1 );
        evtype_Hyperlink:
            ! Obtain current buffer length
            glk_cancel_line_event( gg_mainwin, abortres );
            bufferlen = abortres-->2;
            if ( buffer-->bufferlen == 10 ) {
                bufferlen--;
            }

            ! Obtain new command from hyperlink
            newcmd = manageHyperlinks( event-->2 );

            if ( ~~( newcmd ofclass string ) ) {
                ! Print current buffer in abortres
                PrintAnyToArray(
                                abortres + WORDSIZE,
                                INPUT_BUFFER_LEN - WORDSIZE,
                                buffer
                );
            }
            else bufferlen = 0;

            ! Print new command in abortres
            cmdlen = PrintAnyToArray(
                            abortres + WORDSIZE + bufferlen,
                            INPUT_BUFFER_LEN - WORDSIZE - bufferlen,
                            newcmd
            );
            abortres-->0 = cmdlen + bufferlen;

            ! Update screen
            !print "> ";
            !glk_set_style( style_Input );
            !printAnything( abortres );
            !glk_set_style( style_Normal );
            !new_line;

            ! Re-engage hyperlinks and return, cancelling current line input
            glk_request_hyperlink_event( event-->1 );
            return 2;
    }

    rtrue;
];

! Glk window initialization entry point ----------------------------------------
[ InitGlkWindow winrock;
    switch ( winrock ) {
      GG_MAINWIN_ROCK:
            glk_stylehint_set( gg_mainwin, style_Normal, stylehint_TextColor, SMW_SCTEXT );
            glk_stylehint_set( gg_mainwin, style_Normal, stylehint_BackColor, SMW_SCBACK );
            glk_stylehint_set( gg_mainwin, style_Normal, stylehint_Justification, stylehint_just_LeftRight);
            glk_stylehint_set( gg_mainwin, style_Emphasized, stylehint_Weight, 1 );
            glk_stylehint_set( gg_mainwin, style_Emphasized, stylehint_Oblique, 0 );
            glk_stylehint_set( gg_mainwin, style_Emphasized, stylehint_TextColor, SMW_SCEMPH );
            glk_stylehint_set( gg_mainwin, style_Emphasized, stylehint_BackColor, SMW_SCBACK );
            glk_stylehint_set( gg_mainwin, style_Header, stylehint_TextColor, SMW_SCHEAD );
            glk_stylehint_set( gg_mainwin, style_Header, stylehint_BackColor, SMW_SHBACK );
            glk_stylehint_set( gg_mainwin, style_Subheader, stylehint_TextColor, SMW_SCHEAD );
            glk_stylehint_set( gg_mainwin, style_Subheader, stylehint_BackColor, SMW_SHBACK );
            glk_stylehint_set( gg_mainwin, style_Alert, stylehint_TextColor, SMW_SCBACK );
            glk_stylehint_set( gg_mainwin, style_Alert, stylehint_BackColor, SMW_SCEMPH );
            glk_stylehint_set( gg_mainwin, style_Note, stylehint_TextColor, SMW_SCNOTE );
            glk_stylehint_set( gg_mainwin, style_Note, stylehint_BackColor, SMW_SCBACK );
            glk_stylehint_set( gg_mainwin, style_Note, stylehint_Weight, -1 );
            glk_stylehint_set( gg_mainwin, style_Note, stylehint_Oblique, 1 );
            glk_stylehint_set( gg_mainwin, style_Blockquote, stylehint_TextColor, SMW_SCPREF );
            glk_stylehint_set( gg_mainwin, style_Blockquote, stylehint_BackColor, SMW_SCBACK );
            glk_stylehint_set( gg_mainwin, style_Input, stylehint_TextColor, SMW_SCINPU );
            glk_stylehint_set( gg_mainwin, style_Input, stylehint_BackColor, SMW_SCBACK );
            glk_stylehint_set( gg_mainwin, style_Preformatted, stylehint_TextColor, SMW_SCPREF );
            glk_stylehint_set( gg_mainwin, style_Preformatted, stylehint_BackColor, SMW_SCBACK );
            glk_stylehint_set( gg_mainwin, style_User1, stylehint_TextColor, SMW_SCUDS1 );
            glk_stylehint_set( gg_mainwin, style_User1, stylehint_BackColor, SMW_SCBACK );
            glk_stylehint_set( gg_mainwin, style_User2, stylehint_TextColor, SMW_SCUDS2 );
            glk_stylehint_set( gg_mainwin, style_User2, stylehint_BackColor, SMW_SCBACK );
    }
    rfalse;
];


! Glk object identification entry point ----------------------------------------
[ IdentifyGlkObject phase type ref rock id;

    switch (phase) {
    0:    ! start
        SMW.resetAllGlkReferences();
        return;
    1:    ! pass ref
        switch ( type ) {
            0:    ! window ref
                switch ( rock ) {
                    SMW_PICWIN_ROCK:
                        if ( ~~SMW.usingInlinedGraphics() ) {
                                SMW.setGraphicsWindow( ref );
                        } else {
				SMW.setGraphicsWindow( gg_mainwin );
			}
                    GG_STATUSWIN_ROCK:
                        gg_statuswin = ref;
                    default:
                        SMW.updateSubWindowRef( rock, ref );
                }
        }

        return;
    2:  ! Update music
         id = glk_schannel_iterate( 0, gg_arguments );
         while ( id ) {
            switch ( gg_arguments-->0 ) {
               SMW_MUSICCHAN_ROCK          : SMW.music = id;
               SMW_MUSICCHANSOUND1_ROCK    : SMW.chan1 = id;
               SMW_MUSICCHANSOUND2_ROCK    : SMW.chan2 = id;
           }
           id = glk_schannel_iterate( id, gg_arguments );
         }

        ! Update graphics
        if ( SMW.usingInlinedGraphics() ) {
             SMW.setGraphicsWindow( gg_mainwin );
        }

        ! Chk
        SMW.chkAllGlkReferences();

        ! Redraw
        SMW.redrawGraphicsWindows();

        return;
    }

    return;
];

#Endif;

! ----------------------------------------------------------------- Init library
[ initializeSMW h pos;
    SMW.init( h, pos );
];
