#include "kernel/Globals.h"
#include "user/aufgabe1/TextDemo.h"
#include "user/aufgabe2/HeapDemo.h"
#include "user/aufgabe2/SoundDemo.h"
#include "user/aufgabe4/HelloWorldThread.h"
#include "user/aufgabe4/SoundThread.h"

void menu(int i){
    
    if(i==48){
        aufgabe=0;
        kout.clear();
        kout.setpos(0,1);
        kout << "1. Textausgabe" << endl;
        kout << "2. Sound abspielen" << endl;
        kout << "3. Speicherverwaltung" << endl;
        kout << "4. Preemptives Multitasking" << endl;
        }
    else if(i==49){
        aufgabe=1;
        text_demo();
        }
    else if(i==50){
        kout.clear();
        kout.setpos(0,2);
        kout << "2. Sound abspielen" << endl;
        aufgabe=2;
        SoundThread *sound = new SoundThread();
        scheduler.ready(sound);
        scheduler.schedule();
    }
    else if(i==51){
        aufgabe=3;
        heap_demo();
    }
    else if(i==52){
        aufgabe=4;
        kout.clear();
        //create Threads for showing
        HelloWorldThread *hello = new HelloWorldThread();
        HelloWorldThread *hello2 = new HelloWorldThread();
        HelloWorldThread *hello3 = new HelloWorldThread();
        scheduler.ready(hello);
        scheduler.ready(hello2);
        scheduler.ready(hello3);
        scheduler.schedule();
    }
                
}