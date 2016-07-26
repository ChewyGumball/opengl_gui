#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GLFW\GLFWInputController.h"
#include "Input\InputState.h"
#include "Events\Event.h"

namespace {
	struct InputEvent {
		OpenGLGUI::EventType type;
		OpenGLGUI::InputState state;
		union
		{
			OpenGLGUI::Key key;
			OpenGLGUI::MouseButton button;
		};
	};

	std::vector<InputEvent> inputQueue;

	void keyboardCallback(GLFWwindow *window, int key, int scanCode, int action, int mods)
	{

	}

	void mouseMoveCallback(GLFWwindow *window, double xPosition, double yPosition)
	{

	}

	void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
	{

	}

	void mouseScrollCallback(GLFWwindow *window, double xOffset, double yOffset)
	{

	}
}

namespace OpenGLGUI {
	namespace GLFWInputController {
		void initializeCallbacks() {

		}
		void applyInputQueue(WidgetGroup &w) {

		}
		void clearInputQueue() {

		}
	}
}