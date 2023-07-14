/*****************************************************************************
 *                                                                           *
 *                  G R A P H I C D E M O                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Graphicdemo.                                             *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 26.6.2023                       *
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






/*****************************************************************************
 * Methode:         GraphicDemo::run                                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Hauptthread der Anwendung.                               *
 *****************************************************************************/
void GraphicDemo::run () {
    kout.clear ();

    // Farbverlauf zeichnen  
    for (uint32_t y=0; y < kout.yres; y++) {
        for (uint32_t x=0; x < kout.xres; x++) {
            kout.drawPixel(x, y, 0x0000FF);
        }
    }
    

    // Rechteck zeichnen
    drawRect(20,20,50,200,0x00FF00);
    drawRect(kout.xres-20-50,20,50,200,0x00FF00);
    drawCircle(kout.xres/2,kout.yres/2,15,0xFF0000);
    
    //kout.drawBitmap(20,100,hhu.width,hhu.height, (unsigned char*) hhu.pixel_data, hhu.bytes_per_pixel);
    
    // selbst terminieren
    
}

void GraphicDemo::close(){
    scheduler.exit ();
}
