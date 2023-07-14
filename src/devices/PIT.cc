/*****************************************************************************
 *                                                                           *
 *                                   P I T                                   *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Programmable Interval Timer.                             *
 *                                                                           *
 * Autor:           Michael Schoettner, 3.7.2022                             *
 *****************************************************************************/

#include "devices/PIT.h"
#include "kernel/IOport.h"
#include "kernel/Globals.h"


/*****************************************************************************
 * Methode:         PIT::interval                                            *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Zeitinervall programmieren.                              *
 *                                                                           *
 * Parameter:                                                                *
 *      us:         Zeitintervall in Mikrosekunden, nachdem periodisch ein   * 
 *                  Interrupt erzeugt werden soll.                           *
 *****************************************************************************/
void PIT::interval (int us) {
    uint16_t counter = us*1000/time_base;




    IOport control (0x43);
    control.outb (0b00110110);
    IOport data (0x40);
    data.outb (counter & 0xff);
    data.outb (counter >> 8);

}


/*****************************************************************************
 * Methode:         PIT::plugin                                              *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Unterbrechungen fuer den Zeitgeber erlauben. Ab sofort   *
 *                  wird bei Ablauf des definierten Zeitintervalls die       *
 *                  Methode 'trigger' aufgerufen.                            *
 *****************************************************************************/
void PIT::plugin () {
    pic.allow (pic.timer);
    kout << "Pit systemzeit initialisiert" << endl;
    intdis.assign (intdis.timer, *this);

}


/*****************************************************************************
 * Methode:         PIT::trigger                                             *
 *---------------------------------------------------------------------------*
 * Beschreibung:    ISR fuer den Zeitgeber. Wird aufgerufen, wenn der        * 
 *                  Zeitgeber eine Unterbrechung ausloest. Anzeige der Uhr   *
 *                  aktualisieren und Thread wechseln durch Setzen der       *
 *                  Variable 'forceSwitch', wird in 'int_disp' behandelt.    *
 *****************************************************************************/
void PIT::trigger () {
    
    

    systime += 1;

    scheduler.preempt();
    
    gDemo->update();


/*     if (systime%100 == 0 ){
        //create char arraay
        char spinning[4]= {'|','/','-','\\'};
        kout.show(75,1,spinning[(systime/100)%4],0x05);
    } */
    
}


