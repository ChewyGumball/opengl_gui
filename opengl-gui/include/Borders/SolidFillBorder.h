#pragma once
#include "Borders/Border.h"
namespace OpenGLGUI
{
	class SolidFillBorder : public Border
	{
	private:
		int borderSize;
	public:
		SolidFillBorder(int pixels = 1) : borderSize(pixels) {};
		~SolidFillBorder();

		void size(int pixels) { borderSize = pixels; }
		int size() { return borderSize; }

		void draw(int height, int width);
	};
}
