#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <GL\glew.h>

namespace OpenGLGUI {
	namespace Util {
		class Mesh {
		protected:
			int elementCount;
			bool indexed = false;
			GLuint vao = 0;

			Mesh(int elementCount, bool indexed) : elementCount(elementCount), indexed(indexed) {}

		public:
			Mesh() {}
			Mesh(const std::vector<glm::vec2> &vertexAttributes, bool interleaved = true);
			Mesh(const std::vector<glm::vec2> &vertexAttributes, const std::vector<unsigned int> &indices, bool interleaved = true);
			virtual ~Mesh() {};

			void bind();
			void unbind();
			virtual void draw();
		};

		class InstancedMesh : public Mesh {
		protected:
			int instanceCount;
		public:
			InstancedMesh(const std::vector<glm::vec2> &vertices, const std::vector<std::vector<glm::vec2>> instancedAttributes, int instanceCount);
			InstancedMesh(const std::vector<glm::vec2> &vertices, const std::vector<std::vector<glm::vec2>> instancedAttributes, const std::vector<unsigned int> &indices, int instanceCount);
			~InstancedMesh() {};

			void draw();
		};
	}
}