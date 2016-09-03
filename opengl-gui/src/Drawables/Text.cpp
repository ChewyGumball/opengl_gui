#include <memory>
#include "Drawables\Text.h"
#include "Util.h"
#include "Util/Mesh.h"
#include "Brushes/FontBrush.h"

namespace OpenGLGUI {
	Text::Text(std::string &text, std::shared_ptr<FontBrush> font) : brush(font)
	{
		//This rectangle will be scaled and offset for each instance of a glyph
		std::vector<glm::vec2> vertices {
			glm::vec2(0.0, 0.0), glm::vec2(0.0, 0.0),
			glm::vec2(1.0, 0.0), glm::vec2(1.0, 0.0),
			glm::vec2(0.0, 1.0), glm::vec2(0.0, 1.0),
			glm::vec2(1.0, 1.0), glm::vec2(1.0, 1.0)
		};

		std::vector<glm::vec2> penOffsets;
		std::vector<glm::vec2> glyphScales;
		std::vector<glm::vec2> atlasOffsets;
		std::vector<glm::vec2> atlasScales;

		std::shared_ptr<Font> fontData = font->font();

		glm::vec2 currentPenOffest;

		for (int i = 0; i < text.size(); i++)
		{
			char currentChar = text[i];
			ftgl::texture_glyph_t *glyph = fontData->glyphOf(&currentChar);
			if (i > 0)
			{
				currentPenOffest += glm::vec2(glyph->advance_x, 0);
			}
			penOffsets.push_back(currentPenOffest);
			glyphScales.push_back(glm::vec2(glyph->width, glyph->height));
			atlasOffsets.push_back(glm::vec2(glyph->s0, 1 - glyph->t0));
			atlasScales.push_back(glm::vec2(glyph->s1 - glyph->s0, (1 - glyph->t1) - (1 - glyph->t0)));
		}

		mesh = std::make_shared<Util::InstancedMesh>(vertices, std::vector<std::vector<glm::vec2>> {atlasOffsets, atlasScales, glyphScales, penOffsets}, text.size());
	}

	Text::~Text()
	{
	}

	void Text::draw(glm::vec2 origin)
	{
		brush->activate();
		brush->setUniform2f("offset", origin);
		brush->setUniform2f("screenSize", glm::vec2(640, 480));
		mesh->draw();
		brush->deactivate();
	}
}
