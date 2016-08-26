#include <string>

#include "Util.h"

#include "Brushes/SolidFillBrush.h"
#include "Util.h"
namespace {
	bool initialized = false;
	std::shared_ptr<OpenGLGUI::Util::Texture> whiteTexture = nullptr;

	void initializeGLData() {
		whiteTexture = std::make_shared<OpenGLGUI::Util::Texture>(std::vector<unsigned char> { 255, 255, 255, 255 }, 1,1, GL_RGBA, GL_RGBA);
		initialized = whiteTexture->valid();
		if (!initialized)
		{
			whiteTexture = nullptr;
		}
	}
}

namespace OpenGLGUI {
	SolidFillBrush::SolidFillBrush() : SolidFillBrush(0,0,0)
	{
	}
	SolidFillBrush::SolidFillBrush(const SolidFillBrush & right) : SolidFillBrush(right.colour)
	{
	}

	SolidFillBrush::SolidFillBrush(glm::vec4 colour) : TextureBrush(whiteTexture), colour(colour)
	{
	}

	SolidFillBrush::SolidFillBrush(float red, float green, float blue, float alpha) : SolidFillBrush(glm::vec4(red,green,blue,alpha))
	{
	}

	SolidFillBrush::~SolidFillBrush()
	{
	}

	void SolidFillBrush::activate()
	{
		if (!initialized)
		{
			initializeGLData();
		}
		if (initialized && texture == nullptr)
		{
			texture = whiteTexture;
		}

		TextureBrush::activate();
		setUniform4f("colour", colour);
	}


	namespace Brushes {
		std::shared_ptr<SolidFillBrush> Blue = std::make_shared<SolidFillBrush>(0, 0, 1);
		std::shared_ptr<SolidFillBrush> Red = std::make_shared<SolidFillBrush>(1, 0, 0);
		std::shared_ptr<SolidFillBrush> Green = std::make_shared<SolidFillBrush>(0, 1, 0);
		std::shared_ptr<SolidFillBrush> LightBlue = std::make_shared<SolidFillBrush>(0, 0.5, 0.8);
		std::shared_ptr<SolidFillBrush> LightGrey = std::make_shared<SolidFillBrush>(0.7, 0.7, 0.7);
		std::shared_ptr<SolidFillBrush> DarkGrey = std::make_shared<SolidFillBrush>(0.3, 0.3, 0.3);
		std::shared_ptr<SolidFillBrush> White = std::make_shared<SolidFillBrush>(1, 1, 1);
	}
}