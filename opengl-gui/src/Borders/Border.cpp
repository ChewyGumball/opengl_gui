#include "Borders/Border.h"
#include "Widgets/Widget.h"

namespace OpenGLGUI
{
	void OpenGLGUI::Border::notifyWidgetsOfChange()
	{
		for (auto widget : widgets)
		{
			widget->border(shared_from_this());
		}
	}

	Util::Mesh OpenGLGUI::Border::createMeshFromCorners(std::vector<glm::vec2>& corners)
	{
		std::vector<glm::vec2> meshVertices;
		glm::vec2 previousVertex = corners.back();
		glm::vec2 currentVertex = corners[0];
		glm::vec2 borderThicknessVec(borderThickness, borderThickness);
		for (size_t i = 0; i < corners.size(); i++)
		{
			glm::vec2 nextVertex = corners[(i + 1) % corners.size()];

			glm::vec2 slopeFromPrevious = glm::normalize(currentVertex - previousVertex);
			glm::vec2 slopeFromNext = glm::normalize(currentVertex - nextVertex);

			meshVertices.push_back(corners[i]);
			meshVertices.push_back(currentVertex + borderThicknessVec * slopeFromNext);
			meshVertices.push_back(currentVertex + borderThicknessVec * (slopeFromNext + slopeFromPrevious));
			meshVertices.push_back(currentVertex + borderThicknessVec * slopeFromPrevious);

			previousVertex = currentVertex;
			currentVertex = nextVertex;
		}

		int vertexCount = meshVertices.size();
		std::vector<unsigned int> meshIndices;
		for (size_t i = 0; i < corners.size(); i++)
		{
			unsigned int startIndex = i * 4;
			meshIndices.push_back(startIndex);
			meshIndices.push_back(startIndex + 1);
			meshIndices.push_back(startIndex + 2);

			meshIndices.push_back(startIndex);
			meshIndices.push_back(startIndex + 2);
			meshIndices.push_back(startIndex + 3);

			meshIndices.push_back(startIndex);
			meshIndices.push_back(startIndex + 3);
			meshIndices.push_back((startIndex + 4) % (vertexCount));

			meshIndices.push_back(startIndex + 3);
			meshIndices.push_back((startIndex + 5) % (vertexCount));
			meshIndices.push_back((startIndex + 4) % (vertexCount));
		}

		//add dummy texture coords
		for (size_t i = 0; i < vertexCount; i++)
		{
			meshVertices.push_back(glm::vec2());
		}

		return Util::Mesh(meshVertices, meshIndices, false);
	}
}
