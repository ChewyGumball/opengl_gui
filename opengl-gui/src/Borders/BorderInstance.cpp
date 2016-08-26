#include "Borders/BorderInstance.h"

namespace OpenGLGUI
{
	BorderInstance::BorderInstance()
	{
	}
	BorderInstance::BorderInstance(std::shared_ptr<Border> definition, std::vector<glm::vec2>& corners) : borderDefinition(definition), mesh(definition->createMeshFromCorners(corners))
	{
	}

	void BorderInstance::border(std::shared_ptr<Border> border, std::vector<glm::vec2>& corners)
	{ 
		borderDefinition = border;
		mesh = borderDefinition->createMeshFromCorners(corners);
	}

	void BorderInstance::draw(glm::vec2 origin)
	{
		if (borderDefinition)
		{
			Brush& borderBrush = borderDefinition->brush();
			borderBrush.activate();
			borderBrush.setUniform2f("offset", origin);
			borderBrush.setUniform2f("dimension", glm::vec2(1, 1));
			borderBrush.setUniform2f("screenSize", glm::vec2(640, 480));
			mesh.draw();
			borderBrush.deactivate();
		}
	}
}