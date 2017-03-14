/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

namespace game
{
namespace level
{
	namespace entity
	{
		class EntityManager;
	}

	class LevelBuilder
	{
	public:
		void build(entity::EntityManager& entities);
	};
}
}
