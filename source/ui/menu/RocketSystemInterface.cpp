/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "ui/menu/RocketSystemInterface.hpp"

Rocket::Core::Input::KeyIdentifier ui::menu::RocketSystemInterface::translateKey(GL::Key::key_t key)
{
	return Rocket::Core::Input::KeyIdentifier();
}

int ui::menu::RocketSystemInterface::translateModifiers(bool alt, bool control, bool shift)
{
	return 0;
}

float ui::menu::RocketSystemInterface::GetElapsedTime()
{
	return 0.0f;
}
