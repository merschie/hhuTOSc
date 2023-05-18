/*****************************************************************************
 *                                                                           *
 *                  C O R O U T I N E                                        *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung eines Koroutinen-Konzepts.               *
 *                                                                           *
 *                  Die Koroutinen sind miteinander verkettet, weswegen die  *
 *                  Klasse Coroutine ein Subtyp von 'Chain' ist.             *
 *                                                                           *
 *                  Im Konstruktor wird der initialie Kontext der Koroutine  *
 *                  eingerichtet. Mit 'start' wird ein Koroutine aktiviert.  *
 *                  Das Umschalten auf die naechste Koroutine erfolgt durch  *
 *                  Aufruf von 'switchToNext'.                               *
 *                                                                           *
 *                  Bei einem Koroutinenwechsel werden die Register auf dem  *
 *                  Stack gesichert. Die Instanzvariable 'context' zeigt auf *
 *                  den letzten hierfuer genutzten Stackeintrag.             *
 *                                                                           *
 * Autor:           Michael, Schoettner, HHU, 13.01.2023                     *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "kernel/threads/Thread.h"

// Funktionen, die auf der Assembler-Ebene implementiert werden, muessen als
// extern "C" deklariert werden, da sie nicht dem Name-Mangeling von C++
// entsprechen.
extern "C"
{
void Coroutine_start  (void* context);
void Coroutine_switch (void* context_now, void *context_then);
}


/*****************************************************************************
 * Methode:         Coroutine::Coroutine                                     *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Initialer Kontext einer Koroutine einrichten.            *
 *                                                                           *
 * Parameter:                                                                *
 *      stack       Stack für die neue Koroutine                             *
 *****************************************************************************/
Thread::Thread () {
}


/*****************************************************************************
 * Methode:         Coroutine::switchToNext                          	     *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Auf die nächste Koroutine umschalten.                    *
 *****************************************************************************/
void Thread::switchTo (Thread &next) {
    /* hier muss Code eingefügt werden */
}


/*****************************************************************************
 * Methode:         Coroutine::start                                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Aktivierung der Koroutine.                               *
*****************************************************************************/
void Thread::start () {
    /* hier muss Code eingefügt werden */
}
