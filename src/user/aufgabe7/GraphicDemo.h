/*****************************************************************************
 *                                                                           *
 *                  G R A P H I C D E M O                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Graphicdemo.                                             *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 20.6.2023                       *
 *****************************************************************************/
#ifndef __graphic_demo_include__
#define __graphic_demo_include__


#include "kernel/threads/Thread.h"


class GraphicDemo : public Thread {
    
private:
    int barWidth = 50;
    int barHeight = 200;
    int ballRadius = 15;
    int ballColor = 0xFF0000;
    int barColor = 0x00FF00;
    int backgroundColor = 0x0000FF;
    int wallOffset = 35;
    int barSpeed = 15;

    bool lost = false;
    GraphicDemo (const GraphicDemo &copy); // Verhindere Kopieren
    
    int linInterPol1D(int x, int xr, int l, int r);
    int linInterPol2D(int x, int y, int lt, int rt, int lb, int rb);
    void drawRect(int x, int y, int width, int height, int color);
    void drawCircle(int x, int y, int radius, int color);
    void close();
    int lBarx = 0;
    int rBarx = 0;
    int Ballx = 0;
    int Bally = 0;
    int Ballvx = 0;
    int Ballvy = 0;


public:
    GraphicDemo () : Thread() { }

    // Einstieg in die Anwendung
    void run ();
    void update();
    void lBarUp();
    void lBarDown();
    void rBarUp();
    void rBarDown();
    void restart();
 };

#endif
