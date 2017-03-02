/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <Rocket/Core/SystemInterface.h>
#include <Rocket/Core/Input.h>
#include <GL/Window/Window.hpp>
#include <GL/Window/Event.hpp>
#include <raz/timer.hpp>

namespace gfx
{
namespace gui
{
	class RocketSystemInterface : public Rocket::Core::SystemInterface
	{
	public:
		Rocket::Core::Input::KeyIdentifier translateKey(GL::Key::key_t) const;
		int translateModifiers(bool alt, bool control, bool shift) const;
		virtual float GetElapsedTime();
		//virtual bool LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message);

	private:
		raz::Timer m_timer;
	};
}
}
