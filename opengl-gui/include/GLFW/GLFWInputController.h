#pragma once
#include "Widgets\WidgetGroup.h"

namespace OpenGLGUI {
	namespace GLFWInputController {
		void initializeCallbacks(GLFWwindow *window);
		void applyInputQueue(WidgetGroup &w);
		void clearInputQueue();
	}
}

