#pragma once
#include <unordered_map>

#include "InputState.h"

namespace OpenGLGUI
{
	class MouseState
	{
	private:
		int xPosition;
		int yPosition;
		int deltaPositionX;
		int deltaPositionY;
		std::unordered_map<MouseButton, InputState> state;
		MouseButton mostRecentlyChangedButton;
		int wheelTicks;
	public:
		MouseState();
		~MouseState();

		int x() const;
		int y() const;
		int deltaX() const;
		int deltaY() const;
		int wheel() const;

		void setPosition(int x, int y);
		void setPositionDelta(int deltaX, int deltaY);
		void setWheelTicks(int ticks);
		void setWheelTicksDelta(int deltaTicks);
		void setButtonState(MouseButton button, InputState inputState);
		void clear();

		const InputState& operator[](MouseButton button) const;
		const MouseButton& buttonWithMostRecentStateChange() const;
	};
}
