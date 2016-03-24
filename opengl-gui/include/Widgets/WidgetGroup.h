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
		std::deque<std::reference_wrapper<Widget>> registeredWidgets;
		KeyboardState keyboardState;
		MouseState mouseState;

		void notifyWidgetsOfMouseEvent(EventType eventType);
		void notifyWidgetsOfKeyboardEvent(EventType eventType);

		void createWidgetDetails();
		void createWidgetDetails(Widget& widget, std::vector<WidgetDetails> detailList);

	public:
		WidgetGroup();
		~WidgetGroup();

		void registerWidget(Widget& pane);
		void deregisterWidget(Widget& pane);

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

