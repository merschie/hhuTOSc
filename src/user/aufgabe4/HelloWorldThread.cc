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
#include "user/aufgabe2/SoundDemo.h"

#include "lib/Semaphore.h"


static Semaphore sem (1);

/*****************************************************************************
 * Methode:         HelloWorldThread::run                                    *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einstiegsfunktion in unseren Thread.                     *
 *****************************************************************************/
void HelloWorldThread::run () {
    
    if (this->tid == 1){
        sound_demo();
    }
    else{
    for(int i = 0; ; i++) {
        sem.p();
        kout.setpos(0,this->tid*5);
        kout << "Koroutine [" << this->tid << "]: " << i << endl;
        sem.v();     
    }
    }
    // selbst terminieren
    kout << "Thread [" << this->tid << "] beendet sich selbst." << endl;
    scheduler.exit ();
}


