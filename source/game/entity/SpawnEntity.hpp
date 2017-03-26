/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include "game/entity/Entity.hpp"

namespace game
{
namespace entity
{
	class SpawnEntity : public Entity
	{
	public:
		SpawnEntity(uint32_t id, Entity::Platform platform, int player_id);
		Platform getPlatform() const;
		void setPlayerID(int player_id);

	private:
		Platform m_platform;
	};
}
}
