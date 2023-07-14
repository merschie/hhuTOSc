#include "kernel/Globals.h"
#include "user/aufgabe1/TextDemo.h"
#include "user/aufgabe2/HeapDemo.h"
#include "user/aufgabe2/SoundDemo.h"
#include "user/aufgabe4/HelloWorldThread.h"

void menu(int i){
    
    if(i==48){
        kout.clear();
        kout.setpos(0,1);
        kout << "1. Textausgabe" << endl;
        kout << "2. Sound abspielen" << endl;
        kout << "3. Speicherverwaltung" << endl;
        kout << "4. Preemptives Multitasking" << endl;
        }
    else if(i==49){
        text_demo();
        }
    else if(i==50){
        pcspk.tetris();
    }
    else if(i==51){
        heap_demo();
    }
    else if(i==52){
        kout.clear();
        scheduler.schedule();
    }
                
}