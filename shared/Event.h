#include "GlobalVariables.h"

class Event {
public:
    Event(EventType eventType);

    EventType getEventType();

protected:
    EventType eventType;
};