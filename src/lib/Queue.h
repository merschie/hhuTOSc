/*****************************************************************************
 *                                                                           *
 *                              Q U E U E                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung einer einfach verketteten Liste von      *
 *                  QUEUE Objekten.                                          *
 *                                                                           *
 * Autor:           Fabian Mersch                                            *
 *****************************************************************************/




struct QueueElement
{
    struct QueueElement *next;
    void* element;
};

class Queue {

private:
    struct QueueElement start;

public:
    Queue();
    void* getFirst();
    void addElement(void* element);
    void dump();
    void deleteElement(void* element);
};

