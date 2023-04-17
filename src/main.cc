/*****************************************************************************
 *                                                                           *
 *                                M A I N                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Startroutine, wird direkt vom Bootlader angesprungen,    *
 *                  nachdem dieser in den Protected Mode geschaltet hat und  *
 *                  die GDT und IDT initalisiert hat.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 15.8.2016                       *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "user/aufgabe1/TextDemo.h"
#include "user/aufgabe1/KeyboardDemo.h"
#include "user/aufgabe2/SoundDemo.h"
#include "user/aufgabe2/HeapDemo.h"


void aufgabe01() { 
   // Bildschirmausgabe testen
   text_demo();
    
   // Tastatur testen
   keyboard_demo();
}

void aufgabe02() {
    heap_demo();
}

int main() {
    kout.clear();
    kout.setpos(0, 0);
    kout.print("Mersch OS", 9, 0x0F);

    aufgabe02();

    while (1);
    return 0;
 }
