/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/player/Player.hpp"

game::player::Player::Player(Type type, raz::IMemoryPool* memory) :
	m_type(type)
{
}

game::player::Player::~Player()
{
}

game::player::Player::Type game::player::Player::getType() const
{
	return m_type;
}
