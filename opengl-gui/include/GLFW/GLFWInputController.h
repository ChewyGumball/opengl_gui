#pragma once
#include "Widgets\WidgetGroup.h"

namespace OpenGLGUI {
	namespace GLFWInputController {
		void initializeCallbacks();
		void applyInputQueue(WidgetGroup &w);
		void clearInputQueue();
	}
}

