#include "GlobalVariables.h"

class Event {
public:
    Event();
    Event(EventType eventType);

    EventType getEventType();

    void setEventType(EventType);

protected:
    EventType eventType;
};