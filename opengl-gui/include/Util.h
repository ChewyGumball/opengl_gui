#pragma once
#include <GL\glew.h>
#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

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
			ShaderProgram(const std::vector<std::shared_ptr<Shader>> &shaders);
			~ShaderProgram();

			bool valid() { return shaderProgramID != 0; }
			void enable() { glUseProgram(shaderProgramID); }
			void disable() { glUseProgram(0); }

			void setUniform2f(const std::string &uniformName, glm::vec2 data);
			void setUniform3f(const std::string &uniformName, glm::vec3 data);
			void setUniform4f(const std::string &uniformName, glm::vec4 data);
		private:
			GLuint shaderProgramID = 0;
		};

		class Mesh {
		private:
			int elementCount;
			bool indexed = false;
		public:
			Mesh() {}
			Mesh(const std::vector<glm::vec2> &vertexAttributes, bool interleaved = true);
			Mesh(const std::vector<glm::vec2> &vertexAttributes, const std::vector<unsigned int> &indices, bool interleaved = true);
			~Mesh();

			void bind();
			void unbind();
			void draw();
		private:
			GLuint vao = 0;
			GLuint vbo = 0;
			GLuint ebo = 0;
		};

		class Texture {
		private:
			GLuint textureID;
		public:
			Texture(std::vector<unsigned char> bytes, int width, int height, GLuint inputFormat, GLuint storageFormat);
			Texture(std::string filename, int width, int height, GLuint inputFormat, GLuint storageFormat);
			~Texture();

			bool valid() { return textureID != 0; }

			void bind(GLuint textureUnit = 0);
		};
	}
}