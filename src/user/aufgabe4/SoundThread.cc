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
#include "user/aufgabe4/SoundThread.h"
#include "user/aufgabe2/SoundDemo.h"

#include "lib/Semaphore.h"


static Semaphore sem (1);

/*****************************************************************************
 * Methode:         HelloWorldThread::run                                    *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einstiegsfunktion in unseren Thread.                     *
 *****************************************************************************/
void SoundThread::run () {
    
    sound_demo();
    
}


