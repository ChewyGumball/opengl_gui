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
layout (location = 0) in vec2 position;

uniform vec2 offset;
uniform vec2 dimension;
uniform vec2 screenSize;

void main()
{
	vec2 halfScreenSize = screenSize / 2;
    gl_Position = vec4((position * dimension + offset - halfScreenSize) / halfScreenSize, 0, 1);
} 
	)";

	bool initialized = false;
	OpenGLGUI::Util::Shader *colourFragmentShader;
	OpenGLGUI::Util::Shader *colourVertexShader;
	OpenGLGUI::Util::ShaderProgram *solidFillProgram = nullptr;

	void initializeGLData() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
	SolidFillBrush::SolidFillBrush(const SolidFillBrush & right) : SolidFillBrush(right.r, right.g, right.b, right.a)
	{
	}

	SolidFillBrush::SolidFillBrush(float red, float green, float blue, float alpha) : Brush(solidFillProgram), r(red), g(green), b(blue), a(alpha)
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
			shader = solidFillProgram;
		}
		shader->enable();
		setUniform4f("colour", r, g, b, a);
	}

	void SolidFillBrush::deactivate()
	{
		solidFillProgram->disable();
	}


	namespace Brushes {
		std::shared_ptr<SolidFillBrush> Blue = std::make_shared<SolidFillBrush>(0, 0, 1);
		std::shared_ptr<SolidFillBrush> Red = std::make_shared<SolidFillBrush>(1, 0, 0);
		std::shared_ptr<SolidFillBrush> Green = std::make_shared<SolidFillBrush>(0, 1, 0);
		std::shared_ptr<SolidFillBrush> LightBlue = std::make_shared<SolidFillBrush>(0, 0.5, 0.8);
		std::shared_ptr<SolidFillBrush> LightGrey = std::make_shared<SolidFillBrush>(0.7, 0.7, 0.7);
		std::shared_ptr<SolidFillBrush> DarkGrey = std::make_shared<SolidFillBrush>(0.3, 0.3, 0.3);
	}
}