/*****************************************************************************
 *                                                                           *
 *                  G R A P H I C D E M O                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Graphicdemo.                                             *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 26.6.wallOffset23                       *
 *****************************************************************************/

#include "devices/VGA.h"
#include "kernel/Globals.h"
#include "user/aufgabe7/GraphicDemo.h"
// Bitmap
#include "bmp_hhu.cc"



/*****************************************************************************
 * Methode:         GraphicDemo::linInterPol1D                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Farbwert in einer Dimension interpoliert berechnen.      *
 *****************************************************************************/
int GraphicDemo::linInterPol1D(int x, int xr, int l, int r) {
    return ((((l>>16)*(xr-x)+(r>>16)*x)/xr)<<16)
    |(((((l>>8)&0xFF)*(xr-x)+((r>>8)&0xFF)*x)/xr)<<8)
    |(((l&0xFF)*(xr-x)+(r&0xFF)*x)/xr);
}


/*****************************************************************************
 * Methode:         GraphicDemo::linInterPol2D                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Farbwert in zwei Dimensionen interpoliert berechnen.     *
 *****************************************************************************/
int GraphicDemo::linInterPol2D(int x, int y, int lt, int rt, int lb, int rb) {
    return linInterPol1D(y, kout.yres,
                         linInterPol1D(x, kout.xres, lt, rt),
                         linInterPol1D(x, kout.xres, lb, rb) );
}


/*****************************************************************************
 * Methode:         GraphicDemo::drawRect                                    *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Rechteck zeichnen.                                       *
 *****************************************************************************/
void GraphicDemo::drawRect(int x, int y, int width, int height, int color){
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            kout.drawPixel(x+i,y+j,color);
        }
    }
}


/*****************************************************************************
 * Methode:         GraphicDemo::drawCircle                                  *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Kreis zeichnen.                                          *
 *****************************************************************************/
void GraphicDemo::drawCircle(int x, int y, int radius, int color){
    for(int i = 0; i < radius; i++){
        for(int j = 0; j < radius; j++){
            if(i*i+j*j <= radius*radius){
                kout.drawPixel(x+i,y+j,color);
                kout.drawPixel(x-i,y+j,color);
                kout.drawPixel(x+i,y-j,color);
                kout.drawPixel(x-i,y-j,color);
            }
        }
    }
}


void GraphicDemo::lBarUp(){
    
    lBarx -= barSpeed;
    //draw background where bar was, but only the part where it is not anymore
    drawRect(wallOffset,lBarx+barHeight,barWidth,barSpeed,backgroundColor);
    //draw bar, but only the part that is new
    drawRect(wallOffset,lBarx,barWidth,barSpeed,barColor);
    
}

void GraphicDemo::lBarDown(){
    lBarx += barSpeed;
    drawRect(wallOffset,lBarx-barSpeed,barWidth,barSpeed,backgroundColor);
    drawRect(wallOffset,lBarx+barHeight-barSpeed,barWidth,barSpeed,barColor);
}

void GraphicDemo::rBarUp(){
    rBarx -= barSpeed;
    drawRect(kout.xres-wallOffset-barWidth,rBarx+barHeight,barWidth,barSpeed,backgroundColor);
    drawRect(kout.xres-wallOffset-barWidth,rBarx,barWidth,barSpeed,barColor);
}

void GraphicDemo::rBarDown(){
    rBarx += barSpeed;
    drawRect(kout.xres-wallOffset-barWidth,rBarx-barSpeed,barWidth,barSpeed,backgroundColor);
    drawRect(kout.xres-wallOffset-barWidth,rBarx+barHeight-barSpeed,barWidth,barSpeed,barColor);
}



void GraphicDemo::update(){
    //update ball
    drawCircle(Ballx,Bally,ballRadius,backgroundColor);
    Bally += Ballvy;
    Ballx += Ballvx;
    drawCircle(Ballx,Bally,ballRadius,ballColor);
    //check collision
    if (Bally >= lBarx && Bally <= lBarx+barHeight && Ballx <= wallOffset+barWidth+ballRadius){
        Ballvx *= -1;
        Ballvy = (Bally-lBarx-barHeight/2)/10;
        if (Ballvx < 0){
            Ballvx = Ballvx-1;
        }else{
            Ballvx = Ballvx+1;
        }
        drawRect(wallOffset,lBarx,barWidth,barHeight,barColor);
    }
    if (Bally >= rBarx && Bally <= rBarx+barHeight && Ballx >= kout.xres-wallOffset-barWidth-ballRadius){
        Ballvx *= -1;
        if (Ballvx < 0){
            Ballvx = Ballvx-1;
        }else{
            Ballvx = Ballvx+1;
        }
        Ballvy = (Bally-rBarx-barHeight/2)/10;
        drawRect(kout.xres-wallOffset-barWidth,rBarx,barWidth,barHeight,barColor);
    }

    if (Bally <= ballRadius || Bally >= kout.yres-ballRadius){
        Ballvy *= -1;
    }
    if (Ballx <= ballRadius || Ballx >= kout.xres-ballRadius){
        lost=true;
        Ballvx = 0;
        Ballvy = 0;
    }
}

void GraphicDemo::restart(){
    if (!lost){
       return;
    }
    lost = false;
    Ballx = kout.xres/2;
    Bally = kout.yres/2;
    Ballvx = systime%2 == 0 ? 10 : -10;
    Ballvy = systime%10;
    drawCircle(Ballx,Bally,ballRadius,ballColor);
    
}



/*****************************************************************************
 * Methode:         GraphicDemo::run                                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Hauptthread der Anwendung.                               *
 *****************************************************************************/
void GraphicDemo::run () {
    kout.clear ();
    Ballx = kout.xres/2;
    Bally = kout.yres/2;
    Ballvx = systime%2 == 0 ? 10 : -10;
    Ballvy = systime%10;

    // hintergrund zeichnen
    for (uint32_t y=0; y < kout.yres; y++) {
        for (uint32_t x=0; x < kout.xres; x++) {
            kout.drawPixel(x, y, backgroundColor);
        }
    }
    lost=false;
    

    // Rechteck zeichnen
    drawRect(wallOffset,wallOffset,barWidth,barHeight,barColor);
    drawRect(kout.xres-wallOffset-barWidth,wallOffset,barWidth,barHeight,barColor);
    //drawCircle(kout.xres/2,kout.yres/2,ballRadius,ballColor);
    
    //kout.drawBitmap(wallOffset,barSpeed0,hhu.width,hhu.height, (unsigned char*) hhu.pixel_data, hhu.bytes_per_pixel);
    
    // selbst terminieren
    
}

void GraphicDemo::close(){
    scheduler.exit ();
}
