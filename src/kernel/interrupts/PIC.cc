/*****************************************************************************
 *                                                                           *
 *                                  P I C                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Mit Hilfe des PICs koennen Hardware-Interrupts (IRQs)    *
 *                  einzeln zugelassen oder unterdrueckt werden. Auf diese   *
 *                  Weise wird also bestimmt, ob die Unterbrechung eines     *
 *                  Geraetes ueberhaupt an den Prozessor weitergegeben wird. *
 *                  Selbst dann erfolgt eine Aktivierung der Unterbrechungs- *
 *                  routine nur, wenn der Prozessor bereit ist, auf Unter-   *
 *                  brechungen zu reagieren. Dies kann mit Hilfe der Klasse  *
 *                  CPU festgelegt werden.                                   *
 *                                                                           *
 * Autor:           Olaf Spinczyk, TU Dortmund                               *
 *****************************************************************************/

#include "PIC.h"
#include "kernel/IOport.h"


static IOport IMR1 (0x21);    // interrupt mask register von PIC 1
static IOport IMR2 (0xa1);    // interrupt mask register von PIC 2


/*****************************************************************************
 * Methode:         PIC::allow                                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Sorgt dafuer, dass der uebergebene IRQ ab sofort durch   *
 *                  den PIC an den Prozessor weitergereicht wird. Um eine    *
 *                  Unterbrechungsbehandlung zu ermoeglichen, muss           *
 *                  zusaetzlich CPU::enable_int() aufgerufen werden.         *
 *                                                                           *
 * Parameter:                                                                *
 *      irq:        IRQ der erlaubt werden soll                              *
 *****************************************************************************/
void PIC::allow (int irq) {
    if (irq >= 16) return;

    if (irq < 8) {
        IMR1.outb(IMR1.inb() & ~(1<<irq));
    } else {
        IMR2.outb(IMR2.inb() & ~(1<<(irq-8)));
    }
}


/*****************************************************************************
 * Methode:         PIC::forbid                                              *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Unterdrueckt mit Hilfe des PICs einen bestimmten IRQ.    *
 *                                                                           *
 * Parameter:                                                                *
 *      interrupt:  IRQ der maskiert werden soll                             *
 *****************************************************************************/
void PIC::forbid (int irq) {
    if (irq >= 16) return;

    if (irq < 8) {
        IMR1.outb(IMR1.inb() | (1<<irq));
    } else {
        IMR2.outb(IMR2.inb() | (1<<(irq-8)));
    }
}


/*****************************************************************************
 * Methode:         PIC::status                                              *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Liefert den aktuellen Zustand des Maskierbits eines      *
 *                  bestimmten IRQs.                                         *
 *                                                                           *
 * Parameter:                                                                *
 *      irq:  IRQ dessen Status erfragt werden soll                          *
 *****************************************************************************/
bool PIC::status (int irq) {
    if (irq >= 16) return false;

    if (irq < 8) {
        return (IMR1.inb() >> irq) & 1;
    } else {
        return (IMR2.inb() >> (irq-8)) & 1;
    }
}
