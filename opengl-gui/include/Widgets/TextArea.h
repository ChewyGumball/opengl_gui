#pragma once
#include "Widgets/Widget.h"

namespace OpenGLGUI
{
	class TextArea :
		public Widget
	{
	public:
		TextArea();
		TextArea(std::string &text);
		virtual ~TextArea();
	};
}
