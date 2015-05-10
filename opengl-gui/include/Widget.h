#pragma once
#include <functional>
#include <unordered_map>
#include <vector>

#include "Events\Event.h"
#include "Events\EventSubscription.h"

class Widget
{
private:
	std::unordered_multimap<EventType, short> reclaimedReceiptNumbers;
	std::unordered_map<EventType, short> highestReceiptNumber;
	std::unordered_map<EventType, std::unordered_map<EventSubscription, std::function<void(Event&)>>> eventHandlers;

	short nextReceiptNumber(EventType type);
public:
	EventSubscription subscribe(EventType type, std::function<void(Event&)> callback);
	void unsubscribe(EventSubscription& subscription);

	void notify(EventType type, Event& eventData);
};

