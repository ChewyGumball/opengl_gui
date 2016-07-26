#pragma once
#include "Brushes/Brush.h"
namespace OpenGLGUI {
	class SolidFillBrush : public Brush
	{
	private:
		float r, g, b;
	public:
		SolidFillBrush();
		SolidFillBrush(const SolidFillBrush &right);
		SolidFillBrush(float red, float green, float blue);
		~SolidFillBrush();

		void activate();
		void deactivate();

		static void initialize();
	};
}

