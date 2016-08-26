#include "Drawables\Rectangle.h"

namespace {
	using OpenGLGUI::Util::Mesh;

	bool initialized = false;
	Mesh *rectangleMesh;

	void initializeGLData() {
		rectangleMesh = new Mesh({
			glm::vec2(0.0, 0.0),
			glm::vec2(1.0, 0.0),
			glm::vec2(0.0, 1.0),
			glm::vec2(1.0, 1.0)
		});
		initialized = true;
	}
}

namespace OpenGLGUI
{
	Rectangle::Rectangle(int width, int height, std::shared_ptr<Brush> brush) : width(width), height(height), brush(brush)
	{ }
	Rectangle::~Rectangle()
	{ }

	void Rectangle::setBrush(std::shared_ptr<Brush> brush)
	{
		this->brush = brush;
	}

	void Rectangle::draw(glm::vec2 origin)
	{
		if (!initialized)
		{
			initializeGLData();
		}
		brush->activate();
		brush->setUniform2f("offset", origin);
		brush->setUniform2f("dimension", glm::vec2(width, height));
		brush->setUniform2f("screenSize", glm::vec2(640, 480));
		rectangleMesh->draw();
		brush->deactivate();
	}
}
