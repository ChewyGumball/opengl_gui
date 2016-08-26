#pragma once
#include "Drawables/Drawable.h"
#include <memory>
#include <Brushes/Brush.h>
#include <Brushes/SolidFillBrush.h>

namespace OpenGLGUI
{
	class Rectangle : public Drawable
	{
	private:
		int height, width;
		std::shared_ptr<Brush> brush;
	public:
		Rectangle(int width, int height, std::shared_ptr<Brush> brush = Brushes::White);
		~Rectangle();

		void setBrush(std::shared_ptr<Brush> brush);

		void draw(glm::vec2 origin);
	};
}