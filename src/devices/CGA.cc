/*****************************************************************************
 *                                                                           *
 *                                    C G A                                  *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Mit Hilfe dieser Klasse kann man auf den Bildschirm des  *
 *                  PCs zugreifen. Der Zugriff erfolgt direkt auf der Hard-  *
 *                  wareebene, d.h. ueber den Bildschirmspeicher und den     *
 *                  I/O-Ports der Grafikkarte.                               *
 *                                                                           *
 * Autor:           Olaf Spinczyk, TU Dortmund                               *
 *                  Aenderungen von Michael Schoettner, HHU, 21.8.2016       *
 *****************************************************************************/
#include "devices/CGA.h"
int CGA::x = 0;
int CGA::y = 0;


/*****************************************************************************
 * Methode:         CGA::setpos                                              *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Setzen des Cursors in Spalte x und Zeile y.              *
 *****************************************************************************/
void CGA::setpos (int x, int y) {

    /* Hier muess Code eingefuegt werden */
    CGA::x = x;
    CGA::y = y;
    
}


/*****************************************************************************
 * Methode:         CGA::getpos                                              *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Abfragem der Cursorposition                              *
 *                                                                           *
 * Rückgabewerte:   x und y                                                  *
 *****************************************************************************/
void CGA::getpos (int &x, int &y) {
    x = CGA::x;
    y = CGA::y;
    /* Hier muess Code eingefuegt werden */
    //return CGA::x, CGA::y;
}


/*****************************************************************************
 * Methode:         CGA::show                                                *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Anzeige eines Zeichens mit Attribut an einer bestimmten  *
 *                  Stelle auf dem Bildschirm.                               *
 *                                                                           *
 * Parameter:                                                                *
 *      x,y         Position des Zeichens                                    *
 *      character   Das auszugebende Zeichen                                 *
 *      attrib      Attributbyte fuer das Zeichen                            *
 *****************************************************************************/
void CGA::show (int x, int y, char character, unsigned char attrib) {
    attrib = attribute(GREEN, BLACK, true);
    int tempx = CGA::x;
    int tempy = CGA::y;
    CGA::x = x;
    CGA::y = y;
    print(&character, 1, attrib);
    CGA::x = tempx;
    CGA::y = tempy;
       
}


/*****************************************************************************
 * Methode:         CGA::print                                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Anzeige von 'n' Zeichen ab der aktuellen Cursorposition  *
 *                  '\n' fuer Zeilenvorschub.                                *
 *                                                                           *
 * Parameter:                                                                *
 *      string      Auszugebende Zeichenkette                                *
 *      n           Laenger der Zeichenkette                                 *
 *      attrib      Attributbyte fuer alle Zeichen der Zeichenkette          *
 *****************************************************************************/
void CGA::print (char* string, int n, unsigned char attrib) {
    char *CGA_START = (char *)0xb8000;
    char *pos;
    pos = CGA_START + 2*(x + y*80);
    for (int i = 0; i < n; i++) {
        if (string[i] == '\n') {
            i++;
            y++;
            x = 0;
            pos = CGA_START + 2*(x + y*80);
        }
        *pos = string[i];
        *(pos + 1) = attrib;
        pos += 2;
    }
    x=x+n;
}


/*****************************************************************************
 * Methode:         CGA::scrollup                                            *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Verschiebt den Bildschirminhalt um eine Zeile nach oben. *
 *                  Die neue Zeile am unteren Bildrand wird mit Leerzeichen  *
 *                  gefuellt.                                                *
 *****************************************************************************/
void CGA::scrollup () {
    char *old = (char *)0xb8000 + 160;
    char *neww = (char *)0xb8000;
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80*2; j++) {
            *neww = *old;
            old +=1;
            neww +=1;
        }
    }
}


/*****************************************************************************
 * Methode:         CGA::clear                                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Lösche den Textbildschirm.                               *
 *****************************************************************************/
void CGA::clear () {
    char *CGA_START = (char *)0xb8000;
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80*2; j++) {
            *CGA_START = 0x0;
            CGA_START +=1;
        }
    }
}


/*****************************************************************************
 * Methode:         CGA::attribute                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Hilfsfunktion zur Erzeugung eines Attribut-Bytes aus     *
 *                  Hintergrund- und Vordergrundfarbe und der Angabe, ob das *
 *                  Zeichen blinkend darzustellen ist.                       *
 *                                                                           *
 * Parameter:                                                                *
 *      bg          Background color                                         *
 *      fg          Foreground color                                         *
 *      blink       ywa/no                                                   *
 *****************************************************************************/
unsigned char CGA::attribute (CGA::color bg, CGA::color fg, bool blink) {
    
    unsigned char attrib = 0;
    attrib = attrib | bg;
    attrib = attrib | fg << 4;
    if (blink) {
        attrib = attrib | 0x80;
    }
    return attrib;
    
}
