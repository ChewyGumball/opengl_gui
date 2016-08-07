#pragma once
#include "Widgets/Widget.h"

namespace OpenGLGUI
{
	class Pane :
		public Widget
	{
	private:
		std::vector<std::pair<float, float>> cornerList;
		std::shared_ptr<EventSubscription> dragSubscription;
		void makeCorners();
	protected:
		std::vector<std::pair<float, float>>& corners();
	public:
		Pane();
		Pane(int offsetX, int offsetY, int width, int height);
		Pane(std::shared_ptr<Widget> parent);
		virtual ~Pane() {};

		void draw(int originX, int originY);
		void setDraggable(bool draggable);
	};
}

