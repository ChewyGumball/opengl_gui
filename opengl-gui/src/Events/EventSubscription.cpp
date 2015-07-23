#include "Widgets/Widget.h"
#include "Events/EventSubscription.h"

namespace OpenGLGUI
{
	EventSubscription::EventSubscription(Widget &sourceWidget, EventType type, unsigned short receiptNumber)
		: receipt(receiptNumber), source(sourceWidget), eventType(type)
	{}

	bool EventSubscription::operator==(const EventSubscription& other) const
	{
		return other.eventType == eventType && other.receipt == receipt && &other.source == &source;
	}
}
