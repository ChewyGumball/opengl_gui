#pragma once
#include <memory>

#include "Brushes/SolidFillBrush.h"
#include "Drawables/Drawable.h"

namespace OpenGLGUI
{
	class Widget;

	class Border : private std::enable_shared_from_this<Border>
	{
	private:
		std::vector<std::shared_ptr<Widget>> widgets;
		void notifyWidgetsOfChange();

	protected:
		std::shared_ptr<Brush> borderBrush;
		int borderThickness;
		int borderCornerRadius;
		
	public:
		Border(std::shared_ptr<Brush> brush = std::make_shared<SolidFillBrush>(), int thickness = 1, int cornerRadius = 0) 
			: borderBrush(brush), borderThickness(thickness), borderCornerRadius(cornerRadius) {}
		~Border() {}

		int thickness() { return borderThickness; }
		void thickness(int thickness) { borderThickness = thickness; notifyWidgetsOfChange(); }

		int cornerRadius() { return borderCornerRadius; }
		void cornerRadius(int cornerRadius) { borderCornerRadius = cornerRadius; notifyWidgetsOfChange(); }

		Brush& brush() { return *borderBrush; }
		void brush(std::shared_ptr<Brush> brush) { borderBrush = brush; };
		virtual Util::Mesh createMeshFromCorners(std::vector<glm::vec2> &corners);
	};
}
