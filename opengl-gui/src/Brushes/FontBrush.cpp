#include "Brushes/FontBrush.h"

namespace {

	std::string fragmentShaderSource = R"(
#version 330 core
uniform vec4 foregroundColour;
uniform vec4 backgroundColour;
uniform sampler2D tex;

in vec2 textureCoordinates;
out vec4 colourOut;

void main()
{
    
    colourOut = mix(backgroundColour, foregroundColour, texture(tex, textureCoordinates).r);
}
)";

	std::string vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec2 texCoordOffset;
layout (location = 3) in vec2 texCoordScale;
layout (location = 4) in vec2 glyphOffset;
layout (location = 5) in vec2 glyphDimensions;

uniform vec2 offset;
uniform vec2 screenSize;

out vec2 textureCoordinates;

void main()
{
	vec2 halfScreenSize = screenSize / 2;
    gl_Position = vec4((position * glyphDimensions + glyphOffset + offset - halfScreenSize) / halfScreenSize, 0, 1);
	textureCoordinates = texCoord * texCoordScale + texCoordOffset;
} 
)";

	bool initialized = false;
	std::shared_ptr<OpenGLGUI::Util::Shader> fragmentShader;
	std::shared_ptr<OpenGLGUI::Util::Shader> vertexShader;
	std::shared_ptr<OpenGLGUI::Util::ShaderProgram> shaderProgram;

	void initializeGLData() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		fragmentShader = std::make_shared<OpenGLGUI::Util::Shader>(fragmentShaderSource, GL_FRAGMENT_SHADER);
		vertexShader = std::make_shared<OpenGLGUI::Util::Shader>(vertexShaderSource, GL_VERTEX_SHADER);
		shaderProgram = std::make_shared<OpenGLGUI::Util::ShaderProgram>(std::vector<std::shared_ptr<OpenGLGUI::Util::Shader>> { fragmentShader, vertexShader });

		initialized = fragmentShader->valid() && vertexShader->valid() && shaderProgram->valid();
		if (!initialized)
		{
			shaderProgram = nullptr;
			fragmentShader = nullptr;
			vertexShader = nullptr;
		}
	}
}

namespace OpenGLGUI
{
	FontBrush::FontBrush(std::shared_ptr<Font> font, glm::vec4 foregroundColour, glm::vec4 backgroundColour) : Brush(shaderProgram), fontData(font), foregroundColour(foregroundColour), backgroundColour(backgroundColour)
	{
	}

	void FontBrush::activate()
	{
		if (!initialized)
		{
			initializeGLData();
		}
		if (initialized && shader == nullptr)
		{
			shader = shaderProgram;
		}

		Brush::activate();
		fontData->texture()->bind();
		shader->setUniform4f("foregroundColour", foregroundColour);
		shader->setUniform4f("backgroundColour", backgroundColour);

	}
}
