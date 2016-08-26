#pragma once
#include "Widgets/Widget.h"
#include "Widgets/Pane.h"

namespace OpenGLGUI
{
	class Button : public Widget
	{
	private:
		Rectangle backgroundRectangle;
		std::shared_ptr<Widget> contents;
	public:
		Button();
		Button(std::string &text);
		Button(std::shared_ptr<Widget> contents);
		Button(int width, int height);
		Button(int width, int height, std::string &text);
		Button(int width, int height, std::shared_ptr<Widget> contents);
		virtual ~Button();
		
		/* Widget Background Functions */
		const std::shared_ptr<Brush> background() const { return backgroundDefinition; }
		Widget& background(std::shared_ptr<Brush> background) { backgroundRectangle.setBrush(background); return *this; }
	};
}
