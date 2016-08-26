#pragma once
#include <memory>
#include "Brushes/Brush.h"
namespace OpenGLGUI {
	class SolidFillBrush : public Brush
	{
	private:
		glm::vec4 colour;
	public:
		SolidFillBrush();
		SolidFillBrush(const SolidFillBrush &right);
		SolidFillBrush(glm::vec4 colour);
		SolidFillBrush(float red, float green, float blue, float alpha = 1.0f);
		~SolidFillBrush();

		void activate();
		void deactivate();
	};

	namespace Brushes {
		extern std::shared_ptr<SolidFillBrush> Blue;
		extern std::shared_ptr<SolidFillBrush> Red;
		extern std::shared_ptr<SolidFillBrush> Green;
		extern std::shared_ptr<SolidFillBrush> LightBlue;
		extern std::shared_ptr<SolidFillBrush> LightGrey;
		extern std::shared_ptr<SolidFillBrush> DarkGrey;
		extern std::shared_ptr<SolidFillBrush> White;
	}
}

