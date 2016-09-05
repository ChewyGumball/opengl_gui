#pragma once
#include "Widgets/Widget.h"
#include "Drawables/Text.h"

namespace OpenGLGUI
{
	class TextArea :
		public Widget
	{
	private:
		std::vector<std::pair<float, float>> cornerList;

	protected:
		std::shared_ptr<std::string> textData; 
		int fontHeight;
		std::vector<std::vector<Text>> lines;

	public:
		TextArea() {}
		TextArea(std::string data, std::shared_ptr<FontBrush> font, int width, int height) : TextArea(std::make_shared<std::string>(data), font, width, height) {};
		TextArea(std::shared_ptr<std::string> data, std::shared_ptr<FontBrush> font, int width, int height);
		virtual ~TextArea() {};

		void text(std::shared_ptr<std::string> data) { textData = data; }
		void text(std::string data) { textData = std::make_shared<std::string>(data); }
		std::string& text() { return *textData; }

		void draw(glm::vec2 origin);
	};
}
