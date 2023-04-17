/*****************************************************************************
 *                                                                           *
 *                               G L O B A L S                               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Globale Variablen des Systems.                           *
 *                                                                           *
 * Autor:           Michael Schoettner, 30.7.16                              *
 *****************************************************************************/

#include "kernel/Globals.h"

CPU             cpu;        
PCSPK           pcspk;      // PC-Lautsprecher
CGA_Stream      kout;       // Ausgabe-Strom fuer Kernel
uint64_t        total_mem;  // RAM total
BumpAllocator         allocator;       
//LinkedListAllocator   allocator;       

