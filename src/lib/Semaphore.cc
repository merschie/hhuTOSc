#include "lib/Semaphore.h"
#include "kernel/threads/Thread.h"
#include "kernel/Globals.h"


void Semaphore::p(){
    lock.acquire();
    if(counter > 0){
        counter--;  
    }else{
        waitQueue.addElement(scheduler.get_active());
    }
    lock.release();
}

void Semaphore::v(){
    lock.acquire();
    if(waitQueue.isEmpty()){
        counter++;
    }else{
        Thread* next = (Thread *) waitQueue.getFirst();
        scheduler.dispatch(*next);
    }
    lock.release();
}