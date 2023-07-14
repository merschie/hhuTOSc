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
//void waitForReturn() {

    /* hier muss Code eingefuegt werden */

//}


void heap_demo() {
    //init the heap
    allocator.dump_free_memory();
    kout << "Allocate 128 bits\n" << endl;
    char* testString = (char*) allocator.alloc(1024);
    allocator.dump_free_memory();
    kout << "Allocate 32 bits\n" << endl;
    int* i = (int*) allocator.alloc(32);
    allocator.dump_free_memory();
    kout << "Free 32 bits\n" << endl;
    //free the 32 bits
    allocator.free(i);

    allocator.dump_free_memory();
    kout << "Free 128 bits\n" << endl;
    allocator.free(testString);
    allocator.dump_free_memory();


   /* hier muss Code eingefuegt werden */

}
