/*****************************************************************************
 *                                                                           *
 *                                K E Y B O A R D                            *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Treiber für den Tastaturcontroller des PCs.              *
 *                                                                           *
 * Autor:           Olaf Spinczyk, TU Dortmund                               *
 *                  Modifikationen, Michael Schoettner, 4.5.2023             *
 *****************************************************************************/
#ifndef __Keyboard_include__
#define __Keyboard_include__

#include "devices/Key.h"
#include "kernel/IOport.h"
#include "kernel/interrupts/ISR.h"
#include "lib/Types.h"


class Keyboard : public ISR {

private:
    Keyboard(const Keyboard &copy); // Verhindere Kopieren

    uint8_t code;           // Byte von Tastatur
    uint8_t prefix;         // Prefix von Tastatur
    Key gather;             // letzter dekodierter Key
    char leds;              // Zustand LEDs

    // Benutzte Ports des Tastaturcontrollers
    const IOport ctrl_port;    // Status- (R) u. Steuerregister (W)
    const IOport data_port;    // Ausgabe- (R) u. Eingabepuffer (W)

    // Bits im Statusregister
    enum { outb = 0x01, inpb = 0x02, auxb = 0x20 };

    // Kommandos an die Tastatur
    struct kbd_cmd {
        enum { set_led = 0xed, set_speed = 0xf3 };
    };
    enum { cpu_reset = 0xfe };

    // Namen der LEDs
    struct led {
        enum { caps_lock = 4, num_lock = 2, scroll_lock = 1 };
     };

    // Antworten der Tastatur
    struct kbd_reply {
        enum { ack = 0xfa };
     };

    // Konstanten fuer die Tastaturdekodierung
    enum { break_bit = 0x80, prefix1 = 0xe0, prefix2   = 0xe1 };

    // Klassenvariablen
    static uint8_t normal_tab[];
    static uint8_t shift_tab[];
    static uint8_t alt_tab[];
    static uint8_t asc_num_tab[];
    static uint8_t scan_num_tab[];

    // Interpretiert die Make und Break-Codes der Tastatur.
    bool key_decoded ();

    // Ermittelt anhand von Tabellen den ASCII-Code.
    void get_ascii_code ();

public:
   // speichert den ASCII-Code der zuletzt gedrückten Taste
   // Variable wird in 'trigger' geschrieben
   unsigned int lastkey;

   // Initialisierung der Tastatur.
   Keyboard ();

   // Tastaturabfrage (vorerst Polling)
   // Sollte nicht mehr verwendet werden, daher auskommentieren
   Key key_hit ();

   // Fuehrt einen Neustart des Rechners durch.
   void reboot ();

   // Einstellen der Wiederholungsrate der Tastatur.
   void set_repeat_rate (uint32_t speed, uint32_t delay);

   // Setzt oder loescht die angegebene Leuchtdiode.
   void set_led (char led, bool on);

   // Aktivierung der Unterbrechungen fuer die Tastatur
   void plugin ();

   // Unterbrechnungsroutine der Tastatur.
   void trigger ();

};

#endif
