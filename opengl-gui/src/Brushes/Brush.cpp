#include "Util.h"
#include "Brushes/Brush.h"


namespace {
	std::string fragmentShaderSource = R"(
#version 330 core
uniform vec4 colour;
//uniform sampler2d tex;

//in textureCoordinates;
out vec4 colourOut;

void main()
{
    //colourOut = texture(tex, textureCoordinates) * colour;
	colourOut = colour;
}
)";

	std::string vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 position;
//layout (location = 1) in vec2 texCoord;

uniform vec2 offset;
uniform vec2 dimension;
uniform vec2 screenSize;

//out vec2 textureCoordinates;

void main()
{
	vec2 halfScreenSize = screenSize / 2;
    gl_Position = vec4((position * dimension + offset - halfScreenSize) / halfScreenSize, 0, 1);
	//textureCoordinates = texCoord;
} 
)";

	bool initialized = false;
	OpenGLGUI::Util::Shader *fragmentShader;
	OpenGLGUI::Util::Shader *vertexShader;
	OpenGLGUI::Util::ShaderProgram *shaderProgram = nullptr;

	void initializeGLData() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		fragmentShader = new OpenGLGUI::Util::Shader(fragmentShaderSource, GL_FRAGMENT_SHADER);
		vertexShader = new OpenGLGUI::Util::Shader(vertexShaderSource, GL_VERTEX_SHADER);
		shaderProgram = new OpenGLGUI::Util::ShaderProgram({ fragmentShader, vertexShader });

		initialized = fragmentShader->valid() && vertexShader->valid() && shaderProgram->valid();
		if (!initialized)
		{
			delete shaderProgram;
			delete fragmentShader;
			delete vertexShader;
		}
	}
}

namespace OpenGLGUI {
	Brush::Brush() : shader(shaderProgram)
	{
	}

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
