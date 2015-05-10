#pragma once

#include "KeyboardState.h"
#include "MouseState.h"

enum EventType : char {
	MouseDown,
	MouseUp,
	MouseMove,
	MouseOver,
	MouseClick,
	KeyDown,
	KeyUp,
	KeyPressed,
	MouseWheelScroll
};

//This allows EventType to be used in an unordered_* container
namespace std {
	template <>
	struct hash<EventType>
	{
		size_t operator()(const EventType &type) const
		{
			return hash<char>()(static_cast<char>(type));
		}
	};
}

class Event {
	bool propagate;
public:

	const KeyboardState &keyboard;
	const MouseState &mouse;

	Event(KeyboardState &kState, MouseState &mState);

	void consume();
	bool consumed();
};

