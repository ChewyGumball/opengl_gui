#pragma once
#include "Util.h"
#include <freetype-gl/texture-atlas.h>
#include <freetype-gl/texture-font.h>

namespace OpenGLGUI
{
	class Font
	{
	protected:
		//Currently just caches ascii characters
		std::shared_ptr<Util::Texture> textureData;
		ftgl::texture_atlas_t *atlas;
		ftgl::texture_font_t *font;
	public:
		Font(std::string filename, int size);
		~Font();
		std::shared_ptr<Util::Texture> texture() { return textureData; }

		ftgl::texture_glyph_t* glyphOf(char *character);
	};
}