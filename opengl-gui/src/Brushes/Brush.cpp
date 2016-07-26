#include "Util.h"
#include "Brushes/Brush.h"


namespace OpenGLGUI {
	void Brush::activate()
	{
		shader->enable();
	}

	void Brush::deactivate()
	{
		shader->disable();
	}

	void Brush::setUniform4f(const std::string & uniformName, float a, float b, float c, float d)
	{
		shader->setUniform4f(uniformName, a, b, c, d);
	}
}
