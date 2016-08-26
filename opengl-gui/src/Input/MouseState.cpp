#include "Input/MouseState.h"

namespace OpenGLGUI
{
	MouseState::MouseState() : mousePosition(glm::vec2(0,0)), mouseDeltaPosition(glm::vec2(0,0)), wheelTicks(0), mostRecentlyChangedButton(MouseButton::Left)
	{
		state[MouseButton::Left] = InputState::Released;
		state[MouseButton::Right] = InputState::Released;
		state[MouseButton::Middle] = InputState::Released;
	}

	MouseState::~MouseState()
	{
	}

	glm::vec2 MouseState::position() const { return mousePosition; }
	glm::vec2 MouseState::deltaPosition() const { return mouseDeltaPosition; }
	int MouseState::wheel() const
	{
		return wheelTicks;
	}

	void MouseState::setPosition(int x, int y)
	{
		glm::vec2 newPosition(x, y);
		mouseDeltaPosition = newPosition - mousePosition;
		mousePosition = newPosition;
	}
	void MouseState::setPositionDelta(int deltaX, int deltaY)
	{
		mouseDeltaPosition = glm::vec2(deltaX, deltaY);
		mousePosition += mouseDeltaPosition;
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
		mostRecentlyChangedButton = button;
	}
	void MouseState::clear()
	{
		for (auto key = state.begin(); key != state.end(); key++)
		{
			key->second = InputState::Released;
		}
		mousePosition = glm::vec2(0, 0);
		mouseDeltaPosition = glm::vec2(0, 0);
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
