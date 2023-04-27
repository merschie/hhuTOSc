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
     free_start = (free_block*) heap_start;
     free_start->size = 0;
     
     //create first block
     free_block *first_block = (free_block*) heap_start + sizeof(heap_start);
     first_block->size = heap_end - heap_start - sizeof(heap_start);

     free_start->next = first_block;
}


/*****************************************************************************
 * Methode:         LinkedListAllocator::dump_free_memory                    *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Ausgabe der Freispeicherliste. Zu Debuggingzwecken.      *
 *****************************************************************************/
void LinkedListAllocator::dump_free_memory() {
     free_block *current = free_start;
     while (current != NULL) {   
          kout << "     block start: " << hex << current << " block end: " << hex << current->next << " block size: " << dec <<  current->size << endl;
          kout << "     sizeof: " << hex << (int)sizeof(current) << endl;
          current = current->next;
     }

}


/*****************************************************************************
 * Methode:         LinkedListAllocator::alloc                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen neuen Speicherblock allozieren.                    * 
 *****************************************************************************/
void * LinkedListAllocator::alloc(uint64_t  req_size) {
     
     free_block *current = free_start;
     while (true) {
          if (current -> next -> size >= req_size) {

               //create new block if there is enough space
               if (current->next->size > req_size) {
                    free_block *new_block = (free_block*) ((uint64_t) current->next + req_size);
                    new_block->size = current->next->size - req_size;
                    new_block->next = current->next->next;
                    current -> next = new_block;
                    
               }
               //return adress
               return (void*) current -> next;
         }
         current = current->next;
     }
}


/*****************************************************************************
 * Methode:         LinkedListAllocator::free                                *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen Speicherblock freigeben.                           *
 *****************************************************************************/
void LinkedListAllocator::free(void *ptr) {
     //create new block at ptr
     free_block *new_block = (free_block*) ptr;

     //find block before ptr
     free_block *current = free_start;
     while (current->next > ptr) {
          current = current->next;
     }
     current->next = new_block;
     new_block->next = current->next->next;
     new_block->size = current->next->size + sizeof(current->next);

}

