/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/player/Player.hpp"

game::event::EntityEventQueue& game::player::Player::getEntityEventQueue()
{
	return m_entity_event_queue;
}
