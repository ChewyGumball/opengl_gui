#include <string>

#include "Util.h"

#include "Brushes/SolidFillBrush.h"
namespace {
	std::string colourFragmentShaderSource = R"(
#version 330 core
uniform vec4 colour;
out vec4 colourOut;

void main()
{
    colourOut = colour;
}
	)";

	std::string colourVertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 position;

uniform vec4 offset;
uniform vec4 dimension;

void main()
{
    gl_Position = vec4((position * dimension.xyz) + offset.xyz, 1.0f) / vec4(640, 480, 1, 1);
} 
	)";

	bool initialized = false;
	OpenGLGUI::Util::Shader *colourFragmentShader;
	OpenGLGUI::Util::Shader *colourVertexShader;
	OpenGLGUI::Util::ShaderProgram *solidFillProgram;

	void initializeGLData() {
		colourFragmentShader = new OpenGLGUI::Util::Shader(colourFragmentShaderSource, GL_FRAGMENT_SHADER);
		colourVertexShader = new OpenGLGUI::Util::Shader(colourVertexShaderSource, GL_VERTEX_SHADER);
		solidFillProgram = new OpenGLGUI::Util::ShaderProgram({ colourFragmentShader, colourVertexShader });

		initialized = colourFragmentShader->valid() && colourVertexShader->valid() && solidFillProgram->valid();
		if (!initialized)
		{
			delete solidFillProgram;
			delete colourFragmentShader;
			delete colourVertexShader;
		}
	}
}

namespace OpenGLGUI {
	SolidFillBrush::SolidFillBrush() : SolidFillBrush(0,0,0)
	{
	}
	SolidFillBrush::SolidFillBrush(const SolidFillBrush & right) : SolidFillBrush(right.r, right.g, right.b)
	{
	}

	SolidFillBrush::SolidFillBrush(float red, float green, float blue) : Brush(solidFillProgram), r(red), g(green), b(blue)
	{
	}

	SolidFillBrush::~SolidFillBrush()
	{
	}

	void SolidFillBrush::activate()
	{
		shader->enable();
		setUniform4f("colour", r, g, b, 255.0f);
	}

	void SolidFillBrush::deactivate()
	{
		solidFillProgram->disable();
	}

	void SolidFillBrush::initialize()
	{
		if (!initialized)
		{
			initializeGLData();
		}
	}
}