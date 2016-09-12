#pragma once
#include <glm/vec2.hpp>

namespace OpenGLGUI
{
	struct Drawable
	{
		virtual void draw(glm::vec2 origin, glm::vec2 canvasSize) = 0;
	};
}
