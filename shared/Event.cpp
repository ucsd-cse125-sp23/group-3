#include "Event.h"

Event::Event() {
	this->eventType = EventType::NOEVENT;
}

Event::Event(EventType eventType) {
	this->eventType = eventType;
}

EventType Event::getEventType() {
	return this->eventType;
}

void Event::setEventType(EventType et) {
	this->eventType = et;
}