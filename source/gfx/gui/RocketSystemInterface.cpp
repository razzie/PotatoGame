/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/gui/RocketSystemInterface.hpp"

Rocket::Core::Input::KeyIdentifier gfx::gui::RocketSystemInterface::translateKey(GL::Key::key_t key) const
{
	switch (key)
	{
	case GL::Key::Unknown:
		return Rocket::Core::Input::KI_UNKNOWN;

	case GL::Key::F1:
		return Rocket::Core::Input::KI_F1;

	case GL::Key::F2:
		return Rocket::Core::Input::KI_F2;

	case GL::Key::F3:
		return Rocket::Core::Input::KI_F3;

	case GL::Key::F4:
		return Rocket::Core::Input::KI_F4;

	case GL::Key::F5:
		return Rocket::Core::Input::KI_F5;

	case GL::Key::F6:
		return Rocket::Core::Input::KI_F6;

	case GL::Key::F7:
		return Rocket::Core::Input::KI_F7;

	case GL::Key::F8:
		return Rocket::Core::Input::KI_F8;

	case GL::Key::F9:
		return Rocket::Core::Input::KI_F9;

	case GL::Key::F10:
		return Rocket::Core::Input::KI_F10;

	case GL::Key::F11:
		return Rocket::Core::Input::KI_F11;

	case GL::Key::F12:
		return Rocket::Core::Input::KI_F12;

	case GL::Key::A:
		return Rocket::Core::Input::KI_A;

	case GL::Key::B:
		return Rocket::Core::Input::KI_B;

	case GL::Key::C:
		return Rocket::Core::Input::KI_C;

	case GL::Key::D:
		return Rocket::Core::Input::KI_D;

	case GL::Key::E:
		return Rocket::Core::Input::KI_E;

	case GL::Key::F:
		return Rocket::Core::Input::KI_F;

	case GL::Key::G:
		return Rocket::Core::Input::KI_G;

	case GL::Key::H:
		return Rocket::Core::Input::KI_H;

	case GL::Key::I:
		return Rocket::Core::Input::KI_I;

	case GL::Key::J:
		return Rocket::Core::Input::KI_J;

	case GL::Key::K:
		return Rocket::Core::Input::KI_K;

	case GL::Key::L:
		return Rocket::Core::Input::KI_L;

	case GL::Key::M:
		return Rocket::Core::Input::KI_M;

	case GL::Key::N:
		return Rocket::Core::Input::KI_N;

	case GL::Key::O:
		return Rocket::Core::Input::KI_O;

	case GL::Key::P:
		return Rocket::Core::Input::KI_P;

	case GL::Key::Q:
		return Rocket::Core::Input::KI_Q;

	case GL::Key::R:
		return Rocket::Core::Input::KI_R;

	case GL::Key::S:
		return Rocket::Core::Input::KI_S;

	case GL::Key::T:
		return Rocket::Core::Input::KI_T;

	case GL::Key::U:
		return Rocket::Core::Input::KI_U;

	case GL::Key::V:
		return Rocket::Core::Input::KI_V;

	case GL::Key::W:
		return Rocket::Core::Input::KI_W;

	case GL::Key::X:
		return Rocket::Core::Input::KI_X;

	case GL::Key::Y:
		return Rocket::Core::Input::KI_Y;

	case GL::Key::Z:
		return Rocket::Core::Input::KI_Z;

	case GL::Key::Num0:
		return Rocket::Core::Input::KI_0;

	case GL::Key::Num1:
		return Rocket::Core::Input::KI_1;

	case GL::Key::Num2:
		return Rocket::Core::Input::KI_2;

	case GL::Key::Num3:
		return Rocket::Core::Input::KI_3;

	case GL::Key::Num4:
		return Rocket::Core::Input::KI_4;

	case GL::Key::Num5:
		return Rocket::Core::Input::KI_5;

	case GL::Key::Num6:
		return Rocket::Core::Input::KI_6;

	case GL::Key::Num7:
		return Rocket::Core::Input::KI_7;

	case GL::Key::Num8:
		return Rocket::Core::Input::KI_8;

	case GL::Key::Num9:
		return Rocket::Core::Input::KI_9;

	case GL::Key::LeftBracket:
		return Rocket::Core::Input::KI_OEM_4;

	case GL::Key::RightBracket:
		return Rocket::Core::Input::KI_OEM_6;

	case GL::Key::Semicolon:
		return Rocket::Core::Input::KI_OEM_1;

	case GL::Key::Comma:
		return Rocket::Core::Input::KI_OEM_COMMA;

	case GL::Key::Period:
		return Rocket::Core::Input::KI_OEM_PERIOD;

	case GL::Key::Quote:
		return Rocket::Core::Input::KI_OEM_7;

	case GL::Key::Slash:
		return Rocket::Core::Input::KI_OEM_2;

	case GL::Key::Backslash:
		return Rocket::Core::Input::KI_OEM_5;

	case GL::Key::Tilde:
		return Rocket::Core::Input::KI_OEM_3;

	case GL::Key::Equals:
		return Rocket::Core::Input::KI_OEM_PLUS;

	case GL::Key::Hyphen:
		return Rocket::Core::Input::KI_OEM_MINUS;

	case GL::Key::Escape:
		return Rocket::Core::Input::KI_ESCAPE;

	case GL::Key::Control:
		return Rocket::Core::Input::KI_LCONTROL; // or KI_RCONTROL

	case GL::Key::Shift:
		return Rocket::Core::Input::KI_LSHIFT; // or RSHIFT

	case GL::Key::Alt:
		return Rocket::Core::Input::KI_LMENU; // or RMENU

	case GL::Key::Space:
		return Rocket::Core::Input::KI_SPACE;

	case GL::Key::Enter:
		return Rocket::Core::Input::KI_RETURN;

	case GL::Key::Backspace:
		return Rocket::Core::Input::KI_BACK;

	case GL::Key::Tab:
		return Rocket::Core::Input::KI_TAB;

	case GL::Key::PageUp:
		return Rocket::Core::Input::KI_PRIOR;

	case GL::Key::PageDown:
		return Rocket::Core::Input::KI_NEXT;

	case GL::Key::End:
		return Rocket::Core::Input::KI_END;

	case GL::Key::Home:
		return Rocket::Core::Input::KI_HOME;

	case GL::Key::Insert:
		return Rocket::Core::Input::KI_INSERT;

	case GL::Key::Delete:
		return Rocket::Core::Input::KI_DELETE;

	case GL::Key::Pause:
		return Rocket::Core::Input::KI_PAUSE;

	case GL::Key::Left:
		return Rocket::Core::Input::KI_LEFT;

	case GL::Key::Right:
		return Rocket::Core::Input::KI_RIGHT;

	case GL::Key::Up:
		return Rocket::Core::Input::KI_UP;

	case GL::Key::Down:
		return Rocket::Core::Input::KI_DOWN;

	case GL::Key::Numpad0:
		return Rocket::Core::Input::KI_NUMPAD0;

	case GL::Key::Numpad1:
		return Rocket::Core::Input::KI_NUMPAD1;

	case GL::Key::Numpad2:
		return Rocket::Core::Input::KI_NUMPAD2;

	case GL::Key::Numpad3:
		return Rocket::Core::Input::KI_NUMPAD3;

	case GL::Key::Numpad4:
		return Rocket::Core::Input::KI_NUMPAD4;

	case GL::Key::Numpad5:
		return Rocket::Core::Input::KI_NUMPAD5;

	case GL::Key::Numpad6:
		return Rocket::Core::Input::KI_NUMPAD6;

	case GL::Key::Numpad7:
		return Rocket::Core::Input::KI_NUMPAD7;

	case GL::Key::Numpad8:
		return Rocket::Core::Input::KI_NUMPAD8;

	case GL::Key::Numpad9:
		return Rocket::Core::Input::KI_NUMPAD9;

	case GL::Key::Add:
		return Rocket::Core::Input::KI_ADD;

	case GL::Key::Subtract:
		return Rocket::Core::Input::KI_SUBTRACT;

	case GL::Key::Multiply:
		return Rocket::Core::Input::KI_MULTIPLY;

	case GL::Key::Divide:
		return Rocket::Core::Input::KI_DIVIDE;

	default:
		return Rocket::Core::Input::KI_UNKNOWN;
	}
}

int gfx::gui::RocketSystemInterface::translateModifiers(bool alt, bool control, bool shift) const
{
	int modifiers = 0;
	if (alt) modifiers |= Rocket::Core::Input::KM_ALT;
	if (control) modifiers |= Rocket::Core::Input::KM_CTRL;
	if (shift) modifiers |= Rocket::Core::Input::KM_SHIFT;
	return modifiers;
}

float gfx::gui::RocketSystemInterface::GetElapsedTime()
{
	return (0.001f * m_timer.peekElapsed());
}
