#pragma once
#include "Borders/Border.h"
#include "Graphics/NineSlice.h"

namespace OpenGLGUI
{
	class NineSliceBorder :
		public Border
	{

	private:
		NineSlice& nineSlice;
	public:
		NineSliceBorder(NineSlice& border);
		~NineSliceBorder();
	};
}
