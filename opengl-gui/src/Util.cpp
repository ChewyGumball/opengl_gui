#include <string>
#include <vector>
#include <iostream>
#include <memory>

#include "Util.h"

namespace OpenGLGUI::Util {
	Shader::Shader(const std::string &source, GLuint shaderType)
	{
		shaderID = glCreateShader(shaderType);

		const GLchar *shaderSource = source.c_str();
		glShaderSource(shaderID, 1, &shaderSource, 0);
		glCompileShader(shaderID);

		GLint isCompiled = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);

			//Don't leave garbage
			glDeleteShader(shaderID);

			//print out the error
			std::cout << std::string(infoLog.begin(), infoLog.end());

			//In this simple program, we'll just leave
			shaderID = 0;
		}
	}

	Shader::~Shader() {
		if (shaderID != 0) {
			glDeleteShader(shaderID);
		}
	}

	ShaderProgram::ShaderProgram(const std::vector<std::shared_ptr<Shader>> &shaders)
	{
		shaderProgramID = glCreateProgram();
		for (std::shared_ptr<Shader> s : shaders)
		{
			glAttachShader(shaderProgramID, s->ID());
		}
		glLinkProgram(shaderProgramID);

		GLint isLinked = 0;
		glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &isLinked);
		if (!isLinked) {
			GLint maxLength = 0;
			glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(shaderProgramID, maxLength, &maxLength, &infoLog[0]);

			//Don't leave garbage
			glDeleteProgram(shaderProgramID);

			//print out the error
			std::cout << std::string(infoLog.begin(), infoLog.end());

			//In this simple program, we'll just leave
			shaderProgramID = 0;
		}
	}

	ShaderProgram::~ShaderProgram() {
		if (shaderProgramID != 0) {
			glDeleteProgram(shaderProgramID);
		}
	}

	void ShaderProgram::setUniform2f(const std::string &uniformName, glm::vec2 data)
	{
		GLint location = glGetUniformLocation(shaderProgramID, uniformName.c_str());
		if (location == -1)
		{
			std::cout << "Could not find uniform '" << uniformName << "' in shader!" << std::endl;
			return;
		}
		glUniform2f(location, data.x, data.y);
	}

	void ShaderProgram::setUniform3f(const std::string &uniformName, glm::vec3 data)
	{
		GLint location = glGetUniformLocation(shaderProgramID, uniformName.c_str());
		if (location == -1)
		{
			std::cout << "Could not find uniform '" << uniformName << "' in shader!" << std::endl;
			return;
		}
		glUniform3f(location, data.x, data.y, data.z);
	}

	void ShaderProgram::setUniform4f(const std::string &uniformName, glm::vec4 data)
	{
		GLint location = glGetUniformLocation(shaderProgramID, uniformName.c_str());
		if (location == -1)
		{
			std::cout << "Could not find uniform '" << uniformName << "' in shader!" << std::endl;
			return;
		}
		glUniform4f(location, data.x, data.y, data.z, data.w);
	}


	Texture::Texture(std::vector<unsigned char> bytes, int width, int height, GLuint inputFormat, GLuint storageFormat)
	{
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		//Load image data
		glTexImage2D(GL_TEXTURE_2D, 0, inputFormat, width, height, 0, storageFormat, GL_UNSIGNED_BYTE, bytes.data());

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::Texture(std::string filename, int width, int height, GLuint inputFormat, GLuint storageFormat)
	{
		//Read image data
		const unsigned char *imageData;

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		//Load image data
		glTexImage2D(GL_TEXTURE_2D, 0, inputFormat, width, height, 0, storageFormat, GL_UNSIGNED_BYTE, imageData);

		glBindTexture(GL_TEXTURE_2D, 0);

		//delete image data
	}

	Util::Texture::~Texture()
	{
		glDeleteTextures(1, &textureID);
	}

	void Util::Texture::bind(GLuint textureUnit)
	{
		glActiveTexture(textureUnit);	// Activate the texture unit first before binding texture
		glBindTexture(GL_TEXTURE_2D, textureID);
	}
}
