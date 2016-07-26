#pragma once
#include <string>
#include <Util.h>

namespace OpenGLGUI {
	class Util::ShaderProgram;
	class Brush
	{
	protected:
		Util::ShaderProgram *shader;
		Brush(Util::ShaderProgram *shaderProgram) : shader(shaderProgram) {}
	public:
		Brush() {};
		virtual ~Brush() {};

		virtual void activate();
		virtual void deactivate();

		void setUniform4f(const std::string& uniformName, float a = 0.0f, float b = 0.0f, float c = 0.0f, float d = 0.0f);
	};
}
