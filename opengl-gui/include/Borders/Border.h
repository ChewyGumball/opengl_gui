#pragma once
#include <memory>

#include "Brushes/SolidFillBrush.h"

namespace OpenGLGUI
{
	class Border
	{
	protected:
		std::shared_ptr<Brush> borderBrush;
		int borderThickness;
		int borderCornerRadius;

	public:
		Border(std::shared_ptr<Brush> brush = std::make_shared<SolidFillBrush>(), int thickness = 1, int cornerRadius = 0) 
			: borderBrush(brush), borderThickness(thickness), borderCornerRadius(cornerRadius) {}
		~Border() {}

		int thickness() { return borderThickness; }
		void thickness(int thickness) { borderThickness = thickness; }

		int cornerRadius() { return borderCornerRadius; }
		void cornerRadius(int cornerRadius) { borderCornerRadius = cornerRadius; }

		Brush& brush() { return *borderBrush; }
		void brush(std::shared_ptr<Brush> brush) { borderBrush = brush; };

		virtual std::shared_ptr<Util::Mesh> createBorderMesh(std::vector<std::pair<float, float>> &corners) = 0;
	};
}
