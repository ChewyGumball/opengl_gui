#pragma once
#include <memory>

#include "Drawables/Drawable.h"
#include "Borders/Border.h"

namespace OpenGLGUI
{
	class BorderInstance : public Drawable
	{
	private:
		std::shared_ptr<Border> borderDefinition;
		Util::Mesh mesh;
	public:
		BorderInstance();
		BorderInstance(std::shared_ptr<Border> definition, std::vector<glm::vec2> &corners);
		~BorderInstance() {}

		std::shared_ptr<Border> border() const { return borderDefinition; }
		void border(std::shared_ptr<Border> border, std::vector<glm::vec2>& corners);
		
		void draw(glm::vec2 origin);
	};
}