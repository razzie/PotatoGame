/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <vector>
#include <raz/memory.hpp>
#include "game/entity/Entity.hpp"
#include "game/entity/PlatformEntity.hpp"

namespace game
{
namespace entity
{
	class HubEntity : public Entity
	{
	public:
		static constexpr size_t MAX_NEIGHBORS = 5;

		struct Position
		{
			float x;
			float z;
		};

		HubEntity(uint32_t id, uint64_t seed, uint32_t size, Position position, raz::IMemoryPool* memory = nullptr);
		uint64_t getSeed() const;
		uint32_t getSize() const;
		Position getPosition() const;
		uint32_t getPlatformCount() const;
		PlatformEntity* getPlatform(uint32_t id);
		const PlatformEntity* getPlatform(uint32_t id) const;
		PlatformEntity* getPlatformByAngle(float angle);
		const PlatformEntity* getPlatformByAngle(float angle) const;
		int getPlatformNeighbors(uint32_t platform_id, uint32_t* neighbor_ids) const;
		int countPlayerEntities(int player_id) const;

	private:
		template<class T>
		using Vector = std::vector<T, raz::Allocator<T>>;

		uint64_t m_seed;
		uint32_t m_size;
		Position m_position;
		uint32_t m_inner_platform_count;
		uint32_t m_outer_platform_count;
		Vector<PlatformEntity> m_platforms;

		uint32_t getPlatformIDByAngle(float angle) const;
	};
}
}
