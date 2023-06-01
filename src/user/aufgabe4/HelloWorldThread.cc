/*****************************************************************************
 *                                                                           *
 *                   H E L L O W O R L D T H R E A D                         *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Ein einfacher Thread.                                    *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 21.8.2016                       *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "user/aufgabe4/HelloWorldThread.h"


/*****************************************************************************
 * Methode:         HelloWorldThread::run                                    *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einstiegsfunktion in unseren Thread.                     *
 *****************************************************************************/
void HelloWorldThread::run () {
    
    kout << "Hallo Welt von einem Thread!" << endl;
    for(int i = 0; ; i++) {
        kout.setpos(0,this->tid*5);
        kout << "Koroutine [" << this->tid << "]: " << i << endl;
        if(3 == 3) {
            kout.flush();
        }
        scheduler.yield ();
    }
    // selbst terminieren
    scheduler.exit ();
}


