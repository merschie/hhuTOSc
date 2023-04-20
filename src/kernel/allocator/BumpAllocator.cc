/*****************************************************************************
 *                                                                           *
 *                        B U M P A L L O C A T O R                          *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Eine sehr einfache Heap-Verwaltung, welche freigegebenen *
 *                  Speicher nicht mehr nutzen kann.                         *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 3.3.2022                        *
 *****************************************************************************/

#include <stddef.h>
#include "kernel/Globals.h"
#include "kernel/allocator/BumpAllocator.h"


/*****************************************************************************
 * Methode:         BumpAllocator::init                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    BumpAllokartor intitialisieren.                          *
 *****************************************************************************/
void BumpAllocator::init() {
     //set next to the start of the heap
     next = (unsigned char*) heap_start;



     /* Hier muess Code eingefuegt werden */


}


/*****************************************************************************
 * Methode:         BumpAllocator::dump_free_memory                          *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Ausgabe der Freispeicherinfos. Zu Debuggingzwecken.      *
 *****************************************************************************/
void BumpAllocator::dump_free_memory() {
    

     kout << "   heap_start= " << hex << (uint64_t)heap_start << endl;
     kout << "   heap_end= " << hex << (uint64_t)heap_end << endl;
     kout << "   heap_size= " << dec << (uint64_t)heap_size << endl;
     kout << "   next= " << hex << (uint64_t)next << endl;
     /* Hier muess Code eingefuegt werden */

}


/*****************************************************************************
 * Methode:         BumpAllocator::alloc                                     *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen neuen Speicherblock allozieren.                    * 
 *****************************************************************************/
void * BumpAllocator::alloc(uint64_t req_size) {
     next = (unsigned char*) ((uint64_t )next + req_size);
     allocations++;
     return (void*) (next - req_size);

     /* Hier muess Code eingefuegt werden */

}


/*****************************************************************************
 * Methode:         BumpAllocator::free                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Nicht implementiert.                                     *
 *****************************************************************************/
void BumpAllocator::free(void *ptr) {
    kout << "   mm_free: ptr= " << hex << (uint64_t)ptr << ", not supported" << endl;
}