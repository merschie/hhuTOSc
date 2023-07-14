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
     cpu.disable_int();
     next = (unsigned char*) heap_start;
     allocations = 0;
     cpu.enable_int();


     /* Hier muess Code eingefuegt werden */


}


/*****************************************************************************
 * Methode:         BumpAllocator::dump_free_memory                          *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Ausgabe der Freispeicherinfos. Zu Debuggingzwecken.      *
 *****************************************************************************/
void BumpAllocator::dump_free_memory() {
    
     kout << "BumpAllocator: " << endl;
     kout << "   heap_start  = " << hex << (uint64_t)heap_start << endl;
     kout << "   heap_end    = " << hex << (uint64_t)heap_end << endl;
     kout << "   heap_size   = " << hex << (uint64_t)heap_size << endl;
     kout << "   next        = " << hex << (uint64_t)next << endl;
     kout << "   allocations = " << dec << allocations << endl;
     /* Hier muess Code eingefuegt werden */

}


/*****************************************************************************
 * Methode:         BumpAllocator::alloc                                     *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen neuen Speicherblock allozieren.                    * 
 *****************************************************************************/
void * BumpAllocator::alloc(uint64_t req_size) {
     cpu.disable_int();
     next = next + req_size;
     heap_size = heap_size - req_size;
     allocations++;
     cpu.enable_int();
     return (void*) (next - req_size);
}


/*****************************************************************************
 * Methode:         BumpAllocator::free                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Nicht implementiert.                                     *
 *****************************************************************************/
void BumpAllocator::free(void *ptr) {
    kout << "   mm_free: ptr= " << hex << (uint64_t)ptr << ", not supported" << endl;
}