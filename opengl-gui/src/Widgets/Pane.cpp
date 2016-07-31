#include <GL/glew.h>
#include <array>
#include "Widgets/Pane.h"
#include "Util.h"

#include "Brushes/Brush.h"
#include "Borders/Border.h"

namespace {
	using OpenGLGUI::Util::Mesh;

	bool initialized = false;
	Mesh *paneMesh;

	void initializeGLData() {
		paneMesh = new Mesh({
			0.0, 0.0, 0.0,
			1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			1.0, 1.0, 0.0
		});
		initialized = true;
	}
}


namespace OpenGLGUI
{
	std::vector<std::pair<float, float>>& Pane::corners()
	{
		return cornerList;
	}
	Pane::Pane()
	{
		widgetPositionX = 0;
		widgetPositionY = 0;
		widgetWidth = 150;
		widgetHeight = 100; 
		cornerList = {
			std::make_pair(widgetPositionX, widgetPositionY),
				std::make_pair(widgetPositionX + widgetWidth, widgetPositionY),
				std::make_pair(widgetPositionX + widgetWidth, widgetPositionY + widgetHeight),
				std::make_pair(widgetPositionX, widgetPositionY + widgetHeight)
		};
	}

	Pane::~Pane()
	{
	}
	
	void OpenGLGUI::Pane::draw()
	{		
		if (!initialized)
		{
			initializeGLData();
		}
		backgroundDefinition->activate();
		backgroundDefinition->setUniform4f("offset", widgetPositionX, widgetPositionY);
		backgroundDefinition->setUniform4f("dimension", widgetWidth, widgetHeight, 1, 1);
		paneMesh->draw();
		backgroundDefinition->deactivate();

		borderDefinition->brush().activate();
		borderDefinition->brush().setUniform4f("offset");
		borderDefinition->brush().setUniform4f("dimension", 1, 1, 1, 1);
		borderMesh->draw();
		borderDefinition->brush().deactivate();
	}
}
