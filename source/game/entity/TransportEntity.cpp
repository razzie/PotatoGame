/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/entity/TransportEntity.hpp"

game::entity::TransportEntity::TransportEntity(uint32_t id, Entity::Platform platform1, Entity::Platform platform2) :
	Entity(Type::TRANSPORT, id),
	m_platform1(platform1),
	m_platform2(platform2)
{
}

game::entity::Entity::Platform game::entity::TransportEntity::getPlatform1() const
{
	return m_platform1;
}

game::entity::Entity::Platform game::entity::TransportEntity::getPlatform2() const
{
	return m_platform2;
}
