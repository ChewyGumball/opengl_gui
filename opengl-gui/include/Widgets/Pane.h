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
	protected:
		std::vector<std::pair<float, float>>& corners();
	public:
		Pane();
		virtual ~Pane();

		void draw();
		void setDraggable(bool draggable);
	};
}

