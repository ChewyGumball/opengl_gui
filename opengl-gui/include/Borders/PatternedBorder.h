#pragma once
#include "Borders/Border.h"
#include "Graphics/Pattern.h"

namespace OpenGLGUI
{
	class PatternedBorder :
		public Border
	{
	private:
		Pattern& pattern;
	public:
		PatternedBorder(Pattern& p);
		~PatternedBorder();
	};
}
