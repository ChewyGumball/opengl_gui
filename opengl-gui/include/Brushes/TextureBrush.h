#pragma once
#include <memory>
#include "Brushes/Brush.h"
#include "Util.h"

namespace OpenGLGUI
{
	class TextureBrush : public Brush
	{
	protected:
		std::shared_ptr<Util::Texture> texture;
	public:
		TextureBrush();
		virtual ~TextureBrush();
	};
}

