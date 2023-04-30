/*****************************************************************************
 *                                                                           *
 *                            H E A P D E M O                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Demonstration der dynamischen Speicherverwaltung.        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 27.12.2016                      *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "kernel/Allocator.h"
#include "user/aufgabe2/HeapDemo.h"
#include "devices/PCSPK.h"
// #include "user/MyObj.h"


// Hilfsfunktion: Auf Return-Taste warten
void waitForReturn() {

    /* hier muss Code eingefuegt werden */

}


void heap_demo() {
    //init the heap
    allocator.init();
    allocator.dump_free_memory();
    kout.print("Allocate 128 bits\n",19,0x0F);
    char* testString = (char*) allocator.alloc(1024);
    allocator.dump_free_memory();
    kout.print("Allocate 32 bits\n",18,0x0F);
    int* i = (int*) allocator.alloc(32);
    allocator.dump_free_memory();
    kout.print("Free 32 bits\n",14,0x0F);
    //free the 32 bits
    allocator.free(i);

    allocator.dump_free_memory();
    kout.print("Free 128 bits\n",15,0x0F);
    allocator.free(testString);
    allocator.dump_free_memory();


   /* hier muss Code eingefuegt werden */

}
