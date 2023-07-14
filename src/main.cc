/*****************************************************************************
 *                                                                           *
 *                                M A I N                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einstiegsfunktion in unser Betriebsystem ist 'main'.     * 
 *                  Diese Funktion wird vom Bootlader angesprungen.          *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 11.01.2023                      *
 *****************************************************************************/

#include "kernel/Globals.h"
//#include "user/aufgabe1/KeyboardDemo.h"
#include "user/aufgabe2/SoundDemo.h"
//#include "user/aufgabe4/CoroutineDemo.h"
#include "user/aufgabe4/HelloWorldThread.h"
#include "user/MainMenu/menu.h"



extern "C" void _init_interrupts();     // in 'interrupts.asm' 

void aufgabe03() {
   // Keyboard & Interrupts testen
   //keyboard_demo();

    while(1){
        kout.setpos(0,6);
        for (int i = 0; i < 15; i++) {
            kout << i << endl;
        }
    }
}


/*****************************************************************************
 * Funktion:        main                                                     *
 *---------------------------------------------------------------------------*
 * Beschreibung:    C-Einstiegsfunktion fuer hhuTOS.                         *
 *****************************************************************************/
int main() {
    kout.clear();
    kout.setpos(0,0);
    kout.print("MerschOs\n",10);

    // Heapverwaltung initialisieren
    allocator.init();
    kout << "Heap initialisiert" << endl;

    // IDT & PIC initialisieren
    _init_interrupts();     // in 'interrupts.asm' 
    kout << "Interrupts initialisiert" << endl;

    // Tastatur-Unterbrechungsroutine 'einstoepseln'
    kb.plugin();
    kout << "Tastatur initialisiert" << endl;

    // Interrupt-Verarbeitung durch CPU erlauben 
    cpu.enable_int();
    kout << "Threads laufen jetzt" << endl;

    //Systemzeit initialisieren
    pit.plugin();
    kout << "Systemzeit initialisiert" << endl;


    gDemo = new GraphicDemo();

    scheduler.ready(gDemo);
    scheduler.schedule();

    //kout << endl << "Druecke 0 fuer das Auswahlmenue" << endl;

        
    while (1) ; // wir kehren nicht zum Bootlader zurueck
    return 0;
}
