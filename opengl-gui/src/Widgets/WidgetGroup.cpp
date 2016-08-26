#include <GL\glew.h>
#include <vector>

#include "Widgets/WidgetGroup.h"
#include "Events/Event.h"
#include "Input/InputState.h"




namespace OpenGLGUI
{
	WidgetGroup::WidgetGroup()
	{
	}
	WidgetGroup::~WidgetGroup()
	{
	}

	void WidgetGroup::registerWidget(std::shared_ptr<Widget> widget)
	{
		registeredWidgets.push_front(widget);
	}
	void WidgetGroup::deregisterWidget(std::shared_ptr<Widget> widget)
	{
		registeredWidgets.erase(std::find(registeredWidgets.begin(), registeredWidgets.end(), widget));
	}

	/*Input Functions*/
	void  WidgetGroup::setKeyState(Key key, InputState state)
	{
		keyboardState.setKeyState(key, state);
		notifyWidgetsOfKeyboardEvent(state == InputState::Pressed ? EventType::KeyPressed : EventType::KeyReleased);
	}
	void  WidgetGroup::setMouseState(MouseButton button, InputState state)
	{
		mouseState.setButtonState(button, state);
		notifyWidgetsOfMouseEvent(state == InputState::Pressed ? EventType::MouseButtonPressed : EventType::MouseButtonReleased);
	}
	void  WidgetGroup::setMouseWheel(int tick)
	{
		mouseState.setWheelTicks(tick);
		notifyWidgetsOfMouseEvent(EventType::MouseWheelScroll);
	}
	void  WidgetGroup::setMouseWheelDelta(int delta)
	{
		mouseState.setWheelTicksDelta(delta);
		notifyWidgetsOfMouseEvent(EventType::MouseWheelScroll);
	}
	void  WidgetGroup::setMousePosition(int x, int y)
	{
		mouseState.setPosition(x, y);
		notifyWidgetsOfMouseEvent(EventType::MouseMove);
	}
	void  WidgetGroup::setMousePositionDelta(int deltaX, int deltaY)
	{
		mouseState.setPositionDelta(deltaX, deltaY);
		notifyWidgetsOfMouseEvent(EventType::MouseMove);
	}

	void  WidgetGroup::clearKeyboardState()
	{
		keyboardState.clear();
	}
	void  WidgetGroup::clearMouseState()
	{
		mouseState.clear();
	}

	void WidgetGroup::notifyWidgetsOfMouseEvent(EventType eventType)
	{
		OpenGLGUI::Event event(keyboardState, mouseState);
		for (auto widget = registeredWidgets.begin(); widget != registeredWidgets.end() && !event.consumed(); widget++)
		{
			(*widget)->notify(eventType, event);
		}
	}
	void WidgetGroup::notifyWidgetsOfKeyboardEvent(EventType eventType)
	{
		OpenGLGUI::Event event(keyboardState, mouseState);
		for (auto widget = registeredWidgets.begin(); widget != registeredWidgets.end() && !event.consumed(); widget++)
		{
			(*widget)->notify(eventType, event);
		}
	}

	/*Drawing Functions*/
	void  WidgetGroup::draw()
	{
		for (auto w : registeredWidgets)
		{
			w->draw(glm::vec2(0, 0));
		}
	}
}
