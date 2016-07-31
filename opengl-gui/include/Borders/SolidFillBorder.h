#pragma once
#include "Borders/Border.h"
namespace OpenGLGUI
{
	class SolidFillBorder : public Border
	{
	private:
	public:
		SolidFillBorder(std::shared_ptr<SolidFillBrush> brush, int pixels) : Border(brush, pixels) {}
		~SolidFillBorder();

		std::shared_ptr<Util::Mesh> createBorderMesh(std::vector<std::pair<float, float>> &corners);
	};
}
