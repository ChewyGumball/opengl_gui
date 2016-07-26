#pragma once
#include "Widgets/Widget.h"

namespace OpenGLGUI
{
	class Pane :
		public Widget
	{
	public:
		Pane();
		virtual ~Pane();

		void draw();
	};
}

