#pragma once
#include <string>
#include "Drawables\Drawable.h"
#include "Text\Font.h"
#include "Brushes/FontBrush.h"
#include "Util/Mesh.h"

namespace OpenGLGUI {
	class Text : public Drawable
	{
	private:
		std::shared_ptr<FontBrush> brush;
		std::shared_ptr<Util::InstancedMesh> mesh;
	public:
		Text(std::string& text, std::shared_ptr<FontBrush> font);
		~Text();

		void draw(glm::vec2 origin);
	};
}

