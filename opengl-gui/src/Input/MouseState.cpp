#include "Input/MouseState.h"

namespace OpenGLGUI
{
	MouseState::MouseState() : xPosition(0), yPosition(0), wheelTicks(0), mostRecentlyChangedButton(MouseButton::Left)
	{
		state[MouseButton::Left] = InputState::Released;
		state[MouseButton::Right] = InputState::Released;
		state[MouseButton::Middle] = InputState::Released;
	}

	MouseState::~MouseState()
	{
	}

	int MouseState::x() const
	{
		return xPosition;
	}
	int MouseState::y() const
	{
		return yPosition;
	}
	int MouseState::wheel() const
	{
		return wheelTicks;
	}

	void MouseState::setPosition(int x, int y)
	{
		xPosition = x;
		yPosition = y;
	}
	void MouseState::setPositionDelta(int deltaX, int deltaY)
	{
		xPosition += deltaX;
		yPosition += deltaY;
	}
	void MouseState::setWheelTicks(int ticks)
	{
		wheelTicks = ticks;
	}
	void MouseState::setWheelTicksDelta(int deltaTicks)
	{
		wheelTicks += deltaTicks;
	}

	void MouseState::setButtonState(MouseButton button, InputState inputState)
	{
		state[button] = inputState;
	}
	void MouseState::clear()
	{
		for (auto key = state.begin(); key != state.end(); key++)
		{
			key->second = InputState::Released;
		}
		xPosition = 0;
		yPosition = 0;
		wheelTicks = 0; 
		mostRecentlyChangedButton = MouseButton::Left;
	}

	const InputState& MouseState::operator[](MouseButton button) const
	{
		return state.find(button)->second;
	}
	const MouseButton& MouseState::buttonWithMostRecentStateChange() const
	{
		return mostRecentlyChangedButton;
	}
}
