#pragma once
#include <deque>

#include "Widgets/Widget.h"

#include "Graphics/WidgetDetails.h"

#include "Input/MouseState.h"
#include "Input/KeyboardState.h"

namespace OpenGLGUI
{
	enum class Key;
	enum class MouseButton;
	enum class InputState;

	class WidgetGroup
	{
	private:
		std::deque<std::shared_ptr<Widget>> registeredWidgets;
		KeyboardState keyboardState;
		MouseState mouseState;

		void notifyWidgetsOfMouseEvent(EventType eventType);
		void notifyWidgetsOfKeyboardEvent(EventType eventType);

	public:
		WidgetGroup();
		~WidgetGroup();

		void registerWidget(std::shared_ptr<Widget> widget);
		void deregisterWidget(std::shared_ptr<Widget> widget);

		void setKeyState(Key key, InputState state);
		void setMouseState(MouseButton button, InputState state);
		void setMouseWheel(int tick);
		void setMouseWheelDelta(int delta);
		void setMousePosition(int x, int y);
		void setMousePositionDelta(int deltaX, int deltaY);

		void clearKeyboardState();
		void clearMouseState();

		void draw();
	};
}

