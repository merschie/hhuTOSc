#include "Queue.h"
#include "kernel/Globals.h"

void Queue::init() {
    this->first->next = 0;
    this->first->data = 0;
}

void Queue::addElement(void* pntr) {
    kout << "size of  Element" << (uint64_t)sizeof(QueueElement) << endl;
    QueueElement* newElement = (QueueElement*)allocator.alloc(sizeof(QueueElement));
    //newElement->data = pntr;
    //newElement->next = 0;
    QueueElement* current = this->first;
    while (current->next != 0) {
        current = current->next;
    }
    //current->next = newElement;
}

void* Queue::getFirst() {
    QueueElement* tmp = this->first;
    first = first->next;
    void* data = tmp->data;
    //delete(tmp);
    return data;
}

void Queue::dump() {
    QueueElement* tmp = this->first;
    while (tmp->next != 0) {
        kout << "Data: " << tmp->data << " Next: " << tmp->next << endl;
        tmp = tmp->next;
    }
    kout << "Data: " << tmp->data << " Next: " << tmp->next << "End!!!" << endl;
}