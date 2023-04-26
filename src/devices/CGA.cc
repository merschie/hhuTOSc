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



/*****************************************************************************
 * Methode:         CGA::setpos                                              *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Setzen des Cursors in Spalte x und Zeile y.              *
 *****************************************************************************/
void CGA::setpos (int x, int y) {
    unsigned short position = x + y * CGA::COLUMNS;

    CGA::index_port.outb(15);
    CGA::data_port.outb(position & 0xff);
    CGA::index_port.outb(14);
    CGA::data_port.outb((position >> 8 ) & 0xff);
}


/*****************************************************************************
 * Methode:         CGA::getpos                                              *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Abfragem der Cursorposition                              *
 *                                                                           *
 * Rückgabewerte:   x und y                                                  *
 *****************************************************************************/
void CGA::getpos (int &x, int &y) {


    unsigned short position;

    CGA::index_port.outb(14);
    position = CGA::data_port.inb() << 8;
    CGA::index_port.outb(15);
    position = position | CGA::data_port.inb();

    y = (unsigned short)(position / CGA::COLUMNS);
    x = position - (y * CGA::COLUMNS);

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
    int tempx = 0;
    int tempy = 0;
    getpos(tempx, tempy);
    setpos(x, y);
    print(&character, 1, attrib);
    setpos(tempx, tempy);       
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
    int x=5;
    int y=0;
    getpos(x, y);

    pos = CGA_START + 2*(x + y*80);
    for (int i = 0; i < n; i++) {
        if (string[i] == '\n') {
            i++;
            y++;
            x = 0;
            pos = CGA_START + 2*(x + y*80);
        }
        else if(y > 24) {
            scrollup();
            y = 24;
            pos = CGA_START + 2*(x + y*80);
        }
        else if (x > 79) {
            y++;
            x = 0;
            pos = CGA_START + 2*(x + y*80);
        }
        else{
            *pos = string[i];
            *(pos + 1) = attrib;
            pos += 2;
            x++;
        }
    }
    setpos(x, y);
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
