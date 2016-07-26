#pragma once
#include <GL\glew.h>
#include <string>
#include <vector>

namespace OpenGLGUI {
	namespace Util {

		class Shader {
		public:
			Shader(const std::string &source, GLuint type);
			~Shader();

			bool valid() { return shaderID != 0; }

			GLuint ID() { return shaderID; }
		private:
			GLuint shaderID = 0;
		};

		class ShaderProgram {
		public:
			ShaderProgram(const std::vector<Shader*> &shaders);
			~ShaderProgram();

			bool valid() { return shaderProgramID != 0; }
			void enable() { glUseProgram(shaderProgramID); }
			void disable() { glUseProgram(0); }

			void setUniform4f(const std::string &uniformName, float a, float b, float c, float d);
		private:
			GLuint shaderProgramID = 0;
		};

		class Mesh {
		private:
			int vertexCount;
		public:
			Mesh(const std::vector<float> &vertices);
			~Mesh();

			void bind();
			void draw();
		private:
			GLuint vao = 0;
			GLuint vbo = 0;
		};
	}
}