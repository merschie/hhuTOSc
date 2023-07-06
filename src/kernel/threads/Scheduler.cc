/*****************************************************************************
 *                                                                           *
 *                          S C H E D U L E R                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung eines einfachen Zeitscheiben-Schedulers  *
 *                  welcher kooperative Threads in einer 'readQueue' ver-    *
 *                  waltet.                                                  *
 *                                                                           *
 *                  Der Scheduler wird mit 'schedule' gestartet. Neue Threads*
 *                  können mit 'ready' hinzugefügt werden. Ein Thread muss   *
 *                  die CPU freiwillig mit 'yield' abgeben, damit andere auch*
 *                  rechnen koennen. Ein Thread kann sich selbst mit 'exit'  *
 *                  terminieren. Ein Thread kann einen anderen Thread mit    *
 *                  'kill' beenden.                                          *
 *                                                                           *
 * Autor:           Michael, Schoettner, HHU, 21.12.2018                     *
 *****************************************************************************/

#include "kernel/threads/Scheduler.h"
#include "kernel/threads/IdleThread.h"
#include "kernel/Globals.h"

IdleThread *idle;
bool init = false;

/*****************************************************************************
 * Methode:         Scheduler::schedule                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Scheduler starten. Wird nur einmalig aus main.cc gerufen.*
 *****************************************************************************/
void Scheduler::schedule () {

    if (init) {
        return;
    }
    init = true;
    idle = new IdleThread();

    Thread *current = (Thread *)readyQueue.getFirst();
    if (current == nullptr) {
        start(*idle);
    }
    else{
        start(*current);
    }

}


/*****************************************************************************
 * Methode:         Scheduler::ready                                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Thread in readyQueue eintragen.                          *
 *                                                                           *
 * Parameter:                                                                *
 *      that        Einzutragender Thread                                    *
 *****************************************************************************/
void Scheduler::ready (Thread * that) {
    readyQueue.addElement(that);
    //readyQueue.dump();
}


/*****************************************************************************
 * Methode:         Scheduler::exit                                          *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Thread ist fertig und terminiert sich selbst. Hier muss  *
 *                  nur auf den naechsten Thread mithilfe des Dispatchers    *
 *                  umgeschaltet werden. Der aktuell laufende Thread ist     *
 *                  nicht in der readyQueue.                                 *
 *****************************************************************************/
void Scheduler::exit () {
    cpu.disable_int();
    Thread *current = (Thread *)readyQueue.getFirst();
    if (current == nullptr) {

        start(*idle);
    }
    else{
        dispatch(*current);
    }
    cpu.enable_int();

}


/*****************************************************************************
 * Methode:         Scheduler::kill                                          *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Thread mit 'Gewalt' terminieren. Er wird aus der         *
 *                  readyQueue ausgetragen und wird dann nicht mehr aufge-   *
 *                  rufen. Der Aufrufer dieser Methode muss ein anderer      *
 *                  Thread sein.                                             *
 *                                                                           *
 * Parameter:                                                                *
 *      that        Zu terminierender Thread                                 *
 *****************************************************************************/
void Scheduler::kill (Thread * that) {
    cpu.disable_int();
    if (that == nullptr) {
        return;
    }
    if (that == get_active()) {
        exit();
    }
    else {
        readyQueue.deleteElement(that);
    }
    cpu.enable_int();
}


/*****************************************************************************
 * Methode:         Scheduler::yield                                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    CPU freiwillig abgeben und Auswahl des naechsten Threads.*
 *                  Naechsten Thread aus der readyQueue holen, den aktuellen *
 *                  in die readyQueue wieder eintragen. Das Umschalten soll  *
 *                  mithilfe des Dispatchers erfolgen.                       *
 *                                                                           *
 *                  Achtung: Falls nur der Idle-Thread läuft, so ist die     *
 *                           readyQueue leer.                                *
 *****************************************************************************/
void Scheduler::yield () {
    cpu.disable_int();

    Thread *next = (Thread *)readyQueue.getFirst();
    if (next != nullptr) {
        readyQueue.addElement(get_active());
        dispatch(*next);
    }
    else {
        start(*idle);
    }
    cpu.enable_int();
}



/*****************************************************************************
 * Methode:         Scheduler::preempt                                       *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Diese Funktion wird aus der ISR des PITs aufgerufen und  *
 *                  schaltet auf den naechsten Thread um, sofern einer vor-  *
 *                  handen ist.                                              *
 *****************************************************************************/
void Scheduler::preempt () {
    
    if (!init) {
        return;
    }
    cpu.disable_int();
    Thread *next = (Thread *)readyQueue.getFirst();
    if (next != nullptr) {
        readyQueue.addElement(get_active());
        dispatch(*next);
    }
    else {
        start(*idle);
    }
    cpu.enable_int();
}


/*****************************************************************************
 * Methode:         Scheduler::block                                         *
 * Beschreibung:    Thread blockieren und naechsten Thread waehlen.          *
 *                 Der aktuelle Thread muss sich selbst in eine Blockier-   *
 *                warteschlange eintragen und dann auf den naechsten Thread *
 *              wechseln.                                                  *

 *****************************************************************************/

void Scheduler::block () {
    cpu.disable_int();
    if(!init){
        return;
    }

    Thread *next = (Thread *)readyQueue.getFirst();
    if (next != nullptr) {
        dispatch(*next);
    }
    else {
        start(*idle);
    }
    cpu.enable_int();
}

void Scheduler::deblock (Thread &that) {
    cpu.disable_int();
    if(!init){
        return;
    }
    ready(&that);
    cpu.enable_int();
}