/*****************************************************************************
 *                                                                           *
 *                  L I N K E D L I S T A L L O C A T O R                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einfache Speicherverwaltung, welche den freien Speicher  *
 *                  mithilfe einer einfach verketteten Liste verwaltet.      *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 13.6.2020                        *
 *****************************************************************************/

#include <stddef.h>
#include "kernel/Globals.h"
#include "kernel/allocator/LinkedListAllocator.h"

#define HEAP_MIN_FREE_BLOCK_SIZE 64         // min. Groesse eines freien Blocks


/*****************************************************************************
 * Methode:         LinkedListAllocator::init                                *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Liste der Freispeicherbloecke intitialisieren.           *
 *                  Anker zeigt auf ein Dummy-Element. Danach folgt          *
 *                  ein Block der den gesamten freien Speicher umfasst.      *
 *                                                                           *
 *                  Wird automatisch aufgerufen, sobald eine Funktion der    *
 *                  Speicherverwaltung erstmalig gerufen wird.               *
 *****************************************************************************/
void LinkedListAllocator::init() {
     // Anker fuer die Freispeicherliste
     free_block *anker = (free_block*) heap_start;
     anker->size = 16;
     anker->next = NULL;
}


/*****************************************************************************
 * Methode:         LinkedListAllocator::dump_free_memory                    *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Ausgabe der Freispeicherliste. Zu Debuggingzwecken.      *
 *****************************************************************************/
void LinkedListAllocator::dump_free_memory() {
     kout << "Heap Start: " << hex << heap_start << " heap_end: " << hex << heap_end << endl;
     kout << "Block Start: " << hex << (uint64_t) free_start << " Block End: " << hex << (uint64_t) free_end << "Block Größe: " << size << endl;
     

}


/*****************************************************************************
 * Methode:         LinkedListAllocator::alloc                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen neuen Speicherblock allozieren.                    * 
 *****************************************************************************/
void * LinkedListAllocator::alloc(uint64_t  req_size) {

     
     

}


/*****************************************************************************
 * Methode:         LinkedListAllocator::free                                *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen Speicherblock freigeben.                           *
 *****************************************************************************/
void LinkedListAllocator::free(void *ptr) {

     /* Hier muess Code eingefuegt werden */

}

