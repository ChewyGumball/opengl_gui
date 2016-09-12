#include <iostream>
#include <unordered_map>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GLFW/GLFWInputController.h"
#include "Input/InputState.h"
#include "Events/Event.h"


namespace {

	std::unordered_map<int, OpenGLGUI::Key> glfwKeyMapping{

	};
	std::unordered_map<int, OpenGLGUI::MouseButton> glfwMouseMapping {
		{ 0, OpenGLGUI::MouseButton::Left },
		{ 1, OpenGLGUI::MouseButton::Right },
		{ 2, OpenGLGUI::MouseButton::Middle }
	};

	struct InputEvent {
		OpenGLGUI::EventType type;
		union
		{
			OpenGLGUI::Key key;
			OpenGLGUI::MouseButton button;
			struct {
				double x, y;
			} position;
			double offset;
		};

		InputEvent(OpenGLGUI::EventType t, OpenGLGUI::Key k) : type(t), key(k) {}
		InputEvent(OpenGLGUI::EventType t, OpenGLGUI::MouseButton b) : type(t), button(b) {}
		InputEvent(OpenGLGUI::EventType t, double xPosition, double yPosition) : type(t), position({ xPosition, yPosition }) {}
		InputEvent(OpenGLGUI::EventType t, double o) : type(t), offset(o) {}
	};

	std::vector<InputEvent> inputQueue;
	int windowWidth;
	int windowHeight;

	void keyboardCallback(GLFWwindow *window, int key, int scanCode, int action, int mods)
	{
		inputQueue.emplace_back(action == GLFW_PRESS ? OpenGLGUI::EventType::KeyPressed : OpenGLGUI::EventType::KeyReleased, glfwKeyMapping[key]);
	}

	void mouseMoveCallback(GLFWwindow *window, double xPosition, double yPosition)
	{
		std::cout << "(" << xPosition << "," << windowHeight - yPosition << ")\n";
		inputQueue.emplace_back(OpenGLGUI::EventType::MouseMove, xPosition, windowHeight - yPosition);
	}
	
	void windowSizeCallback(GLFWwindow* window, int width, int height)
	{
		windowWidth = width;
		windowHeight = height;
	}

	void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
	{
		inputQueue.emplace_back(action == GLFW_PRESS ? OpenGLGUI::EventType::MouseButtonPressed : OpenGLGUI::EventType::MouseButtonReleased, glfwMouseMapping[button]);
	}

	void mouseScrollCallback(GLFWwindow *window, double xOffset, double yOffset)
	{
		inputQueue.emplace_back(OpenGLGUI::EventType::MouseWheelScroll, yOffset);
	}
}

namespace OpenGLGUI {
	namespace GLFWInputController {
		void initializeCallbacks(GLFWwindow *window) {
			glfwSetKeyCallback(window, keyboardCallback);
			glfwSetCursorPosCallback(window, mouseMoveCallback);
			glfwSetMouseButtonCallback(window, mouseButtonCallback);
			glfwSetScrollCallback(window, mouseScrollCallback);
			glfwSetWindowSizeCallback(window, windowSizeCallback); 

			glfwGetWindowSize(window, &windowWidth, &windowHeight);
		}
		void applyInputQueue(WidgetGroup &w) {
			w.setCanvasSize(windowWidth, windowHeight);
			for (InputEvent &event : inputQueue)
			{
				switch (event.type)
				{
				case EventType::KeyPressed:
					w.setKeyState(event.key, OpenGLGUI::InputState::Pressed);
					break;
				case EventType::KeyReleased:
					w.setKeyState(event.key, OpenGLGUI::InputState::Released);
					break;
				case EventType::MouseButtonPressed:
					w.setMouseState(event.button, OpenGLGUI::InputState::Pressed);
					break;
				case EventType::MouseButtonReleased:
					w.setMouseState(event.button, OpenGLGUI::InputState::Released);
					break;
				case EventType::MouseMove:
					w.setMousePosition(event.position.x, event.position.y);
					break;
				case EventType::MouseWheelScroll:
					w.setMouseWheelDelta(event.offset);
					break;
				}
			}
		}
		void clearInputQueue() {
			inputQueue.clear();
		}
	}
}