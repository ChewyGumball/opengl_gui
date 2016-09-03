#include <GL\glew.h>
#include <Text/Font.h>

namespace OpenGLGUI {
	Font::Font(std::string filename, int size) : atlas(ftgl::texture_atlas_new(256, 256, 1)), font(texture_font_new_from_file(atlas, size, filename.c_str()))
	{
		char text[256-32];
		for (int i = 0; i < 256 - 32; i++)
		{
			text[i] = i + 32;
		}
		int missed = texture_font_load_glyphs(font, text);

		glGenTextures(1, &atlas->id);
		glBindTexture(GL_TEXTURE_2D, atlas->id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, atlas->width, atlas->height, 0, GL_RED, GL_UNSIGNED_BYTE, atlas->data);

		textureData = std::make_shared<Util::Texture>(atlas->id);
	}

	Font::~Font()
	{
		texture_font_delete(font);
		texture_atlas_delete(atlas);
	}

	ftgl::texture_glyph_t* Font::glyphOf(char * character)
	{
		return texture_font_get_glyph(font, character);
	}
}
