#pragma once
#include <string>
#include <Util.h>

namespace OpenGLGUI {
	class Brush
	{
	protected:
		std::shared_ptr<Util::ShaderProgram> shader;

	public:
		Brush(std::shared_ptr<Util::ShaderProgram> shaderProgram) : shader(shaderProgram) {}
		virtual ~Brush();

		virtual void activate();
		virtual void deactivate();

		void setUniform2f(const std::string& uniformName, glm::vec2 data);
		void setUniform3f(const std::string& uniformName, glm::vec3 data);
		void setUniform4f(const std::string& uniformName, glm::vec4 data);
	};
}
