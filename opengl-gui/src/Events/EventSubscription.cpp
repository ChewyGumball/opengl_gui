#include "Widget.h"
#include "Events/EventSubscription.h"

EventSubscription::EventSubscription(Widget &sourceWidget, EventType type, unsigned short receiptNumber) 
	: source(sourceWidget), eventType(type), receipt(receiptNumber) 
{}

bool EventSubscription::operator==(const EventSubscription& other) const
{
	return other.eventType == eventType && other.receipt == receipt && &other.source == &source;
}
