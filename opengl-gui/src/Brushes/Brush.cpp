#include "Util.h"
#include "Brushes/Brush.h"

namespace OpenGLGUI {

	Brush::~Brush()
	{
	}

	void Brush::activate()
	{
		shader->enable();
	}

	void Brush::deactivate()
	{
		shader->disable();
	}

	void Brush::setUniform2f(const std::string & uniformName, glm::vec2 data)
	{
		shader->setUniform2f(uniformName, data);
	}
	void Brush::setUniform3f(const std::string & uniformName, glm::vec3 data)
	{
		shader->setUniform3f(uniformName, data);
	}
	void Brush::setUniform4f(const std::string & uniformName, glm::vec4 data)
	{
		shader->setUniform4f(uniformName, data);
	}
}
