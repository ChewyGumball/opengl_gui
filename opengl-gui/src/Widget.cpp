#include "Widget.h"

short Widget::nextReceiptNumber(EventType type)
{
	auto reclaimed = reclaimedReceiptNumbers.find(type);
	if (reclaimed == reclaimedReceiptNumbers.end())
	{
		return highestReceiptNumber[type]++;
	}
	else
	{
		short receipt = reclaimed->second;
		reclaimedReceiptNumbers.erase(reclaimed);
		return receipt;
	}
}

EventSubscription Widget::subscribe(EventType type, std::function<void(Event&)> callback)
{
	EventSubscription subscription(*this, type, nextReceiptNumber(type));
	eventHandlers[type][subscription] = callback;

	return subscription;
}

void Widget::unsubscribe(EventSubscription& subscription)
{
	if (&subscription.source == this)
	{
		eventHandlers[subscription.eventType].erase(subscription);
	}
}

void Widget::notify(EventType type, Event& eventData)
{
	if (eventHandlers.count(type) > 0)
	{
		for (auto &callback : eventHandlers[type])
		{
			callback.second(eventData);
		}
	}
}