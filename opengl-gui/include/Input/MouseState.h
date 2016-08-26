#pragma once
#include <unordered_map>
#include <glm/vec2.hpp>

#include "InputState.h"

namespace OpenGLGUI
{
	class MouseState
	{
	private:
		glm::vec2 mousePosition;
		glm::vec2 mouseDeltaPosition;
		std::unordered_map<MouseButton, InputState> state;
		MouseButton mostRecentlyChangedButton;
		int wheelTicks;
	public:
		MouseState();
		~MouseState();

		glm::vec2 position() const;
		glm::vec2 deltaPosition() const;
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
