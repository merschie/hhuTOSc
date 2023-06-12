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
    kout.print("MerschOs\n",10,0x05);
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

    kout << "Koroutinen initialisiert" << endl;

    pit.plugin();
    sound_demo();

    //kout.clear();
    //kout.setpos(0,0);
/*     Queue readyqueue;
    allocator.dump_free_memory();
    int a = 1;
    int b = 2;
    int c = 3;
    readyqueue.addElement(&a);
    readyqueue.addElement(&b);
    readyqueue.addElement(&c);
    allocator.dump_free_memory();

    readyqueue.dump();
    
    int *d = (int*)readyqueue.getFirst();
    kout << "d: " << dec << *d << endl;
    int *e = (int*)readyqueue.getFirst();
    kout << "d: " << dec << *e << endl;
    int *f = (int*)readyqueue.getFirst();
    kout << "d: " << dec << *f << endl; */

    //CoroutineDemo().main();
    //aufgabe03();

    //HelloWorldThread *hello = new HelloWorldThread();
    //HelloWorldThread *hello2 = new HelloWorldThread();
    //HelloWorldThread *hello3 = new HelloWorldThread();

    //scheduler.ready(hello);
    //scheduler.ready(hello2);
    //scheduler.ready(hello3);

    // Scheduler für Threadverwaltung starten
    //scheduler.schedule();
        
    while (1) ; // wir kehren nicht zum Bootlader zurueck
    return 0;
}
