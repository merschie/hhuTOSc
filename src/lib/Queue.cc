#include "Queue.h"


void Queue::init() {
    first = new QueueElement;
    first->next = 0;
    first->data = 0;
}

void Queue::addElement(void* data) {
    QueueElement* newElement = new QueueElement;
    newElement->data = data;
    newElement->next = 0;
    while (first->next != 0) {
        first = first->next;
    }
    first->next = newElement;
}

void* Queue::getFirst() {
    QueueElement* tmp = first;
    first = first->next;
    void* data = tmp->data;
    delete tmp;
    return data;
}