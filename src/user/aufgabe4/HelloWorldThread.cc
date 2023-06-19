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


/*****************************************************************************
 * Methode:         HelloWorldThread::run                                    *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einstiegsfunktion in unseren Thread.                     *
 *****************************************************************************/
void HelloWorldThread::run () {
    
    kout << "Hallo Welt von einem Thread!" << endl;
    if (this->tid == 2){
        sound_demo();
    } 

    else{
    for(int i = 0; ; i++) {
        int x = 0;
        int y = 0;
        cpu.disable_int();
        kout.setpos(0,this->tid*5);
        kout << "Koroutine [" << this->tid << "]: " << i << endl;     
        cpu.enable_int();
    }
    }
    // selbst terminieren
    scheduler.exit ();
}


