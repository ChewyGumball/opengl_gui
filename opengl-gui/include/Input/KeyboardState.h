#pragma once
#include <unordered_map>

#include "InputState.h"

namespace OpenGLGUI
{
	class KeyboardState
	{
	private:
		std::unordered_map<Key, InputState> state;
		Key mostRecentlyChangedKey;
	public:
		KeyboardState();
		~KeyboardState();

		void setKeyState(Key key, InputState inputState);
		
		const InputState& operator[](Key key) const;
		const Key keyWithMostRecentStateChange() const;
	};
}
