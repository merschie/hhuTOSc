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
    kout.print("Allocate 64bit value\n",21,0x0F);
    allocator.alloc(128);
    allocator.dump_free_memory();
    kout.print("Allocate 32bit value\n",21,0x0F);
    allocator.alloc(256);
    allocator.dump_free_memory();


   /* hier muss Code eingefuegt werden */

}
