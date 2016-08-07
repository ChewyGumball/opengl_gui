#include "Borders/SolidFillBorder.h"

#include <utility>
#include <math.h>

namespace {
	void pushVertex(std::vector<float> &vertices, float x, float y)
	{
		vertices.push_back(x);
		vertices.push_back(y);
	}

	std::pair<float, float> normalizeSlope(std::pair<float, float> a, std::pair<float, float> b)
	{
		float x = a.first - b.first;
		float y = a.second - b.second;

		float length = std::sqrtf(x * x + y * y);

		return std::make_pair(x / length, y / length);
	}
}

namespace OpenGLGUI
{
	SolidFillBorder::~SolidFillBorder()
	{
	}

	std::shared_ptr<Util::Mesh> SolidFillBorder::createBorderMesh(std::vector<std::pair<float, float>>& corners)
	{
		std::vector<float> meshVertices;
		std::pair<float, float> previousVertex = corners.back();
		std::pair<float, float> currentVertex = corners[0];
		for (size_t i = 0; i < corners.size(); i++)
		{
			std::pair<float, float> nextVertex = corners[(i + 1) % corners.size()];

			std::pair<float, float> slopeFromPrevious = normalizeSlope(currentVertex, previousVertex);
			std::pair<float, float> slopeFromNext = normalizeSlope(currentVertex, nextVertex);

			pushVertex(meshVertices, corners[i].first, corners[i].second);
			pushVertex(meshVertices, currentVertex.first + borderThickness * slopeFromNext.first, currentVertex.second + borderThickness * slopeFromNext.second);
			pushVertex(meshVertices, currentVertex.first + borderThickness * (slopeFromPrevious.first + slopeFromNext.first), currentVertex.second + borderThickness * (slopeFromPrevious.second + slopeFromNext.second));
			pushVertex(meshVertices, currentVertex.first + borderThickness * slopeFromPrevious.first, currentVertex.second + borderThickness * slopeFromPrevious.second);

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
			meshIndices.push_back((startIndex + 4) % (vertexCount / 2));

			meshIndices.push_back(startIndex + 3);
			meshIndices.push_back((startIndex + 5) % (vertexCount / 2));
			meshIndices.push_back((startIndex + 4) % (vertexCount / 2));
		}

		return std::make_shared<Util::Mesh>(meshVertices, meshIndices);
	}
}
