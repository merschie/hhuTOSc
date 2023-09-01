/*****************************************************************************
 *                                                                           *
 *                   H E L L O W O R L D T H R E A D                         *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Ein einfacher Thread.                                    *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 16.12.2016                      *
 *****************************************************************************/
#ifndef __sound_thread_include__
#define __sound_world_thread_include__


#include "kernel/threads/Thread.h"


class SoundThread : public Thread {
    
private:
    SoundThread (const SoundThread &copy); // Verhindere Kopieren

public:
    SoundThread () : Thread () { }

    // Thread-Startmethode
    void run ();

 };

#endif
