/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <array>
#include "game/level/entity/Entity.hpp"

namespace game
{
namespace level
{
namespace entity
{
	class CreatureEntity : public Entity
	{
	public:
		constexpr static int DEFAULT_CHARGES = 15;
		constexpr static int DEFAULT_MAX_CHARGES = 30;

		CreatureEntity(uint32_t id, uint64_t seed, Entity::Platform platform, int player_id);
		uint64_t getSeed() const;
		Platform getPlatform() const;
		void setPlatform(Platform platform);
		void setPlayerID(int player_id);
		int getCharges() const;
		void addCharges(int amount);
		void lowerCharges();
		int getMaxCharges() const;
		void setMaxCharges(int amount);

	private:
		uint64_t m_seed;
		Platform m_platform;
		int m_charges;
		int m_max_charges;
	};
}
}
}
