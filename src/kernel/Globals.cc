/*****************************************************************************
 *                                                                           *
 *                               G L O B A L S                               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Globale Variablen des Systems.                           *
 *                                                                           *
 * Autor:           Michael Schoettner, 8.7.2022                             *
 *****************************************************************************/

#include "kernel/Globals.h"

uint64_t              systime=0;  // wird all 10ms hochgezaehlt
PIT                   pit(10000); // Zeitgeber (10ms)
CPU                   cpu;        // CPU-spezifische Funktionen
PCSPK                 pcspk;      // PC-Lautsprecher
CGA_Stream            kout;       // Ausgabe-Strom fuer Kernel
Keyboard              kb;         // Tastatur
IntDispatcher         intdis;     // Unterbrechungsverteilung
PIC                   pic;        // Interrupt-Controller
unsigned int          total_mem;  // RAM total
//BumpAllocator         allocator;
LinkedListAllocator   allocator;
Scheduler             scheduler;  // Scheduler
unsigned int          ThreadIdCounter=1;    //aktuelle ThreadID
unsigned int          aufgabe=0;      //aktuelle ThreadID

