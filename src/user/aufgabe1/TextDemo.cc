/*****************************************************************************
 *                                                                           *
 *                           T E X T D E M O                                 *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Testausgaben für den CGA-Treiber.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 26.10.2018                       *
 *****************************************************************************/

#include "kernel/Globals.h"


void text_demo() {
   kout.clear();
   kout.setpos(5, 10);
   kout.print("Hello World!\nzeilenumbruch", 27, 0x09);
   kout.show(8, 11, 'H', 0x0A);
   kout.setpos(1, 0);
   kout.print("Hello World!", 12, 0x08);
   kout.setpos(0, 1);
   kout.print("Hello World!", 12, 0x0C);
   kout.scrollup();
   
   }
