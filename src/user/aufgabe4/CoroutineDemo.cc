/*****************************************************************************
 *                                                                           *
 *                      C O R O U T I N E D E M O                            *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einstieg in eine Anwendung.                              *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 15.5.2023                       *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "user/aufgabe4/CoroutineDemo.h"
#include "user/aufgabe4/CoroutineLoop.h"


/*****************************************************************************
 * Methode:         CoroutineDemo::main                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    main-Methode der Anwendung.                              *
 *****************************************************************************/
void CoroutineDemo::main () {

    /*
     * Die 3 Koroutinen einrichten, verketten und die 1. starten
     */

    CoroutineLoop app1(1);
    CoroutineLoop app2(2);
    CoroutineLoop app3(3);

    app1.setNext(&app2);
    app2.setNext(&app3);
    app3.setNext(&app1);

    app1.start();

}
