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


class Queue {

struct QueueElement
{
    QueueElement* next;
    void* data;
};
    
private:
    Queue(const Queue &copy); // Verhindere Kopieren
    QueueElement* first;

public:
    void init();
    void* getFirst();
    void addElement(void* data);
    Queue() {}
};

