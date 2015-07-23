#pragma once

#include "Event.h"

namespace OpenGLGUI
{
	class Widget;
	class EventSubscription
	{
	private:
		const unsigned short receipt;
	public:
		const Widget &source;
		const EventType eventType;

		EventSubscription(Widget &sourceWidget, EventType type, unsigned short receiptNumber);

		bool operator==(const EventSubscription &other) const;

		friend std::hash<EventSubscription>;
	};
}

namespace std {
	template <>
	struct hash<OpenGLGUI::EventSubscription>
	{
		size_t operator()(const OpenGLGUI::EventSubscription &subscription) const
		{
			return hash<short>()(subscription.receipt);
		}
	};
}

