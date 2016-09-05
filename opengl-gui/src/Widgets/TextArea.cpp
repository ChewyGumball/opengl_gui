#include "Widgets/TextArea.h"

namespace {
	std::vector<std::vector<OpenGLGUI::Text>> layoutText(std::string text, std::shared_ptr<OpenGLGUI::FontBrush> fontBrush, int width, int height)
	{
		std::vector<std::vector<OpenGLGUI::Text>> lines;
		std::vector<OpenGLGUI::Text> currentLine;

		std::shared_ptr<OpenGLGUI::Font> font = fontBrush->font();

		int currentLinePosition = 0;
		int currentLineWidth = 0;
		for (int i = 0; i < text.size(); i++)
		{
			char currentChar = text[i];
			if (currentChar == '\n')
			{
				currentLine.emplace_back(text.substr(i - currentLinePosition, currentLinePosition), fontBrush);
				lines.push_back(currentLine);
				currentLine = std::vector<OpenGLGUI::Text>();
				currentLineWidth = 0;
				currentLinePosition = 0;
			}
			else
			{
				ftgl::texture_glyph_t *glyph = font->glyphOf(&currentChar);
				int currentWidth = glyph->advance_x;
				int kerning = 0;
				if (currentLinePosition != 0)
				{
					kerning = texture_glyph_get_kerning(glyph, &text[i - 1]);
				}

				//go to next line if too long
				if (currentLineWidth + currentWidth + kerning > width)
				{
					//find closest previous space character
					int previousSpaceOffset = 0;
					char previousChar = text[i - previousSpaceOffset];
					while (previousSpaceOffset < currentLinePosition && text[i - previousSpaceOffset] != ' ')
					{
						previousSpaceOffset++;
					}

					if (previousSpaceOffset == currentLinePosition)
					{
						previousSpaceOffset = 0;
					}

					currentLine.emplace_back(text.substr(i - currentLinePosition, currentLinePosition - previousSpaceOffset), fontBrush);
					lines.push_back(currentLine);
					currentLine = std::vector<OpenGLGUI::Text>();

					//start laying out again AFTER the space
					i -= previousSpaceOffset - 1;
					currentLineWidth = 0;
					currentLinePosition = 0;
					kerning = 0;
				}

				currentLineWidth += currentWidth + kerning;
				currentLinePosition++;
			}
		}

		return lines;
	}
}

namespace OpenGLGUI
{
	TextArea::TextArea(std::shared_ptr<std::string> data, std::shared_ptr<FontBrush> font, int width, int height) : Widget(0,0,width,height), textData(data), fontHeight(font->font()->height()), lines(layoutText(*data, font, widgetWidth, widgetHeight))
	{
	}
	void TextArea::draw(glm::vec2 origin)
	{
		glm::vec2 widgetOrigin = origin + widgetPosition;
		//glScissor(widgetOrigin.x, widgetOrigin.y, widgetWidth, widgetHeight);
		int lineCount = 0;
		for (auto& line : lines)
		{
			for (auto& text : line)
			{
				text.draw(widgetOrigin - glm::vec2(0, lineCount * fontHeight));
				lineCount++;
			}
		}
	}
}
