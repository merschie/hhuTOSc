/*****************************************************************************
 *                                                                           *
 *                        K E Y B O A R D D E M O                            *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Testausgaben für den CGA-Treiber.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 26.10.2018                      *
 *****************************************************************************/

#include "kernel/Globals.h"


void keyboard_demo() {

    Keyboard kbd;
    kbd.set_led(4,true);
    kbd.set_repeat_rate(3,3);
    int pos = 0;
    while (true)
    {   
        if(kbd.key_hit().valid())
        {
            kout.setpos(pos,0);
            kout.show(pos,0,kbd.key_hit().ascii(),0x0F);
            pos++;
        }
        kout.show(2,2,kbd.key_hit().ascii(),0x0F);
    }
}
