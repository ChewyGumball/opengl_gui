#include <string>
#include <vector>
#include <iostream>

#include "Util.h"

OpenGLGUI::Util::Shader::Shader(const std::string &source, GLuint shaderType)
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

OpenGLGUI::Util::Shader::~Shader() {
	if (shaderID != 0) {
		glDeleteShader(shaderID);
	}
}

OpenGLGUI::Util::ShaderProgram::ShaderProgram(const std::vector<Shader*> &shaders)
{
	shaderProgramID = glCreateProgram();
	for (Shader *s : shaders)
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

OpenGLGUI::Util::ShaderProgram::~ShaderProgram() {
	if (shaderProgramID != 0) {
		glDeleteProgram(shaderProgramID);
	}
}

void OpenGLGUI::Util::ShaderProgram::setUniform4f(const std::string &uniformName, float a, float b, float c, float d)
{
	GLint location = glGetUniformLocation(shaderProgramID, uniformName.c_str());
	if (location == -1)
	{
		std::cout << "Could not find uniform '" << uniformName << "' in shader!" << std::endl;
		return;
	}
	glUniform4f(location, a, b, c, d);
}

OpenGLGUI::Util::Mesh::Mesh(const std::vector<float> &vertices)
{
	vertexCount = vertices.size();
	glGenBuffers(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
}

OpenGLGUI::Util::Mesh::~Mesh() {}

void OpenGLGUI::Util::Mesh::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void OpenGLGUI::Util::Mesh::draw()
{
	bind();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexCount);
}