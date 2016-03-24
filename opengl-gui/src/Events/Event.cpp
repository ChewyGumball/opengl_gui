#include <functional>

#include "Events/Event.h"

namespace OpenGLGUI
{
	Event::Event(KeyboardState &kState, MouseState &mState) : propagate(true), keyboard(kState), mouse(mState)
	{}

	void Event::consume() { propagate = false; }
	bool Event::consumed() { return !propagate; }
	void Event::reset() { propagate = true; }
}
