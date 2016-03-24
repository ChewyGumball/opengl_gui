#include "Input/KeyboardState.h"

#include "Input/InputState.h"

namespace OpenGLGUI
{
	KeyboardState::KeyboardState() : mostRecentlyChangedKey(Key::Enter)
	{
		state[Key::Escape] = InputState::Released;
		state[Key::One] = InputState::Released;
		state[Key::Two] = InputState::Released;
		state[Key::Three] = InputState::Released;
		state[Key::Four] = InputState::Released;
		state[Key::Five] = InputState::Released;
		state[Key::Six] = InputState::Released;
		state[Key::Seven] = InputState::Released;
		state[Key::Eight] = InputState::Released;
		state[Key::Nine] = InputState::Released;
		state[Key::Zero] = InputState::Released;
		state[Key::Dash] = InputState::Released;
		state[Key::Equals] = InputState::Released;
		state[Key::Backspace] = InputState::Released;
		state[Key::Tab] = InputState::Released;
		state[Key::Q] = InputState::Released;
		state[Key::W] = InputState::Released;
		state[Key::E] = InputState::Released;
		state[Key::R] = InputState::Released;
		state[Key::T] = InputState::Released;
		state[Key::Y] = InputState::Released;
		state[Key::U] = InputState::Released;
		state[Key::I] = InputState::Released;
		state[Key::O] = InputState::Released;
		state[Key::P] = InputState::Released;
		state[Key::LeftBracket] = InputState::Released;
		state[Key::RightBracket] = InputState::Released;
		state[Key::Enter] = InputState::Released;
		state[Key::LeftControl] = InputState::Released;
		state[Key::A] = InputState::Released;
		state[Key::S] = InputState::Released;
		state[Key::D] = InputState::Released;
		state[Key::F] = InputState::Released;
		state[Key::G] = InputState::Released;
		state[Key::H] = InputState::Released;
		state[Key::J] = InputState::Released;
		state[Key::K] = InputState::Released;
		state[Key::L] = InputState::Released;
		state[Key::Semicolon] = InputState::Released;
		state[Key::SingleQuote] = InputState::Released;
		state[Key::Backtick] = InputState::Released;
		state[Key::LeftShift] = InputState::Released;
		state[Key::Backslash] = InputState::Released;
		state[Key::Z] = InputState::Released;
		state[Key::X] = InputState::Released;
		state[Key::C] = InputState::Released;
		state[Key::V] = InputState::Released;
		state[Key::B] = InputState::Released;
		state[Key::N] = InputState::Released;
		state[Key::M] = InputState::Released;
		state[Key::Comma] = InputState::Released;
		state[Key::Period] = InputState::Released;
		state[Key::Slash] = InputState::Released;
		state[Key::RightShift] = InputState::Released;
		state[Key::KeypadAsterisk] = InputState::Released;
		state[Key::LeftAlt] = InputState::Released;
		state[Key::Space] = InputState::Released;
		state[Key::CapsLock] = InputState::Released;
		state[Key::F1] = InputState::Released;
		state[Key::F2] = InputState::Released;
		state[Key::F3] = InputState::Released;
		state[Key::F4] = InputState::Released;
		state[Key::F5] = InputState::Released;
		state[Key::F6] = InputState::Released;
		state[Key::F7] = InputState::Released;
		state[Key::F8] = InputState::Released;
		state[Key::F9] = InputState::Released;
		state[Key::F10] = InputState::Released;
		state[Key::NumLock] = InputState::Released;
		state[Key::ScrollLock] = InputState::Released;
	}

	KeyboardState::~KeyboardState()
	{
	}

	void KeyboardState::setKeyState(const Key key, const InputState inputState)
	{
		state[key] = inputState;
		mostRecentlyChangedKey = key;
	}
	
	void KeyboardState::clear()
	{
		for (auto key = state.begin(); key != state.end(); key++)
		{
			key->second = InputState::Released;
		}
		mostRecentlyChangedKey = Key::Enter;
	}

	const InputState& KeyboardState::operator[](const Key key) const
	{
		return state.find(key)->second;
	}
	const Key& KeyboardState::keyWithMostRecentStateChange() const
	{
		return mostRecentlyChangedKey;
	}
}
