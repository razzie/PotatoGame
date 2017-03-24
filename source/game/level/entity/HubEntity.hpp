/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <vector>
#include <raz/memory.hpp>
#include "game/level/entity/Entity.hpp"
#include "game/level/entity/PlatformEntity.hpp"

namespace game
{
namespace level
{
namespace entity
{
	class HubEntity : public Entity
	{
	public:
		struct Position
		{
			float x;
			float z;
		};

		HubEntity(uint32_t id, uint64_t seed, uint32_t size, Position position);
		uint64_t getSeed() const;
		uint32_t getSize() const;
		Position getPosition() const;
		uint32_t getPlatformCount() const;
		PlatformEntity* getPlatform(uint32_t id);
		const PlatformEntity* getPlatform(uint32_t id) const;
		PlatformEntity* getPlatformByAngle(float angle);
		const PlatformEntity* getPlatformByAngle(float angle) const;
		int countPlayerEntities(int player_id) const;

	private:
		template<class T>
		using Vector = std::vector<T, raz::Allocator<T>>;

		uint64_t m_seed;
		uint32_t m_size;
		Position m_position;
		Vector<PlatformEntity> m_platforms;
	};
}
}
}
