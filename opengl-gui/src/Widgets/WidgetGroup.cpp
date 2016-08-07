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

	void WidgetGroup::registerWidget(Widget& pane)
	{
		registeredWidgets.push_front(pane);
	}
	void WidgetGroup::deregisterWidget(Widget& pane)
	{
		registeredWidgets.erase(std::find(registeredWidgets.begin(), registeredWidgets.end(), pane));
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
			widget->get().notify(eventType, event);
		}
	}
	void WidgetGroup::notifyWidgetsOfKeyboardEvent(EventType eventType)
	{
		OpenGLGUI::Event event(keyboardState, mouseState);
		for (auto widget = registeredWidgets.begin(); widget != registeredWidgets.end() && !event.consumed(); widget++)
		{
			widget->get().notify(eventType, event);
		}
	}

	/*Drawing Functions*/
	void  WidgetGroup::draw() 
	{
		for (Widget& w : registeredWidgets)
		{
			w.draw();
		}
	}

	void  WidgetGroup::createWidgetDetails()
	{
		std::vector<WidgetDetails> details;
		for (Widget& w : registeredWidgets)
		{
			createWidgetDetails(w, details);
		}

	}

	void WidgetGroup::createWidgetDetails(Widget& widget, std::vector<WidgetDetails> detailList)
	{
		detailList.push_back({ widget.X(), widget.Y(), widget.width(), widget.height() });
		createWidgetDetails(*(widget.childWidget()), detailList);

		//Make quad buffer
		GLuint vbo = 0;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		float quad[] = {
			0.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			1.0, 1.0, 0.0,
			1.0, 0.0, 0.0
		};

		glBufferData(vbo, 12 * sizeof(float), quad, GL_STATIC_DRAW);

		//Make 
	}

}
