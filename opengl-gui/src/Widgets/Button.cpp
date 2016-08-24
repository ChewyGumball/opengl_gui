#include "Widgets/Button.h"
#include "Widgets/TextArea.h"
#include <memory>


namespace OpenGLGUI
{
	Button::Button(int width, int height) : Button(width, height, std::string(""))
	{}

	Button::Button() : Button(0,0)
	{}

	Button::Button(std::string & text) : Button(std::make_shared<TextArea>(text)) 
	{}

	Button::Button(int width, int height, std::string & text) : Button(width, height, std::make_shared<TextArea>(text))
	{}

	Button::Button(int width, int height, std::shared_ptr<Widget> contents) : pane(std::make_shared<Pane>(0, 0, width, height)), contents(contents)
	{}

	Button::Button(std::shared_ptr<Widget> contents) : Button(contents->width(), contents->height(), contents)
	{}


	Button::~Button()
	{
	}
}
