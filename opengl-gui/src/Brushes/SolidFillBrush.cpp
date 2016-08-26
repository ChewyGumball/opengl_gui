#include <string>

#include "Util.h"

#include "Brushes/SolidFillBrush.h"
namespace {
	std::string colourFragmentShaderSource = R"(
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

	std::string colourVertexShaderSource = R"(
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
		fragmentShader = new OpenGLGUI::Util::Shader(colourFragmentShaderSource, GL_FRAGMENT_SHADER);
		vertexShader = new OpenGLGUI::Util::Shader(colourVertexShaderSource, GL_VERTEX_SHADER);
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
	SolidFillBrush::SolidFillBrush() : SolidFillBrush(0,0,0)
	{
	}
	SolidFillBrush::SolidFillBrush(const SolidFillBrush & right) : SolidFillBrush(right.colour)
	{
	}

	SolidFillBrush::SolidFillBrush(glm::vec4 colour) : Brush(shaderProgram), colour(colour)
	{
	}

	SolidFillBrush::SolidFillBrush(float red, float green, float blue, float alpha) : SolidFillBrush(glm::vec4(red,green,blue,alpha))
	{
	}

	SolidFillBrush::~SolidFillBrush()
	{
	}

	void SolidFillBrush::activate()
	{
		if (!initialized)
		{
			initializeGLData();
		}
		if (initialized && shader == nullptr)
		{
			shader = shaderProgram;
		}
		shader->enable();
		setUniform4f("colour", colour);
	}

	void SolidFillBrush::deactivate()
	{
		shaderProgram->disable();
	}


	namespace Brushes {
		std::shared_ptr<SolidFillBrush> Blue = std::make_shared<SolidFillBrush>(0, 0, 1);
		std::shared_ptr<SolidFillBrush> Red = std::make_shared<SolidFillBrush>(1, 0, 0);
		std::shared_ptr<SolidFillBrush> Green = std::make_shared<SolidFillBrush>(0, 1, 0);
		std::shared_ptr<SolidFillBrush> LightBlue = std::make_shared<SolidFillBrush>(0, 0.5, 0.8);
		std::shared_ptr<SolidFillBrush> LightGrey = std::make_shared<SolidFillBrush>(0.7, 0.7, 0.7);
		std::shared_ptr<SolidFillBrush> DarkGrey = std::make_shared<SolidFillBrush>(0.3, 0.3, 0.3);
		std::shared_ptr<SolidFillBrush> White = std::make_shared<SolidFillBrush>(1, 1, 1);
	}
}