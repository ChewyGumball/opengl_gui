#include "Util/Mesh.h"

namespace OpenGLGUI {
	namespace Util {

		Mesh::Mesh(const std::vector<glm::vec2> &vertexAttributes, bool interleaved) : elementCount(static_cast<int>(vertexAttributes.size()) / 2) //we have positions and texture coords in the same vector
		{
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			GLuint vbo;
			glGenBuffers(1, &vbo);

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, vertexAttributes.size() * 2 * sizeof(float), vertexAttributes.data(), GL_STATIC_DRAW);

			if (interleaved)
			{
				GLsizei elementSize = 2 * sizeof(GLfloat);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, elementSize * 2, (GLvoid*)0);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, elementSize * 2, (GLvoid*)elementSize);
			}
			else
			{
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)elementCount);
			}
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);

			glBindVertexArray(0);
		}

		Mesh::Mesh(const std::vector<glm::vec2>& vertices, const std::vector<unsigned int>& indices, bool interleaved) : indexed(true), elementCount(static_cast<int>(indices.size()))
		{
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			GLuint ebo;
			GLuint vbo;
			glGenBuffers(1, &vbo);
			glGenBuffers(1, &ebo);

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * 2 * sizeof(float), vertices.data(), GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

			if (interleaved)
			{
				GLsizei elementSize = 2 * sizeof(float);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, elementSize * 2, (GLvoid*)0);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, elementSize * 2, (GLvoid*)elementSize);
			}
			else
			{
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)elementCount);
			}
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);

			glBindVertexArray(0);
		}

		void Mesh::bind()
		{
			glBindVertexArray(vao);
		}

		void Mesh::unbind()
		{
			glBindVertexArray(0);
		}

		void Mesh::draw()
		{
			bind();
			if (indexed)
			{
				glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, 0);
			}
			else
			{
				glDrawArrays(GL_TRIANGLE_STRIP, 0, elementCount);
			}
			unbind();
		}

		InstancedMesh::InstancedMesh(const std::vector<glm::vec2>& vertices, const std::vector<std::vector<glm::vec2>> instancedAttributes, int instanceCount)
			: Mesh(static_cast<int>(vertices.size()) / 2, false), instanceCount(instanceCount)
		{
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);
			int currentAttribute = 0;

			GLuint ebo;
			GLuint vbo;
			glGenBuffers(1, &vbo);
			glGenBuffers(1, &ebo);

			//bind position/uv data
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * 2 * sizeof(float), vertices.data(), GL_STATIC_DRAW);

			GLsizei elementSize = 2 * sizeof(float);
			glVertexAttribPointer(currentAttribute, 2, GL_FLOAT, GL_FALSE, elementSize * 2, (GLvoid*)0);
			glEnableVertexAttribArray(currentAttribute++);
			glVertexAttribPointer(currentAttribute, 2, GL_FLOAT, GL_FALSE, elementSize * 2, (GLvoid*)elementSize);
			glEnableVertexAttribArray(currentAttribute++);
			
			//bind instance data
			for (auto attribute : instancedAttributes)
			{
				glGenBuffers(1, &vbo);
				glBindBuffer(GL_ARRAY_BUFFER, vbo);
				glBufferData(GL_ARRAY_BUFFER, attribute.size() * 2 * sizeof(float), attribute.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(currentAttribute, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
				glEnableVertexAttribArray(currentAttribute);
				glVertexAttribDivisor(currentAttribute++, 1);
			}

			glBindVertexArray(0);
		}

		InstancedMesh::InstancedMesh(const std::vector<glm::vec2>& vertices, const std::vector<std::vector<glm::vec2>> instancedAttributes, const std::vector<unsigned int>& indices, int instanceCount)
			: Mesh(static_cast<int>(indices.size()), true), instanceCount(instanceCount)
		{
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);
			int currentAttribute = 0;

			GLuint ebo;
			GLuint vbo;
			glGenBuffers(1, &vbo);
			glGenBuffers(1, &ebo);

			//bind position/uv data
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * 2 * sizeof(float), vertices.data(), GL_STATIC_DRAW);

			GLsizei elementSize = 2 * sizeof(float);
			glVertexAttribPointer(currentAttribute, 2, GL_FLOAT, GL_FALSE, elementSize * 2, (GLvoid*)0);
			glEnableVertexAttribArray(currentAttribute++);
			glVertexAttribPointer(currentAttribute, 2, GL_FLOAT, GL_FALSE, elementSize * 2, (GLvoid*)elementSize);
			glEnableVertexAttribArray(currentAttribute++);

			//bind index data
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

			//bind instance data
			for (auto attribute : instancedAttributes)
			{
				glGenBuffers(1, &vbo);
				glBindBuffer(GL_ARRAY_BUFFER, vbo);
				glBufferData(GL_ARRAY_BUFFER, attribute.size() * 2 * sizeof(float), attribute.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(currentAttribute, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
				glEnableVertexAttribArray(currentAttribute);
				glVertexAttribDivisor(currentAttribute++, 1);
			}

			glBindVertexArray(0);
		}

		void InstancedMesh::draw()
		{
			bind();
			if (indexed)
			{
				glDrawElementsInstanced(GL_TRIANGLES, GL_UNSIGNED_INT, elementCount, 0, instanceCount);
			}
			else
			{
				glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, elementCount, instanceCount);
			}
			unbind();
		}
	}
}