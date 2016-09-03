#pragma once
#include <memory>
#include "Brushes/Brush.h"
#include "Util.h"
#include "Text/Font.h"

namespace OpenGLGUI
{
	class FontBrush : public Brush
	{
	protected:
		std::shared_ptr<Font> fontData;
		glm::vec4 foregroundColour;
		glm::vec4 backgroundColour;

	public:
		FontBrush(std::shared_ptr<Font> font, glm::vec4 foregroundColour = glm::vec4(1,1,1,1), glm::vec4 backgroundColour = glm::vec4(0,0,0,0));
		~FontBrush() {};

		std::shared_ptr<Font> font() { return fontData; }

		void activate();
	};
}
