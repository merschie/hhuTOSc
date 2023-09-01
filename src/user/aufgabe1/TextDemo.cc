/*****************************************************************************
 *                                                                           *
 *                           T E X T D E M O                                 *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Testausgaben für den CGA-Treiber.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 26.10.2018                       *
 *****************************************************************************/

#include "kernel/Globals.h"


void text_demo() {
   kout.clear();
   kout.setpos(0, 0);
   kout << "Text Demo" << endl;
   kout.setpos(0, 2);
   kout << "   | dec | hex | bin   |" << endl;
   kout << "   ---------------------" << endl;
   int x,y;
   kout.getpos(x,y);
   for(int i = 0; i < 17; i++)
   {
   kout.getpos(x,y);
   kout << "   | " << dec << i << endl;
   kout.setpos(x+9,y);
   kout << "| " << hex << i << endl;
   kout.setpos(x+15,y);
   kout << "| " << bin << i << endl;
   kout.setpos(x+23,y);
   kout << "|" << endl;
   }
   kout << "   ---------------------" << endl;
   kout << "Zeilenumbruch" << endl;
   kout << "Zeilenumbruch" << endl;
   kout << "Zeilenumbruch" << endl;
   kout << "Zeilenumbruch" << endl;
   kout << "Zeilenumbruch" << endl;
   kout << "Zeilenumbruch" << endl;
   kout << "Zeilenumbruch" << endl;

   }
