#pragma once

#include "Input/KeyboardState.h"
#include "Input/MouseState.h"

namespace OpenGLGUI
{
	enum class EventType {
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMove,
		MouseOver,
		KeyReleased,
		KeyPressed,
		MouseWheelScroll
	};

	class Event {
		bool propagate;
	public:

		const KeyboardState &keyboard;
		const MouseState &mouse;

		Event(KeyboardState &kState, MouseState &mState);

		void consume();
		bool consumed();
		void reset();
	};
}

//This allows EventType to be used in an unordered_* container
namespace std {
	template <>
	struct hash<OpenGLGUI::EventType>
	{
		size_t operator()(const OpenGLGUI::EventType &type) const
		{
			return hash<char>()(static_cast<char>(type));
		}
	};
}

