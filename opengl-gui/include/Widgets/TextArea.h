#pragma once
#include "Widgets/Widget.h"

namespace OpenGLGUI
{
	class TextArea :
		public Widget
	{
	private:
		std::vector<std::pair<float, float>> cornerList;

	protected:
		std::shared_ptr<std::string> textData; 

	public:
		TextArea() : TextArea("") {};
		TextArea(std::string data) : TextArea(std::make_shared<std::string>(data)) {};
		TextArea(std::shared_ptr<std::string> data) : textData(data) {};
		virtual ~TextArea() {};

		void text(std::shared_ptr<std::string> data) { textData = data; }
		void text(std::string data) { textData = std::make_shared<std::string>(data); }
		std::string& text() { return *textData; }

		void draw(glm::vec2 origin);
	};
}
