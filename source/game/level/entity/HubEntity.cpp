/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/level/entity/HubEntity.hpp"

game::level::entity::HubEntity::HubEntity(uint32_t id, uint64_t seed, uint32_t size, Position position) :
	Entity(Type::HUB, id)
{
}

uint64_t game::level::entity::HubEntity::getSeed() const
{
	return uint64_t();
}

uint32_t game::level::entity::HubEntity::getSize() const
{
	return uint32_t();
}

game::level::entity::HubEntity::Position game::level::entity::HubEntity::getPosition() const
{
	return Position();
}

uint32_t game::level::entity::HubEntity::getPlatformCount() const
{
	return uint32_t();
}

game::level::entity::PlatformEntity* game::level::entity::HubEntity::getPlatform(uint32_t id)
{
	return nullptr;
}

const game::level::entity::PlatformEntity* game::level::entity::HubEntity::getPlatform(uint32_t id) const
{
	return nullptr;
}

game::level::entity::PlatformEntity* game::level::entity::HubEntity::getPlatformByAngle(float angle)
{
	return nullptr;
}

const game::level::entity::PlatformEntity* game::level::entity::HubEntity::getPlatformByAngle(float angle) const
{
	return nullptr;
}

int game::level::entity::HubEntity::countPlayerEntities(int player_id) const
{
	return 0;
}
