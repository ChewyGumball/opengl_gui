#pragma once
#include "Brushes/Brush.h"
namespace OpenGLGUI {
	class SolidFillBrush : public Brush
	{
	private:
		float r, g, b, a;
	public:
		SolidFillBrush();
		SolidFillBrush(const SolidFillBrush &right);
		SolidFillBrush(float red, float green, float blue, float alpha = 1.0f);
		~SolidFillBrush();

		void activate();
		void deactivate();

		static void initialize();
	};
}

