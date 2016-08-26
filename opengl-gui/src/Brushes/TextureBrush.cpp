#include "Brushes/TextureBrush.h"

namespace {
	std::string fragmentShaderSource = R"(
#version 330 core
uniform vec4 colour;
uniform sampler2D tex;

in vec2 textureCoordinates;
out vec4 colourOut;

void main()
{
    colourOut = texture(tex, textureCoordinates) * colour;
}
)";

	std::string vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;

uniform vec2 offset;
uniform vec2 dimension;
uniform vec2 screenSize;

out vec2 textureCoordinates;

void main()
{
	vec2 halfScreenSize = screenSize / 2;
    gl_Position = vec4((position * dimension + offset - halfScreenSize) / halfScreenSize, 0, 1);
	textureCoordinates = texCoord;
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
	TextureBrush::TextureBrush(std::shared_ptr<Util::Texture> texture) : Brush(shaderProgram), texture(texture)
	{ }

	void TextureBrush::activate()
	{
		if (!initialized)
		{
			initializeGLData();
		}
		if (initialized && shader == nullptr)
		{
			shader = shaderProgram;
		}

		texture->bind();

		Brush::activate();
	}
}
