/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <GL/Platform.hpp>
#include "common/InputHelper.hpp"

common::InputHelper::InputHelper() :
	m_mouse_pos{0,0},
	m_mouse_delta{ 0,0 },
	m_left_mouse_btn_down(false),
	m_right_mouse_btn_down(false),
	m_middle_mouse_btn_down(false),
	m_alt_down(false),
	m_control_down(false),
	m_shift_down(false)
{
}

void common::InputHelper::feed(GL::Event& ev)
{
	switch (ev.Type)
	{
	case GL::Event::MouseMove:
		m_mouse_delta.x = ev.Mouse.X - m_mouse_pos.x;
		m_mouse_delta.y = ev.Mouse.Y - m_mouse_pos.y;
		m_mouse_pos.x = ev.Mouse.X;
		m_mouse_pos.y = ev.Mouse.Y;
		break;

	case GL::Event::MouseDown:
		if (ev.Mouse.Button == GL::MouseButton::Left)
			m_left_mouse_btn_down = true;
		else if (ev.Mouse.Button == GL::MouseButton::Right)
			m_right_mouse_btn_down = true;
		else if (ev.Mouse.Button == GL::MouseButton::Middle)
			m_middle_mouse_btn_down = true;
		break;

	case GL::Event::MouseUp:
		if (ev.Mouse.Button == GL::MouseButton::Left)
			m_left_mouse_btn_down = false;
		else if (ev.Mouse.Button == GL::MouseButton::Right)
			m_right_mouse_btn_down = false;
		else if (ev.Mouse.Button == GL::MouseButton::Middle)
			m_middle_mouse_btn_down = false;
		break;

	case GL::Event::KeyDown:
		if (ev.Key.Code == GL::Key::Alt)
			m_alt_down = true;
		else if (ev.Key.Code == GL::Key::Control)
			m_control_down = true;
		else if (ev.Key.Code == GL::Key::Shift)
			m_shift_down = true;
		break;

	case GL::Event::KeyUp:
		if (ev.Key.Code == GL::Key::Alt)
			m_alt_down = false;
		else if (ev.Key.Code == GL::Key::Control)
			m_control_down = false;
		else if (ev.Key.Code == GL::Key::Shift)
			m_shift_down = false;
		break;
	}
}

common::Point2D<int> common::InputHelper::getMousePosition() const
{
	return m_mouse_pos;
}

common::Point2D<int> common::InputHelper::getMouseDelta() const
{
	return m_mouse_delta;
}

bool common::InputHelper::isLeftMouseButtonDown() const
{
	return m_left_mouse_btn_down;
}

bool common::InputHelper::isRightMouseButtonDown() const
{
	return m_right_mouse_btn_down;
}

bool common::InputHelper::isMiddleMouseButtonDown() const
{
	return m_middle_mouse_btn_down;
}

bool common::InputHelper::isAltDown() const
{
	return m_alt_down;
}

bool common::InputHelper::isControlDown() const
{
	return m_control_down;
}

bool common::InputHelper::isShiftDown() const
{
	return m_shift_down;
}
