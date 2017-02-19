/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/Window/Event.hpp>
#include "common/Point2D.hpp"

namespace common
{
	class InputHelper
	{
	public:
		InputHelper();
		void feed(GL::Event& ev);
		Point2D<int> getMousePosition() const;
		Point2D<int> getMouseDelta() const;
		bool isLeftMouseButtonDown();
		bool isRightMouseButtonDown();
		bool isMiddleMouseButtonDown();
		bool isAltDown() const;
		bool isControlDown() const;
		bool isShiftDown() const;

	private:
		Point2D<int> m_mouse_pos;
		Point2D<int> m_mouse_delta;
		bool m_left_mouse_btn_down;
		bool m_right_mouse_btn_down;
		bool m_middle_mouse_btn_down;
		bool m_alt_down;
		bool m_control_down;
		bool m_shift_down;
	};
}
