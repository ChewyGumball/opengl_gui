#pragma once
#include "Widgets/Widget.h"
#include "Drawables/Rectangle.h"

namespace OpenGLGUI
{
	class Pane :
		public Widget
	{
	private:
		std::shared_ptr<EventSubscription> dragSubscription;
		Rectangle backgroundRectangle;
	public:
		Pane();
		Pane(int offsetX, int offsetY, int width, int height);
		Pane(std::shared_ptr<Widget> parent);
		virtual ~Pane() {};

		void draw(glm::vec2 origin);
		void setDraggable(bool draggable);

		const std::shared_ptr<Brush> Pane::background() const;
		Widget& background(std::shared_ptr<Brush> background);
	};
}

