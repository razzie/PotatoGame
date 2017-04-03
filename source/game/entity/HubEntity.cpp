/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "common/PI.hpp"
#include "game/entity/HubEntity.hpp"

game::entity::HubEntity::HubEntity(uint32_t id, uint64_t seed, uint32_t size, Position position, raz::IMemoryPool* memory) :
	Entity(Type::HUB, id),
	m_seed(seed),
	m_size(size),
	m_position(position),
	m_inner_platform_count(m_size * 3),
	m_outer_platform_count(m_inner_platform_count * 2),
	m_platforms(memory)
{
	const uint32_t platform_count = m_inner_platform_count + m_outer_platform_count;
	m_platforms.reserve(platform_count);

	for (uint32_t i = 0; i < platform_count; ++i)
	{
		m_platforms.emplace_back(i, platform_count);
	}
}

uint64_t game::entity::HubEntity::getSeed() const
{
	return m_seed;
}

uint32_t game::entity::HubEntity::getSize() const
{
	return m_size;
}

game::entity::HubEntity::Position game::entity::HubEntity::getPosition() const
{
	return m_position;
}

uint32_t game::entity::HubEntity::getPlatformCount() const
{
	return m_platforms.size();
}

game::entity::PlatformEntity* game::entity::HubEntity::getPlatform(uint32_t id)
{
	if (id < getPlatformCount())
		return &m_platforms[id];
	else
		return nullptr;
}

const game::entity::PlatformEntity* game::entity::HubEntity::getPlatform(uint32_t id) const
{
	if (id < getPlatformCount())
		return &m_platforms[id];
	else
		return nullptr;
}

game::entity::PlatformEntity* game::entity::HubEntity::getPlatformByAngle(float angle)
{
	float angle_step = (2.f * (float)common::PI) / m_outer_platform_count;
	uint32_t id = (uint32_t(angle / angle_step) % m_outer_platform_count) + m_inner_platform_count;

	return getPlatform(id);
}

game::entity::PlatformEntity* game::entity::HubEntity::getRandomEmptyPlatform(raz::Random& random, Entity::Type type)
{
	uint32_t starting_id = random(0u, m_platforms.size() - 1);

	for (uint32_t id = 0, count = m_platforms.size(); id < count; ++id)
	{
		PlatformEntity* platform = getPlatform((starting_id + id) % count);
		Entity::Data entity_data;

		if (!platform->getEntity(type, entity_data))
			return platform;
	}

	return nullptr;
}

game::entity::PlatformEntity* game::entity::HubEntity::getRandomEntity(raz::Random& random, Entity::Type type)
{
	uint32_t starting_id = random(0u, m_platforms.size() - 1);

	for (uint32_t id = 0, count = m_platforms.size(); id < count; ++id)
	{
		PlatformEntity* platform = getPlatform((starting_id + id) % count);
		Entity::Data entity_data;

		if (platform->getEntity(type, entity_data))
			return platform;
	}

	return nullptr;
}

game::entity::PlatformEntity* game::entity::HubEntity::getRandomEntity(raz::Random& random, Entity::Type type, int player)
{
	uint32_t starting_id = random(0u, m_platforms.size() - 1);

	for (uint32_t id = 0, count = m_platforms.size(); id < count; ++id)
	{
		PlatformEntity* platform = getPlatform((starting_id + id) % count);
		Entity::Data entity_data;

		if (platform->getEntity(type, entity_data) && entity_data.player_id == player)
			return platform;
	}

	return nullptr;
}

unsigned game::entity::HubEntity::getPlatformNeighbors(uint32_t platform_id, uint32_t* neighbor_ids) const
{
	const PlatformEntity* platform = getPlatform(platform_id);
	if (!platform)
		return 0;

	uint32_t id = platform->getID();
	uint32_t sub_id = platform->getSubID();

	if (platform->isInner())
	{
		neighbor_ids[0] = (id + m_inner_platform_count - 1) % m_inner_platform_count;
		neighbor_ids[1] = (id + 1) % m_inner_platform_count;
		neighbor_ids[2] = ((id * 2) + m_outer_platform_count) % m_outer_platform_count + m_inner_platform_count;
		neighbor_ids[3] = (id * 2) + m_inner_platform_count;
		neighbor_ids[4] = ((id * 2 + 1) % m_outer_platform_count) + m_inner_platform_count;

		return 5;
	}
	else
	{
		if (id % 2 == 0)
		{
			neighbor_ids[0] = (sub_id / 2);
			neighbor_ids[1] = (sub_id / 2) + 1;
			neighbor_ids[2] = (id + m_outer_platform_count - 1) % m_outer_platform_count;
			neighbor_ids[3] = (id + 1) % m_outer_platform_count;
		}
		else
		{
			neighbor_ids[0] = (sub_id / 2) + 1;
			neighbor_ids[1] = (sub_id / 2) + 2;
			neighbor_ids[2] = (id + m_outer_platform_count - 1) % m_outer_platform_count;
			neighbor_ids[3] = (id + 1) % m_outer_platform_count;
		}

		return 4;
	}
}

unsigned game::entity::HubEntity::countEntities(Entity::Type type) const
{
	int count = 0;

	for (auto& platform : m_platforms)
	{
		Entity::Data data[PlatformEntity::MAX_ENTITIES];
		int data_count = platform.getEntities(data);

		for (int i = 0; i < data_count; ++i)
		{
			if (data[i].type == type)
				++count;
		}
	}

	return count;
}

unsigned game::entity::HubEntity::countPlayerEntities(int player_id) const
{
	int count = 0;

	for (auto& platform : m_platforms)
	{
		Entity::Data data[PlatformEntity::MAX_ENTITIES];
		int data_count = platform.getEntities(data);

		for (int i = 0; i < data_count; ++i)
		{
			if (data[i].player_id == player_id)
				++count;
		}
	}

	return count;
}
