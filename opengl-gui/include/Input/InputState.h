#pragma once
namespace OpenGLGUI
{
	enum class Key {
		Escape,				//01
		One,				//02
		Two,				//03
		Three,				//04
		Four,				//05
		Five,				//06
		Six,				//07
		Seven,				//08
		Eight,				//09
		Nine,				//0a
		Zero,				//0b
		Dash,				//0c
		Equals,				//0d
		Backspace,			//0e
		Tab,				//0f
		Q,					//10
		W,					//11
		E,
		R,
		T,
		Y,
		U,
		I,
		O,
		P,
		LeftBracket,
		RightBracket,
		Enter,
		LeftControl,
		A,
		S,
		D,
		F,
		G,
		H,
		J,
		K,
		L,
		Semicolon,
		SingleQuote,
		Backtick,
		LeftShift,
		Backslash,
		Z,
		X,
		C,
		V,
		B,
		N,
		M,
		Comma,
		Period,
		Slash,
		RightShift,
		KeypadAsterisk,
		LeftAlt,
		Space,
		CapsLock,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		NumLock,
		ScrollLock,


	};
	enum class MouseButton {
		Left,
		Right,
		Middle
	};
	enum class InputState {
		Pressed,
		Released
	};
}

namespace std {
	template <>
	struct hash<OpenGLGUI::Key>
	{
		size_t operator()(const OpenGLGUI::Key &type) const
		{
			return hash<int>()(static_cast<int>(type));
		}
	};

	template <>
	struct hash<OpenGLGUI::MouseButton>
	{
		size_t operator()(const OpenGLGUI::MouseButton &type) const
		{
			return hash<int>()(static_cast<int>(type));
		}
	};

	template <>
	struct hash<OpenGLGUI::InputState>
	{
		size_t operator()(const OpenGLGUI::InputState &type) const
		{
			return hash<int>()(static_cast<int>(type));
		}
	};
}