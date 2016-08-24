#pragma once
#include "Widgets/Widget.h"
#include "Widgets/Pane.h"

namespace OpenGLGUI
{
	class Button : public Widget
	{
	private:
		std::shared_ptr<Pane> pane;
		std::shared_ptr<Widget> contents;
	public:
		Button();
		Button(std::string &text);
		Button(std::shared_ptr<Widget> contents);
		Button(int width, int height);
		Button(int width, int height, std::string &text);
		Button(int width, int height, std::shared_ptr<Widget> contents);
		virtual ~Button();

		/* Widget Border Functions */
		std::shared_ptr<Border> border() const { return pane->border(); }
		Widget& border(std::shared_ptr<Border> border) { pane->border(border); }

		/* Widget Background Functions */
		std::shared_ptr<Brush> background() const { pane->background(); }
		Widget& background(std::shared_ptr<Brush> background) { pane->background(background); }
	};
}
