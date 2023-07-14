#include "lib/Semaphore.h"
#include "kernel/threads/Thread.h"
#include "kernel/Globals.h"


void Semaphore::p(){
    lock.acquire();
    bool more = counter > 0;
    if(more){
        counter--;  
        lock.release();
    }else{
        waitQueue.addElement(scheduler.get_active());
        lock.release();
        scheduler.block();
    }

}

void Semaphore::v(){
    lock.acquire();
    if(waitQueue.isEmpty()){
        counter++;
    }else{
        Thread* next = (Thread *) waitQueue.getFirst();
        scheduler.deblock(*next);
    }
    lock.release();
}