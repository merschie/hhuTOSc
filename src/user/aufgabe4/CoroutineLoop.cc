/*****************************************************************************
 *                                                                           *
 *                       C O R O U T I N E L O O P                           *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Loop ist eine Koroutine, die nichts weiter tut als einen *
 *                  Zaehler hochzuzaehlen und diesen auf dem Bildschirm      *
 *                  anzuzeigen und dann auf die naechste Koroutine umzu-     *
 *                  schalten.				 	                  	 	           			 *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 15.8.2016                       *
 *****************************************************************************/

#include "user/aufgabe4/CoroutineLoop.h"
#include "kernel/Globals.h"


/*****************************************************************************
 * Methode:         CoroutineLoop::run                                       *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einstiegsfunktion der Koroutine.                         *
 *****************************************************************************/
void CoroutineLoop::run () {
    int x, y;
    kout.getpos(x, y);
    y++;

    for(int i = 0; ; i++) {
        if(id == 1) {
            kout.setpos(0, y);
        }
        kout << "Koroutine [" << id << "]: " << i << "   ";
        if(id == 3) {
            kout.flush();
        }
        switch2next();
    }
   
}
