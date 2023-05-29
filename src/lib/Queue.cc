#include "Queue.h"
//#include "kernel/Globals.h"

Queue::Queue () {
    struct QueueElement first = QueueElement();
    first.element = nullptr;
    first.next = nullptr;
    start = first;
}

void Queue::addElement(void* pntr) {
    QueueElement *newElement = new QueueElement();
    newElement->element = pntr;
    newElement->next = nullptr;
    QueueElement *current = &start;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newElement;
}

void* Queue::getFirst() {
    QueueElement *tmp = start.next;
    void* data = tmp->element;
    start.next = tmp->next;
    delete tmp;
    return data;
}

void Queue::dump() {
    QueueElement *tmp = &start;
    while (tmp->next != 0) {
        //kout << "Data: " << tmp->element << " Next: " << tmp->next << endl;
        tmp = tmp->next;
    }
    //kout << "Data: " << tmp->element << " Next: " << tmp->next << "End!!!" << endl;
}

void Queue::deleteElement(void *element) {
    QueueElement *current = &start;
    while(current->next != nullptr) {
        if(current->next->element == element) {
            QueueElement *to_delete = current->next;
            current->next = current->next->next;
            delete(to_delete);
        }
        current = current->next;
    }
}