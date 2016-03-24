#pragma once

namespace OpenGLGUI
{
	class NineSlice
	{
	private:
		int top, topLeft, left, bottomLeft, bottom, bottomRight, right, topRight;
	public:
		NineSlice();
		~NineSlice();
	};
}
