#include <GL/glew.h>
#include <array>
#include "Widgets/Pane.h"
#include "Util.h"

namespace {
	using OpenGLGUI::Util::Mesh;

	bool initialized = false;
	Mesh *paneMesh;

	void initializeGLData() {
		paneMesh = new Mesh({
			0.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			1.0, 1.0, 0.0,
			1.0, 0.0, 0.0
		});
		initialized = true;
	}
}


namespace OpenGLGUI
{
	Pane::Pane()
	{
		widgetPositionX = 0;
		widgetPositionY = 0;
		widgetWidth = 100;
		widgetHeight = 100;
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
		backgroundDefinition->setUniform4f("offset", widgetPositionX, widgetPositionY, 0);
		backgroundDefinition->setUniform4f("dimension", widgetWidth, widgetHeight, 1, 1);
		paneMesh->draw();
		backgroundDefinition->deactivate();
	}
}
