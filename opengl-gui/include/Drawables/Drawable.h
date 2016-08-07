#pragma once

namespace OpenGLGUI
{
	struct Drawable
	{
		virtual void draw(int originX, int originY) = 0;
	};
}
