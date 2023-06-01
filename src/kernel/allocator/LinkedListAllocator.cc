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
     first_block->next = NULL;

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
          kout << "     block start: " << hex << current << " next block: " << hex << current->next << " block size: " << dec <<  current->size << endl;
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
     while (current -> next != NULL) {
          //if size is big enough to make new block
          if (current -> next -> size >= req_size + sizeof(free_block)) {
               free_block *to_alloc = current -> next;
               free_block *new_block = (free_block*) ((char*) current -> next + req_size + sizeof(free_block));        
               new_block -> size = current -> next -> size - (req_size - sizeof(free_block));
               //to_alloc -> size = req_size;

               new_block -> next = current -> next -> next;
               //unlink current->next and show pointer to new_block
               current -> next = new_block;
               //kout << "allocating block at " << hex << to_alloc<< " with size " << dec << req_size << endl;
               //kout << "size of new block: " << dec << new_block -> size << endl;
               //kout << "adress of new block: " << hex << new_block << endl;
               //kout << "Adress of next block: " << hex << new_block -> next << endl;
               //return pointer of to_alloc + sizeof(free_block)
               return (void*) to_alloc + sizeof(free_block);
               
          }
          //if size is not big enough to make new block
          else if (current -> next -> size >= req_size) {
               current -> next = current -> next -> next;
               //kout << "allocating block kfeusjfilsjfiosfjat " << hex << current -> next << endl;
               return (void*) current -> next + sizeof(free_block);      
          }
         current = current->next;
     }

     while (true)
     
     kout << "no memory left" << endl;
          
     return NULL;
}


/*****************************************************************************
 * Methode:         LinkedListAllocator::free                                *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen Speicherblock freigeben.                           *
 *****************************************************************************/
void LinkedListAllocator::free(void *ptr) {
     //recover block at ptr - sizeof(free_block)
     //kout << "freeing block at " << hex << ptr << endl;
     free_block *block = (free_block*) ((char*) ptr - sizeof(free_block));
     
     //find last block
     free_block *current = free_start;
     while (current -> next != NULL) {
          current = current -> next;
     }
     //link last block to block
     current -> next = block;
     block -> next = NULL;

}