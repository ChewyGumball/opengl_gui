#pragma once
#include <glm/vec2.hpp>

namespace OpenGLGUI
{
	struct Drawable
	{
		virtual void draw(glm::vec2 origin) = 0;
	};
}
